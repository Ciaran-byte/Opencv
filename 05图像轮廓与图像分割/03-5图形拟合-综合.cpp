#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat src, dst;

	//01�ҶȻ�
	src = imread("1.jpg", 0);
	imshow("src", src);

	//02�˲�
	blur(src, dst, Size(3, 3));
	//GaussianBlur(src, dst, Size(3, 3), 0);
	//dst = src.clone();
	imshow("dst1", dst);

	//03��ֵ��



	Canny(dst, dst, 100, 200, 3);
	imshow("dst2", dst);

	//04��������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//05���ж������ϡ�Բ����Ϻ;�����ϣ������Ҫ����洢��
	vector<vector<Point>> polyContours(contours.size());
	vector<Rect> rt(contours.size());
	vector<Point2f> center(contours.size());
	vector<float> radius(contours.size());
	vector<double>epsilion(contours.size());

	

	//05��ȡ��������ͼ
	Mat drawing = Mat::zeros(dst.size(), CV_8UC3);
	RNG rng(12345);
	for (int i = 0; i < contours.size(); i++)
	{
		//��ȡ����
		epsilion[i] = 0.01 * arcLength(contours[i], true);
		approxPolyDP(contours[i], polyContours[i], epsilion[i], true);
		rt[i]=boundingRect(contours[i]);
		minEnclosingCircle(contours[i], center[i], radius[i]);


		//��ͼ
		
		drawContours(drawing,polyContours , i, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, hierarchy, 0, Point());
		circle(drawing, center[i], radius[i], Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
		rectangle(drawing, rt[i], Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
	
	}
	imshow("dst", drawing);

	//08��������ͳ���
	
	waitKey(0);

	return 0;
}

