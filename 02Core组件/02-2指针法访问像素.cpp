#include<opencv2/opencv.hpp>
#include<iostream>



using namespace cv;
using namespace std;

void colorReduce(Mat& srcImg, Mat& dstImg, int dividedValue)
{
	//�������ұ�
	char table[256];
	for (int i = 0; i < 256; i++)
	{
		table[i] = i / dividedValue * dividedValue;
	}
	//��¼ͼƬ����
	int row = srcImg.rows;
	int col = srcImg.cols;
	int channel = srcImg.channels();
	srcImg.copyTo(dstImg);

	//ʹ�ö���ָ��ķ�����������
	for (int i = 0; i < row; i++)
	{
		uchar* p = dstImg.ptr<uchar>(i);  //ptr��mat���һ��ģ�庯��������ֵ�ǵ�i�е�ͷָ�룬��������ŵ��Ƿ���ֵ����
		for (int j = 0; j < col * channel; j++)
		{
			p[j] = table[p[j]];
		}
	}

}
int main()
{

	
	Mat srcImg, dstImg;
	
	srcImg = imread("1.png");
	srcImg.copyTo(dstImg);
	imshow("a", dstImg);
	colorReduce(srcImg, dstImg, 100);
	imshow("b", dstImg);

	
	waitKey(0);
}