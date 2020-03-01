#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{
	
	//��1������ԭʼͼ��Mat��������   
	
	Mat m = imread("1.jpg");
	Mat mid,dst;
	//��2�����б�Ե����ת��Ϊ�Ҷ�ͼ
	cvtColor(m, mid, COLOR_BGRA2GRAY);
	GaussianBlur(mid, dst, Size(9, 9), 0, 0);
	Canny(dst, dst, 50, 200,3);
	imshow("dst", dst);

	//��3�����л����߱任
	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 100);
	//��4��������ͼ�л��Ƴ�ÿ���߶�

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
	

	//��5����ʾԭʼͼ  
	imshow("m", m);

	//��6����Ե�����ͼ 
	

	//��7����ʾЧ��ͼ  


	waitKey(0);  
	
	
	return 0;
}

