#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int main()
{
	//01����ͼ��
	Mat m = imread("poly.jpg");
	Mat dst;
	

	//02�Ҷ�ͼ
	cvtColor(m, dst, COLOR_BGR2GRAY);
	

	//03�˲�
	blur(dst, dst, Size(3, 3));
	

	//04��ֵ��
	threshold(dst, dst, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	

	//05Ѱ������
	Mat drawing = Mat::zeros(m.cols, m.rows, CV_8UC3);
	
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours,hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	//����findcontours�ҵ�������
	int b = getTickCount();
	RNG rg(b);
	
	Scalar color = Scalar(rg.uniform(0, 255), rg.uniform(0, 255), rg.uniform(0, 255));
	
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(drawing, contours, i,color , 4);
	}
	imshow("b", drawing);

	//06���þ���

	double epsilon = 0.02 * arcLength(contours[0],true);
	
	//07��������
	Mat drawing2 = m.clone();
	vector<Point> approxCurve;
	approxPolyDP(contours[0], approxCurve, epsilon, true);
	
	//08��������
	rg.next();
	color = Scalar(rg.uniform(0, 255), rg.uniform(0, 255), rg.uniform(0, 255));
	vector< vector<Point>> t = { approxCurve };
	drawContours(drawing2, t, -1, color, 4);
	cout << "!" << endl;
	imshow("a", drawing2);
	
	waitKey(0);

	return 0;
}

