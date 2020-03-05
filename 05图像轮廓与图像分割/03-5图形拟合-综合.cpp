#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src, dst;

	//01灰度化
	src = imread("1.jpg", 0);
	imshow("src", src);

	//02滤波
	blur(src, dst, Size(3, 3));
	//GaussianBlur(src, dst, Size(3, 3), 0);
	//dst = src.clone();
	imshow("dst1", dst);

	//03二值化



	Canny(dst, dst, 100, 200, 3);
	imshow("dst2", dst);

	//04查找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//05进行多边形拟合、圆形拟合和矩形拟合，因此需要定义存储量
	vector<vector<Point>> polyContours(contours.size());
	vector<Rect> rt(contours.size());
	vector<Point2f> center(contours.size());
	vector<float> radius(contours.size());
	vector<double>epsilion(contours.size());

	

	//05提取轮廓并绘图
	Mat drawing = Mat::zeros(dst.size(), CV_8UC3);
	RNG rng(12345);
	for (int i = 0; i < contours.size(); i++)
	{
		//提取轮廓
		epsilion[i] = 0.01 * arcLength(contours[i], true);
		approxPolyDP(contours[i], polyContours[i], epsilion[i], true);
		rt[i]=boundingRect(contours[i]);
		minEnclosingCircle(contours[i], center[i], radius[i]);


		//绘图
		
		drawContours(drawing,polyContours , i, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, hierarchy, 0, Point());
		circle(drawing, center[i], radius[i], Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
		rectangle(drawing, rt[i], Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
	
	}
	imshow("dst", drawing);

	//08计算面积和长度
	
	waitKey(0);

	return 0;
}

