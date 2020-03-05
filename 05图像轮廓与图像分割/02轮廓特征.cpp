#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src, dst;

	//01�ҶȻ�
	src = imread("1.jpg",0);
	imshow("src",src);

	//02�˲�
	blur(src, dst, Size(3, 3));
	//GaussianBlur(src, dst, Size(3, 3), 0);
	//dst = src.clone();
	imshow("dst1", dst);

	//03��ֵ��
	
	
	
	Canny(dst, dst, 100, 200, 3);
	imshow("dst2", dst);

	//04��������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours,hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//05�����
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	//06�������ľ�
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}

	//07��������
	Mat drawing=Mat::zeros(dst.size(),CV_8UC3);
	RNG rng(12345);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color,2,8,hierarchy,0,Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
	imshow("dst", drawing);

	//08��������ͳ���
	for (int i = 0; i < contours.size(); i++)
	{
		cout << "m00��" << mu[i].m00 << endl;
		cout << "�����" << contourArea(contours[i], false) << endl;
		cout << "����:" << arcLength(contours[i], true);
		cout << endl<<endl;
	}
	waitKey(0);

	return 0;
}

