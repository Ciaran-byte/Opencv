//该程序用于实现图像拼接

#include<iostream>
#include<opencv2/opencv.hpp>
#include<algorithm>
using namespace std;
using namespace cv;

int main()
{

	Mat m = imread("1.jpg",0);
	Mat n;
	threshold(m, n, 0, 255, THRESH_BINARY_INV | CV_THRESH_OTSU);
	imshow("a", n);
	threshold(m, n, 0, 255, THRESH_BINARY | CV_THRESH_OTSU);
	imshow("b", n);
	threshold(m, n, 0, 255, THRESH_TRUNC | CV_THRESH_OTSU);
	imshow("c", n);
	threshold(m, n, 0, 255, THRESH_TOZERO| CV_THRESH_OTSU);
	imshow("d", n);

	threshold(m, n, 0, 255, THRESH_TOZERO_INV | CV_THRESH_OTSU);
	imshow("e", n);

	
	imshow("f", n);
	waitKey(0);
	return 0;
}


