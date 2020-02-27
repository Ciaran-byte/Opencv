#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;



int main()
{

	Mat src = imread("1.jpg");
	Mat dst;
	imshow("src", src);
	Mat n = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	morphologyEx(src, dst, MORPH_OPEN, n);

	imshow("dst", dst);

	morphologyEx(src, dst, MORPH_CLOSE, n);

	imshow("dst2", dst);

	morphologyEx(src, dst, MORPH_BLACKHAT, n);
	imshow("dst3", dst);

	morphologyEx(src, dst, MORPH_TOPHAT, n);
	imshow("dst4", dst);

	morphologyEx(src, dst, MORPH_GRADIENT, n);
	imshow("dst5", dst);

	waitKey(0);

	return 0;
}



