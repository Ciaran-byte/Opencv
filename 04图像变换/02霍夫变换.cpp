#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{
	
	//【1】载入原始图和Mat变量定义   
	
	Mat m = imread("1.jpg");
	Mat mid,dst;
	//【2】进行边缘检测和转化为灰度图
	cvtColor(m, mid, COLOR_BGRA2GRAY);
	GaussianBlur(mid, dst, Size(9, 9), 0, 0);
	Canny(dst, dst, 50, 200,3);
	imshow("dst", dst);

	//【3】进行霍夫线变换
	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 100);
	//【4】依次在图中绘制出每条线段

	float rho, theta, a, b, x0,y0;
	Point pt1, pt2;
	for (int i = 0; i < lines.size(); i++)
	{
		rho = lines[i][0];
		theta = lines[i][1];
		a = cos(theta);
		b = sin(theta);
		x0 = rho * a;
		y0 = rho * b;

		pt1.x = cvRound(x0 + 1000 * b);
		pt1.y = cvRound(y0 - 1000 * a);
		
		pt2.x = cvRound(x0 - 1000 * b);
		pt2.y = cvRound(y0 + 1000 * a);

		line(m, pt1, pt2, Scalar(55, 100, 195),1);
		


	}
	

	//【5】显示原始图  
	imshow("m", m);

	//【6】边缘检测后的图 
	

	//【7】显示效果图  


	waitKey(0);  
	
	
	return 0;
}

