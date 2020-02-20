#include<opencv2/opencv.hpp>
#include<iostream>



using namespace cv;
using namespace std;
int main()
{
	
	double t1 = (double)getTickCount();
	//������ֵ��
	uchar table[256];
	int dividedValue = 100;
	for (int i = 0; i < 256; i++)
	{
		table[i] = i / dividedValue * dividedValue;
	}

	//����ͼƬ
	Mat srcImg, lut, dstImg;
	srcImg = imread("1.png");

	//�������ұ�
	lut.create(1, 256, CV_8UC1); //���ұ�һ��ͨ���Ϳ��ԣ�������ͨ��ͼƬ��ʱ�򣬻������ͨ������װlut�Ĺ�����б任
	uchar* p = lut.data;
	for (int i = 0; i < 256; i++)
	{
		p[i] = table[i];
	}
	
	//���ұ���
	imshow("a", srcImg);
	LUT(srcImg, lut, dstImg);
	imshow("b", dstImg);

	 t1 = ((double)getTickCount()-t1)/getTickFrequency();
	 cout << t1 << endl;


	waitKey(0);
}