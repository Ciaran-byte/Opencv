#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{

	//��1������ԭʼͼ��Mat��������   

	Mat m = imread("1.jpg");
	Mat mid, dst;
	//��2�����б�Ե����ת��Ϊ�Ҷ�ͼ
	cvtColor(m, mid, COLOR_BGRA2GRAY);
	GaussianBlur(mid, dst, Size(9, 9), 0, 0);
	Canny(dst, dst, 50, 200, 3);
	imshow("dst", dst);

	//��3�����л����߱任
	vector<Vec4f> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180,80,0);
	//��4��������ͼ�л��Ƴ�ÿ���߶�

	
	Point pt1, pt2;
	for (int i = 0; i < lines.size(); i++)
	{
		
		Vec4f l = lines[i];
		line(m, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0));



	}


	//��5����ʾԭʼͼ  
	imshow("m", m);

	//��6����Ե�����ͼ 


	//��7����ʾЧ��ͼ  


	waitKey(0);


	return 0;
}

