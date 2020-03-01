#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat src, gray, dst,dst2;
	src = imread("1.jpg",0);
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	Laplacian(dst, dst2, CV_16S,3);
	convertScaleAbs(dst2, dst2);
	imshow("a", dst2);




	waitKey(0);
	return 0;
}

