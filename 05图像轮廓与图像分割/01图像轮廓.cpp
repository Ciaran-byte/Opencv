#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat m = imread("4.jpg",0);
	imshow("m", m);

	Mat dst = m.clone();
	
	threshold(dst, dst, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("dst", dst);
	
	Mat n = Mat::zeros(m.cols, m.rows, m.type());
	
	
	vector<vector<Point>> contours;

	vector<Vec4i> hierarchy;
	findContours(dst, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255);
		drawContours(n, contours, index, color, 1, 8, hierarchy);
	}

	
	
		
		imshow("dst1", n);


	waitKey(0);

	return 0;
}

