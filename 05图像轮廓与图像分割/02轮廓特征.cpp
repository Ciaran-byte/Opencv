#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src, dst;

	//01灰度化
	src = imread("1.jpg",0);
	imshow("src",src);

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
	findContours(dst, contours,hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//05计算矩
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	//06计算中心矩
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}

	//07绘制轮廓
	Mat drawing=Mat::zeros(dst.size(),CV_8UC3);
	RNG rng(12345);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color,2,8,hierarchy,0,Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
	imshow("dst", drawing);

	//08计算面积和长度
	for (int i = 0; i < contours.size(); i++)
	{
		cout << "m00：" << mu[i].m00 << endl;
		cout << "面积：" << contourArea(contours[i], false) << endl;
		cout << "长度:" << arcLength(contours[i], true);
		cout << endl<<endl;
	}
	waitKey(0);

	return 0;
}

