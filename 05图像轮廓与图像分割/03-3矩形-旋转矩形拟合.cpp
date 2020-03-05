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


	//03给这些形成的点寻找矩形或者旋转矩形
	Rect rt;
	rt = boundingRect(Points);
	
	
	RotatedRect rrt = minAreaRect(Points);
	
	
	//把旋转矩形画出来的一种方法，用boxPoints变成32S类型的mat，再用polylines画出
	
	Mat contour, boxPointsCov;
	boxPoints(rrt, contour);
	cout << contour<< endl;

	contour.assignTo(boxPointsCov, CV_32S);
	cout << boxPointsCov << endl;

	
	

	//04绘制矩形或者旋转矩形
	
	rectangle(m, rt, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
	polylines(m, boxPointsCov, true, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
	//上面这个绘图函数要求的点集必须是CV_32S格式的
	for (int i = 0; i < PointCount; i++)
	{
		circle(m, Points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1);
	}
	imshow("m", m);

	waitKey(0);

	return 0;
}

