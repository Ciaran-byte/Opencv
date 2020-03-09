#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//01灰度化
	Mat src = imread("house.jpg");
	Mat gray;
	cvtColor(src, gray,COLOR_BGR2GRAY);

	//02准备参数
	
	

	vector<Point> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	int maxNum =100;


	
	
	
		//03shi-tomasi角点检测



	goodFeaturesToTrack(gray, corners, maxNum, qualityLevel, minDistance, Mat(), blockSize,false,k);
	//04绘制角点
	for (int i = 0; i < corners.size(); i++)
	{
		circle(src, corners[i], 3, Scalar(0, 0, 255), -1);
	}

	//05显示
	imshow("src", src);

	waitKey(0);
	return 0;
}


