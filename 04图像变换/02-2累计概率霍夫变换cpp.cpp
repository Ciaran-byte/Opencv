#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{

	//【1】载入原始图和Mat变量定义   

	Mat m = imread("1.jpg");
	Mat mid, dst;
	//【2】进行边缘检测和转化为灰度图
	cvtColor(m, mid, COLOR_BGRA2GRAY);
	GaussianBlur(mid, dst, Size(9, 9), 0, 0);
	Canny(dst, dst, 50, 200, 3);
	imshow("dst", dst);

	//【3】进行霍夫线变换
	vector<Vec4f> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180,80,0);
	//【4】依次在图中绘制出每条线段

	
	Point pt1, pt2;
	for (int i = 0; i < lines.size(); i++)
	{
		
		Vec4f l = lines[i];
		line(m, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0));



	}


	//【5】显示原始图  
	imshow("m", m);

	//【6】边缘检测后的图 


	//【7】显示效果图  


	waitKey(0);


	return 0;
}

