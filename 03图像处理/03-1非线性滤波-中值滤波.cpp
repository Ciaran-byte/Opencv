#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{

	Mat m = imread("bosong.jfif");
	imshow("m", m);
	Mat dst;
	/*boxFilter(m, dst, -1, Size(3, 3));
	imshow("dst", dst);
	GaussianBlur(m, dst, Size(9, 9), 0, 0);
	imshow("dst2", dst);
	medianBlur(m, dst,5);
	imshow("dst3", dst);*/
	
	bilateralFilter(m, dst, 45,10, 25/2);
	imshow("dst5", dst);
	bilateralFilter(m, dst, 45, 40, 25 / 2);
	imshow("dst6", dst);
	waitKey(0);


	return 0;
}

