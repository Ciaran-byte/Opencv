#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//第一部分是自己写的harris角点检测函数，效果比较差
	//01获取图片和灰度图
	Mat src = imread("house.jpg");
	Mat gray = imread("house.jpg", 0);
	Mat sss = src.clone();

	//02计算x方向和y方向的梯度
	Mat sobel_x, sobel_y;
	Sobel(gray, sobel_x, CV_16S, 1, 0, 3);
	Sobel(gray, sobel_y, CV_16S, 0, 1, 3);

	//03把梯度转换为8位无符号整型
	convertScaleAbs(sobel_x, sobel_x);
	convertScaleAbs(sobel_y, sobel_y);

	//04计算Ix^2,Iy^2和Ix*Iy

	//Ix^2
	int row = sobel_x.rows;
	int col = sobel_x.cols;
	Mat sobelxx(row, col, CV_32F);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sobelxx.at<float>(i, j) = sobel_x.at<uchar>(i, j) * sobel_x.at<uchar>(i, j);
		}
	}
	//Iy^2
	Mat sobelyy(row, col, CV_32F);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sobelyy.at<float>(i, j) = sobel_y.at<uchar>(i, j) * sobel_y.at<uchar>(i, j);
		}
	}
	//Ixy
	Mat sobelxy(row, col, CV_32F);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			sobelxy.at<float>(i, j) = sobel_x.at<uchar>(i, j) * sobel_y.at<uchar>(i, j);
		}
	}

	//05 对上面三个参数进行高斯滤波
	GaussianBlur(sobelxx, sobelxx, Size(3,3),1);
	GaussianBlur(sobelxy, sobelxy, Size(3,3),1);
	GaussianBlur(sobelyy, sobelyy, Size(3,3),1);
											  
	//06计算评定参数
	Mat dst(row, col, CV_32F);
	float k = 0.05;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			float a = sobelxx.at<float>(i, j);
			float b = sobelyy.at<float>(i, j);
			float c = sobelxy.at<float>(i, j);

			dst.at<float>(i, j) = (a * b - c * c) - k * (a + b) * (a + b);
		}
	}
	double min, max;
	minMaxLoc(dst, &min, &max);
	cout << max << endl;
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	//07非极大值抑制
	int r = 3;
	int dir[8][2] = { 0, 1, 0, -1, 1, 0, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1 };
	for (int i = r; i < row-r; i++)
	{
		for (int j = r; j < col-r; j++) {
			bool flag = true;

			for (int k = 0; k < 8; k++)
			{
				int tx = i + dir[k][0];
				int ty = j + dir[k][1];
				if (dst.at<float>(i, j) < dst.at<float>(tx, ty)) {
					flag = false;
				}


			}
			if (flag == true && (int)dst.at<float>(i, j) > 180)
			{
				//circle(src, Point(i, j), 5, Scalar(0, 0, 255), -1, 8, 0);
				src.at<Vec3b>(i, j)[0] = 0;
				src.at<Vec3b>(i, j)[1] = 0;
				src.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}

	namedWindow("src", WINDOW_NORMAL);
	
	imshow("src", src);


	//第二部分使用的是opencv自带的harris角点检测，效果比较好
	Mat src2,norm ;
	
	cornerHarris(gray, src2, 2, 3, 0.06);
	normalize(src2, norm, 0, 255, NORM_MINMAX);
	convertScaleAbs(norm, norm);
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < col; i++)
		{
			if (norm.at<uchar>(j, i) > 150)
			{
				circle(sss, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
	}
	imshow("sss", sss);
	waitKey(0);
	return 0;
}

