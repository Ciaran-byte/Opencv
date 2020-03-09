#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//01�ҶȻ�
	Mat src = imread("house.jpg");
	Mat gray;
	cvtColor(src, gray,COLOR_BGR2GRAY);

	//02׼������
	
	

	vector<Point> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	int maxNum =100;


	
	
	
		//03shi-tomasi�ǵ���



	goodFeaturesToTrack(gray, corners, maxNum, qualityLevel, minDistance, Mat(), blockSize,false,k);
	//04���ƽǵ�
	for (int i = 0; i < corners.size(); i++)
	{
		circle(src, corners[i], 3, Scalar(0, 0, 255), -1);
	}

	//05��ʾ
	imshow("src", src);

	waitKey(0);
	return 0;
}


