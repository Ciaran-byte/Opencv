#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat m = imread("2.jpg",0);
	Mat n;
	adaptiveThreshold(m, n, 255.0, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11,2);
	//threshold(m, n, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("n",n);


	waitKey(0);
	return 0;
}

