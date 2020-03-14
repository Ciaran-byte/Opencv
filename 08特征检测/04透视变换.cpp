#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
using namespace std;
using namespace cv;
using namespace xfeatures2d;

int main()
{
	//01 读取图片
	Mat src1 = imread("1.jpg");
	Mat src2 = imread("3.jpg");
	imshow("src1", src1);
	imshow("src2", src2);

	//02 创建关键点

	
	int minHessian = 800;//使用海森矩阵检测的阈值
	Ptr<SURF> detector = SURF::create(minHessian);

	vector<KeyPoint> keyPoint1, keyPoint2;
	detector->detect(src1, keyPoint1);
	detector->detect(src2, keyPoint2);

	


	//03 为关键点计算特征值
	Mat descriptor1, descriptor2;
	detector->compute(src1, keyPoint1, descriptor1);
	detector->compute(src2, keyPoint2, descriptor2);

	
	//04 匹配关键点

	// flann匹配方法

	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptor1, descriptor2, matches);

	


	//05 筛选匹配的关键点
	double min_dst = 100;
	double max_dst = 0;
	vector<DMatch> good_matches;
	for (int i = 0; i < matches.size(); i++)
	{
		double distance = matches[i].distance;
		if (distance > max_dst)
		{
			max_dst = distance;
		}
		if (distance < min_dst)
		{
			min_dst = distance;
		}
	}
	cout << max_dst << endl;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < 3 * min_dst)
		{
			good_matches.push_back(matches[i]);
		}
	}


	//06绘制匹配结果
	Mat out;
	drawMatches(
		src1, keyPoint1,
		src2, keyPoint2,
		good_matches, out,
		Scalar::all(-1), Scalar::all(-1),
		vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
	);
	imshow("out", out);

	//07 分离匹配对
	vector<Point2f> obj, scene;
	for (int i = 0; i < good_matches.size(); i++)
	{
		obj.push_back(keyPoint1[good_matches[i].queryIdx].pt);
		scene.push_back(keyPoint2[good_matches[i].trainIdx].pt);
	}
	
	//08 寻找透视变换矩阵
	Mat H = findHomography(obj, scene, CV_RANSAC);
	
	//09 从待测图片中获取角点
	vector<Point2f> corners(4);
	corners[0] = Point2f(0, 0);
	corners[1] = Point2f(static_cast<float>(src1.cols), 0);
	corners[2] = Point2f(static_cast<float>(src1.cols), static_cast<float>(src1.rows));
	corners[3] = Point2f(0, static_cast<float>(src1.rows));
	vector<Point2f> dst_corners(4);
	//10 透视变换
	perspectiveTransform(corners, dst_corners, H);

	//11 绘制直线
	line(out,
		dst_corners[0] + Point2f(static_cast<float>(src1.cols), 0),
		dst_corners[1] + Point2f(static_cast<float>(src1.cols), 0),
		Scalar(255, 0, 123),
		4
	);
	line(out,
		dst_corners[1] + Point2f(static_cast<float>(src1.cols), 0),
		dst_corners[2] + Point2f(static_cast<float>(src1.cols), 0),
		Scalar(255, 0, 123),
		4
	);
	line(out,
		dst_corners[2] + Point2f(static_cast<float>(src1.cols), 0),
		dst_corners[3] + Point2f(static_cast<float>(src1.cols), 0),
		Scalar(255, 0, 123),
		4
	);
	line(out,
		dst_corners[3] + Point2f(static_cast<float>(src1.cols), 0),
		dst_corners[0] + Point2f(static_cast<float>(src1.cols), 0),
		Scalar(255, 0, 123),
		4
	);

	imshow("out2", out);
	waitKey(0);

	return 0;
}


