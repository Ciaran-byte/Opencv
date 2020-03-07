#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	//01读取图片
	Mat m = imread("1.jpg");
	Mat hsv;
	cvtColor(m, hsv, COLOR_BGR2HSV);


	//02设置参数
	const int channels[] = { 0,1 };
	Mat hsvHist;

	int hSize = 30;
	int sSize = 32;
	const int histSize[] = { hSize,sSize };

	float hRange[] = { 0,180 };
	float sRange[] = { 0,256 };
	const float* histRange[] = { hRange,sRange };
	
	bool uniform = true;
	bool accumulate = false;


	//03求直方图
	calcHist(&hsv, 1, channels, Mat(), hsvHist, 2, histSize, histRange, uniform, accumulate);



	//04归一化
	normalize(hsvHist, hsvHist, 0, 255, NORM_MINMAX);
	
	//05绘图
	
	int scale = 20;
	Mat hist(sSize * scale, hSize * scale, CV_8UC3, Scalar::all(0));

	for (int i = 1; i < hSize; i++)
	{
		for (int j = 1; j < sSize; j++)
		{
			rectangle
			(
				hist,
				Point((i - 1) * scale, (j - 1) * scale),
				Point((i)*scale, j * scale),
				Scalar::all(cvRound(hsvHist.at<float>(i - 1, j - 1))),
				-1
				
			);
		}
	}
	imshow("hist", hist);


	waitKey(0);
	return 0;
}

