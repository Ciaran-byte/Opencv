#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	//01����ͼƬ
	const Mat m = imread("1.jpg", 0);

	//02�趨����
	const int channels[] = { 0}; //����ͼƬm�ĵ�0��ͨ����ֱ��ͼ
	Mat gray_hist;
	int size = 256;
	const int histSize[] = { size };
	float range[] = { 0,255 };
	const float* histRange[] = { range };
	bool uniform = true;
	bool accumulate = false;


	//03����ֱ��ͼ
	calcHist(&m, 1, channels, Mat(), gray_hist, 1, histSize, histRange, uniform, accumulate);

	
	

	//04��һ��
	int hist_h = 400;
	int scale = 2;
	int hist_w = size * scale;
	normalize(gray_hist, gray_hist, 0, hist_h, NORM_MINMAX);

	//05��ͼ
	Mat hist(hist_h, hist_w, CV_8UC3, Scalar::all(0));
	for (int i = 1; i < size; i++)
	{
		rectangle
		(
			hist,
			Point(scale * (i - 1), cvRound(hist_h - 0)),
			Point(scale * i, cvRound(hist_h - gray_hist.at<float>(i - 1, 0))),
			Scalar(255,0,0),
			2
		);

	}
	imshow("hist", hist);
	waitKey(0);
	return 0;
}

