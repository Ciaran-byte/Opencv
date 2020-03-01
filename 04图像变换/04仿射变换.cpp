#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{

	//01输入图像
	Mat m = imread("1.jpg");
	Mat dst1,dst2;
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);


	//02计算变换矩阵:

	//计算仿射三点变换前和后的坐标，通过这三个变换点，计算变换矩阵
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float> (m.cols), static_cast<float> (0));
	srcTriangle[2] = Point2f(static_cast<float> (0),static_cast<float> (m.rows));

	dstTriangle[0] = Point2f(0, static_cast<float> (m.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float> (m.cols*0.65), static_cast<float> (m.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float> (m.cols*0.15), static_cast<float> (m.rows * 0.6));

	//获取三点变换矩阵
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	//获取旋转变换矩阵
	rotMat = getRotationMatrix2D(Point2f(0, 0), 30, 1);


	//03进行仿射变换

	warpAffine(m, dst1, warpMat, m.size());
	imshow("dst1", dst1);


	warpAffine(dst1, dst2, rotMat, m.size());
	imshow("dst2", dst2);

	waitKey(0);

	return 0;
}

