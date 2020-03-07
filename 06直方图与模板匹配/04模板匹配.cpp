#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	
	//01����ͼƬ
	Mat src = imread("src.jpg");
	Mat tmp = imread("template.jpg");
	
	//02�������ͼ��
	int dst_cols = src.cols - tmp.cols + 1;
	int dst_rows = src.rows - tmp.rows + 1;
	Mat dst(dst_cols, dst_rows, CV_32F);

	//03ƥ��ͱ�׼��
	int matchMethod = TM_SQDIFF;
	matchTemplate(src, tmp, dst, matchMethod);
	normalize(dst, dst, 0, 1, NORM_MINMAX);

	//04ͨ��minMaxloc��λ���ƥ��λ��

	double minValue;
	double maxValue;
	Point minLocation;
	Point maxLocation;
	Point matchPoint;

	minMaxLoc(dst, &minValue, &maxValue, &minLocation, &maxLocation);
	if (matchMethod == TM_SQDIFF || TM_SQDIFF_NORMED)
	{
		matchPoint = minLocation;
	}
	else
	{
		matchPoint = maxLocation;
	}

	//05���ƾ���
	rectangle(src, matchPoint, Point(matchPoint.x + tmp.cols, matchPoint.y + tmp.rows), Scalar(0, 0, 255));
	imshow("src", src);
	rectangle(dst, matchPoint, Point(matchPoint.x + tmp.cols, matchPoint.y + tmp.rows), Scalar(0, 0, 255));
	imshow("dst", dst);
	waitKey(0);
	return 0;
}

