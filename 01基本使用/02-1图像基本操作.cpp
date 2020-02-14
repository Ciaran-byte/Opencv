#include<opencv2/opencv.hpp>

#include<stdio.h>
#include<stdlib.h>
using namespace cv;

int main()
{

	Mat m = imread("dota.jpg", IMREAD_ANYDEPTH| IMREAD_ANYCOLOR);
	namedWindow("a",WINDOW_NORMAL);
	imshow("a", m);
	imwrite("1.jpg", m);
	waitKey(0);
	
	return 0;
}
