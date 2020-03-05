#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int main()
{
	//01����һ��ͼ
	Mat m = Mat::zeros(600, 600, CV_8UC3);

	//02�������0-103����
	int64 t = getTickCount();
	RNG rng(t);
	int PointCount = rng.uniform(3, 103);
	vector<Point> Points;
	Point p;
	for (int i = 0; i < PointCount; i++)
	{
		p.x = rng.uniform(m.cols / 4, m.rows * 3 / 4);
		p.y = rng.uniform(m.cols / 4, m.rows * 3 / 4);
		Points.push_back(p);

	}


	//03����Щ�����ֱ�����

	Vec4f ln;
	fitLine(Points,ln, 2, 0, 0.01, 0.01); //�������������ʾ����;����ϵľ��ȣ�һ�㶼ȡ0.01


	//04���Ƶ����ϵ�ֱ��
	//ʹ��y=k(x-x0)+y0�ķ�������߽��
	double k = ln[1] / ln[0];//����б��=dy/dx
	Point p1, p2;//���÷��ص�ֱ�߽ǶȺ�ֱ����һ�����ֱ�ߣ��������㶼�Ǳ߽��
	p1.x = 0;
	p1.y = k * (0 - ln[2]) + ln[3];

	p2.x = m.cols;
	p2.y = k * (m.cols - ln[2]) + ln[3];

	line(m, p1, p2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
	


	
	for (int i = 0; i < PointCount; i++)
	{
		circle(m, Points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1);
	}
	imshow("m", m);

	waitKey(0);

	return 0;
}

