#include<iostream>9
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{

	Mat src, src1,grad_x, grad_y, abs_grad_x, abs_grad_y, dst;
		src = imread("1.jpg", 0);
		src1 = imread("1.jpg", 0);

		GaussianBlur(src1, src1, Size(9, 9), 0, 0);

		Scharr(src1, grad_x, CV_32F, 1, 0, 1);
		convertScaleAbs(grad_x, abs_grad_x);

	
		Scharr(src1, grad_y, CV_32F, 0, 1, 1);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
		imshow("a", dst);




		Scharr(src, grad_x, CV_32F, 1, 0, 1);
		convertScaleAbs(grad_x, abs_grad_x);


		Scharr(src, grad_y, CV_32F, 0, 1, 1);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
		imshow("c", dst);




		Sobel(src, grad_x, CV_32F, 1, 0);
		convertScaleAbs(grad_x, abs_grad_x);

		Sobel(src, grad_y, CV_32F, 0, 1);
		convertScaleAbs(grad_y, abs_grad_y);
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
		imshow("b", dst);
	waitKey(0);
	return 0;
}

