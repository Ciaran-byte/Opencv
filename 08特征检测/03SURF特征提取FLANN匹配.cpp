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

	//02-1使用surf方法判断关键点
	int minHessian = 800;//使用海森矩阵检测的阈值
	Ptr<SURF> detector =SURF::create(minHessian);

	vector<KeyPoint> keyPoint1, keyPoint2;
	detector->detect(src1, keyPoint1);
	detector->detect(src2, keyPoint2);

	//02-2 绘制关键点
	/*Mat dst1, dst2;
	drawKeypoints(src1, keyPoint1, dst1);
	drawKeypoints(src2, keyPoint2, dst2);
	imshow("dst1", dst1);
	imshow("dst2", dst2);*/


	//03 为关键点计算特征值
	Mat descriptor1, descriptor2;
	detector->compute(src1, keyPoint1, descriptor1);
	detector->compute(src2, keyPoint2, descriptor2);

	//03备注：下面是一种可以同时进行关键点检测和特征值计算的写法
	/*detector->detectAndCompute(src1, Mat(), keyPoint1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keyPoint2, descriptor2);*/

	//04 匹配关键点
	
	//04-1 flann匹配方法

	//写法1
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptor1, descriptor2, matches);
	
	//写法2
	/*Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);*/
	
	
	//04-2 对比一下暴力匹配法的写法1
	/*Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
	vector< DMatch > matches;
	matcher->match(descriptor1, descriptor2, matches);*/

	//暴力匹配法的写法2
	/*BFMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptor1, descriptor2, matches);*/

	//04-3 绘制关键点匹配之后的结果图
	/*Mat m;
	drawMatches(src1, keyPoint1, src2, keyPoint2, matches, m);
	imshow("m", m);*/

	
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
		if (matches[i].distance < 2 * min_dst)
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
	waitKey(0);

	return 0;
}


