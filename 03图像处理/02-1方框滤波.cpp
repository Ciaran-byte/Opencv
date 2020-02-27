#include<opencv2/opencv.hpp>
#include<stdio.h>

using namespace std;
using namespace cv;

int main()
{

	Mat src = imread("1.jpg");
	imshow("src", src);
	Mat dst;
	boxFilter(src, dst, -1, Size(20, 20), Point(-1, -1));
	imshow("dst", dst);
	

	waitKey(0);
	return 0;
}
