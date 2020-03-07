#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	//01 ȡ����׼ͼƬ�Ͳ���ͼƬ
	Mat base, baseHsv;
	

	base = imread("hand.jpg");
	

	//02 ת��ɫ�ʿռ�
	cvtColor(base, baseHsv, COLOR_BGR2HSV);
	

	//03 ���ò���
	Mat histBase;
	const int channels[] = { 0,1 };

	int hSize = 50;
	int sSize = 60;
	const int histSize[] = { hSize,sSize };

	float hRange[] = { 0,180 };
	float sRange[] = { 0,255 };
	const float* histRange[] = { hRange,sRange };

	bool uniform = true;
	bool accumulate = false;

	//04 ����ֱ��ͼ
	calcHist(&baseHsv, 1, channels, Mat(), histBase, 2, histSize, histRange, uniform, accumulate);
	
	//05 ֱ��ͼ��һ��--��������ܹ��鿴�ķ���ͶӰͼ
	
	normalize(histBase, histBase, 0, 255, NORM_MINMAX);
	imshow("h", histBase);
	
	//06�����������Ƶ�ͼƬ
	Mat backProj;
	Mat baseWarp ;
	Mat baseWarpHsv;
	Mat warp = getRotationMatrix2D(Point(0, 0), 30, 1);
	warpAffine(base, baseWarp, warp, base.size());

	
	cvtColor(baseWarp, baseWarpHsv, COLOR_BGR2HSV);

	//07����ͶӰ
	calcBackProject(&baseWarpHsv, 1, channels, histBase, backProj, histRange, 1, true);

	//08�鿴ͼ��
	imshow("backProj", backProj);

	waitKey(0);
	return 0;
}

