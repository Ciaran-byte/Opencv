#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{


	Mat m = imread("1.jpg");

	m = m(Rect(0, 0, m.cols & -2, m.rows & -2));
	if (!m.data)return false;
	Mat g0,g1, l;


	//高斯金字塔
	pyrDown(m, g0);
	pyrUp(g0, g1);
	imshow("c", m);
	imshow("a", g0);
	imshow("b", g1);

	//拉普拉斯金字塔
	absdiff(m, g1, l);
	imshow("d", l);





	waitKey(0);
	return 0;
}


