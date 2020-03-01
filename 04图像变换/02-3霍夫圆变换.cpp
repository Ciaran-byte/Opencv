#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{
	Mat n = imread("1.jpg");
	Mat m = imread("1.jpg",0);
	GaussianBlur(m, m, Size(9, 9), 2,2);
	
	vector<Vec3f> circles;
	HoughCircles(m, circles, HOUGH_GRADIENT, 1, 10, 200, 50);

	for (size_t i = 0; i <circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(n, center, radius, Scalar(0,0,255), 3);
		circle(n, center, 3, Scalar(255,0,0), -1);

	}
	imshow("m", n);



	waitKey(0);
	return 0;
}

