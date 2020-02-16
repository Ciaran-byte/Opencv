#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat m = Mat::zeros(600, 600, CV_32F);

	ellipse(m, Point(300, 300),Size(100, 50), 0, 0, 360,Scalar(255,0,0), 1, 8);
	ellipse(m, Point(300, 300), Size(100, 50), 90, 0, 360, Scalar(255, 0, 0), 1, 8);
	ellipse(m, Point(300, 300), Size(100, 50), 45, 0, 360, Scalar(255, 0, 0), 1, 8);
	ellipse(m, Point(300, 300), Size(100, 50), -45, 0, 360, Scalar(255, 0, 0), 1, 8);
	circle(m, Point(300, 300), 20, Scalar(255, 0, 0),-1);
	
	imshow("a", m);
	waitKey(0);
	return 0;
}

