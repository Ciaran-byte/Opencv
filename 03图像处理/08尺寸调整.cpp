//该程序用于实现图像拼接

#include<iostream>
#include<opencv2/opencv.hpp>
#include<algorithm>
using namespace std;
using namespace cv;

int main()
{
	
	Mat m = imread("1.jpg");
	for (int i = 0; i < 5; i++)
	{
		resize(m, m,Size(), 0.5, 0.5,INTER_LINEAR);
	}
	imshow("a", m);
	for (int i = 0; i < 5; i++)
	{
		resize(m, m, Size(), 2, 2, INTER_LINEAR);
	}
	imshow("c", m);

	
		for (int i = 0; i < 5; i++)
	{
		resize(m, m, Size(), 0.5, 0.5,CV_INTER_AREA);
	}
	imshow("D", m);
	for (int i = 0; i < 5; i++, CV_INTER_AREA)
	{
		resize(m, m, Size(), 2, 2);
	}
	imshow("E", m);

	waitKey(0);
	return 0;
}


