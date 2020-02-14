#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//全局变量，滑动条
const int Max = 100;
int g_nowValue;
double alpha;
double beta;

//全局变量，图片
Mat m1, m2, m3;

void Track(int, void*)
{
	alpha = (double)g_nowValue / Max;
	beta = 1 - alpha;
	addWeighted(m1, alpha, m2, beta, 0.0, m3);
	imshow("1", m3);
}
int main()
{
	m1 = imread("1.jpg");
	m2 = imread("2.jpg");
	g_nowValue = 70;
	Track(g_nowValue,0);

	namedWindow("1");
	string TrackName = "透明度100";
		
	createTrackbar(TrackName, "1", &g_nowValue, Max, Track);
	waitKey(0);


	return 0;
}

