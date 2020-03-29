#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace cv;
using namespace std;

int main()
{
	
	Mat src = imread("gaussianNoise17.jpg");
	imshow("src", src);
	waitKey(0);
	
	return 0;
}

