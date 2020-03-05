#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int main()
{
	//01创建一张图
	Mat m = Mat::zeros(600, 600, CV_8UC3);

	//02随机绘制0-103个点
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


	//03给这些点进行直线拟合

	Vec4f ln;
	fitLine(Points,ln, 2, 0, 0.01, 0.01); //最后两个参数表示方向和距离上的精度，一般都取0.01


	//04绘制点和拟合的直线
	//使用y=k(x-x0)+y0的方法计算边界点
	double k = ln[1] / ln[0];//计算斜率=dy/dx
	Point p1, p2;//利用返回的直线角度和直线上一点绘制直线，这两个点都是边界点
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

