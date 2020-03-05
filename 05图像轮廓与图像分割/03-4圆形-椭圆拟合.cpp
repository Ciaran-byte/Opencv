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


	//03给这些形成的点寻找拟合圆形或者椭圆
	
	Point2f center;
	float radius;
	RotatedRect ep = fitEllipse(Points);
	minEnclosingCircle(Points, center, radius);
	

	

	




	//04绘制圆形或者椭圆
	ellipse(m, ep, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
	circle(m, center, radius, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
	for (int i = 0; i < PointCount; i++)
	{
		circle(m, Points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1);
	}
	imshow("m", m);

	waitKey(0);

	return 0;
}

