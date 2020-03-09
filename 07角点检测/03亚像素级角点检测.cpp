#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	//01�ҶȻ�
	Mat src = imread("house.jpg");
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	//02׼������



	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	int maxNum = 100;





	//03shi-tomasi�ǵ���



	goodFeaturesToTrack(gray, corners, maxNum, qualityLevel, minDistance, Mat(), blockSize, false, k);
	
	//shi-tomasi���ƽǵ�
	for (int i = 0; i < corners.size(); i++)
	{
		circle(src, corners[i], 3, Scalar(0, 0, 255), -1);
	}

	//04 �����ؼ���Ľǵ���


	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
	cornerSubPix(gray, corners, winSize, zeroZone, criteria);

	//04����ǵ�
	
	for (int i = 0; i < corners.size(); i++)
	{
		cout << "��ȷ����[" << i << "]:(" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
	
	//05��ʾshi-tomasi�ǵ�
	imshow("src", src);

	waitKey(0);
	return 0;
}

