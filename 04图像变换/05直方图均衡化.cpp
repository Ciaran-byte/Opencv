#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{

	
	Mat m = imread("1.jpg");
	vector<Mat> channels;
	split(m, channels);
	Mat blue, green, red;
	blue = channels[0];
	green = channels[1];
	red = channels[2];

	imshow("1", blue);
	imshow("2", green);
	imshow("3", red);

	equalizeHist(blue, blue);
	equalizeHist(green, green);
	equalizeHist(red, red);
	imshow("4", blue);
	imshow("5", green);
	imshow("6", red);
	
	Mat dst;
	
	merge(channels, dst);
		
	
	
	imshow("m", m);
	imshow("dst", dst);

	waitKey(0);

	return 0;
}

