#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat grad_x, grad_y, abs_grad_x, abs_grad_y, dst;
	Mat m = imread("1.jpg");

	//求x方向梯度
	Sobel(m, grad_x, CV_32F, 1, 0);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("a", abs_grad_x);
	
	//求y方向梯度
	Sobel(m, grad_y, CV_32F, 1, 0);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("b", abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}

