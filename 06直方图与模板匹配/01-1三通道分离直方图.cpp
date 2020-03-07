#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	//01读取图像
	Mat src = imread("1.jpg");

	

	//02设定参数
	Mat b_hist, g_hist, r_hist;
	const int channelIndex1[] = { 0};
	const int channelIndex2[] = { 1 };
	const int channelIndex3[] = { 2 };
	const int histSize[] = { 256 };
	float range[] = { 0,255 };
	const float* histRange[] = { range };

	//03计算直方图
	calcHist(&src, 1, channelIndex1, Mat(), b_hist, 1, histSize, histRange, true, false);
	calcHist(&src, 1, channelIndex2, Mat(), g_hist, 1, histSize, histRange, true, false);
	calcHist(&src, 1, channelIndex3, Mat(), r_hist, 1, histSize, histRange, true, false);

	//04参数归一化
	int bins = 256;
	int hist_w = 512;
	int hist_h = 400;
	Mat hist1(hist_h, hist_w, CV_8UC3, Scalar::all(0));
	normalize(b_hist, b_hist, 0, 400, NORM_MINMAX);
	normalize(g_hist, g_hist, 0, 400, NORM_MINMAX);
	normalize(r_hist, r_hist, 0, 400, NORM_MINMAX);

	int bin_w = cvRound((double)hist_w / bins);
	//05绘制直方图
	for (int i = 1; i < bins; i++)
	{
		line
		(
			hist1,
			Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1, 0))),
			Point(bin_w * i, hist_h - cvRound(b_hist.at<float>(i, 0))),
			Scalar(255, 0, 0), 2
		);
		line
		(
			hist1,
			Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1, 0))),
			Point(bin_w * i, hist_h - cvRound(g_hist.at<float>(i, 0))),
			Scalar(0, 255, 0), 2
		);
		line
		(
			hist1,
			Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1, 0))),
			Point(bin_w * i, hist_h - cvRound(r_hist.at<float>(i, 0))),
			Scalar(0, 0, 255), 2
		);
	}

	imshow("hist", hist1);
	waitKey(0);


	return 0;
}

