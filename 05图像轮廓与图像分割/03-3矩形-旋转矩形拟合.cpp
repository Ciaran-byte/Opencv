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


	//03����Щ�γɵĵ�Ѱ�Ҿ��λ�����ת����
	Rect rt;
	rt = boundingRect(Points);
	
	
	RotatedRect rrt = minAreaRect(Points);
	
	
	//����ת���λ�������һ�ַ�������boxPoints���32S���͵�mat������polylines����
	
	Mat contour, boxPointsCov;
	boxPoints(rrt, contour);
	cout << contour<< endl;

	contour.assignTo(boxPointsCov, CV_32S);
	cout << boxPointsCov << endl;

	
	

	//04���ƾ��λ�����ת����
	
	rectangle(m, rt, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
	polylines(m, boxPointsCov, true, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2);
	//���������ͼ����Ҫ��ĵ㼯������CV_32S��ʽ��
	for (int i = 0; i < PointCount; i++)
	{
		circle(m, Points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1);
	}
	imshow("m", m);

	waitKey(0);

	return 0;
}

