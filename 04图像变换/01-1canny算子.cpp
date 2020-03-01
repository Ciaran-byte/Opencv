#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat src = imread("1.jpg");
	Mat src1 = src.clone();

	Mat dst, gray, edge,dst2;

	//01转灰度
	cvtColor(src, gray, CV_RGB2GRAY);

	//02方均滤波
	blur(gray, edge,Size(5,5));

	//03canny算子
	Canny(edge, dst, 30, 90);
	src.copyTo(dst2, dst);
	imshow("m", dst2);
	Canny(edge, dst, 3, 9);

	src.copyTo(dst2, dst);
	imshow("n", dst2);
	waitKey(0);








	return 0;
}

