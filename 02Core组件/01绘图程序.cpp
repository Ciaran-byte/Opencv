#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat m = imread("1.png",0);
	Mat table(1,256,CV_8UC1);
	uchar* p = table.data;
		for (int i = 0; i < 256; i++)
	{
			p[i] = i / 10 * 10;
			
	}

		Mat m2;
		imshow("a", m);
		LUT(m, table, m2);
		imshow("b", m2);
	
		waitKey(0);
	
	
	
	return 0;
}

