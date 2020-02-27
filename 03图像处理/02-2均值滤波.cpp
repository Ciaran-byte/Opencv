#include<opencv2/opencv.hpp>
#include<stdio.h>

using namespace std;
using namespace cv;

int main()
{

	Mat src = imread("1.jpg");
	imshow("src", src);
	Mat dst;
	boxFilter(src, dst, -1, Size(2, 200), Point(-1, -1));
	imshow("dst1", dst);
	boxFilter(src, dst, -1, Size(200, 2), Point(-1, -1));
	imshow("dst2", dst);
	

	waitKey(0);
	return 0;
}
