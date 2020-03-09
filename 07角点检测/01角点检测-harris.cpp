#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//��һ�������Լ�д��harris�ǵ��⺯����Ч���Ƚϲ�
	//01��ȡͼƬ�ͻҶ�ͼ
	Mat src = imread("house.jpg");
	Mat gray = imread("house.jpg", 0);
	Mat sss = src.clone();

	//02����x�����y������ݶ�
	Mat sobel_x, sobel_y;
	Sobel(gray, sobel_x, CV_16S, 1, 0, 3);
	Sobel(gray, sobel_y, CV_16S, 0, 1, 3);

	//03���ݶ�ת��Ϊ8λ�޷�������
	convertScaleAbs(sobel_x, sobel_x);
	convertScaleAbs(sobel_y, sobel_y);

	//04����Ix^2,Iy^2��Ix*Iy

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

	//05 �����������������и�˹�˲�
	GaussianBlur(sobelxx, sobelxx, Size(3,3),1);
	GaussianBlur(sobelxy, sobelxy, Size(3,3),1);
	GaussianBlur(sobelyy, sobelyy, Size(3,3),1);
											  
	//06������������
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
	//07�Ǽ���ֵ����
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


	//�ڶ�����ʹ�õ���opencv�Դ���harris�ǵ��⣬Ч���ȽϺ�
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

