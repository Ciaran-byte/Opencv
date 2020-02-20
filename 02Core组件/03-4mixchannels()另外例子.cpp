#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat bgra(500, 500, CV_8UC4, Scalar(255, 0, 0, 255));
	Mat bgr(bgra.rows, bgra.cols, CV_8UC3);
	Mat alpha(bgra.rows, bgra.cols, CV_8UC1);
	

	Mat out[] = { bgr,alpha };
	int fromTo[] = { 0, 2, 1, 1, 2, 0, 3, 3 };
	
	mixChannels(&bgra, 1, out, 2, fromTo, 4);
	imshow("bgra", bgra);
	imshow("bgr", bgr);
	imshow("alpha", alpha);
	
	

	waitKey(0);

	return 0;
}




