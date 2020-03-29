#include<iostream>
#include<opencv2/opencv.hpp>
#include "evaluate.h"
using namespace std;
using namespace cv;
int main()
{
	//01��ʼ������
	bool rst = false;
	int step = 11;
	int t = 3;
	int symbol = 1;
	double minStep = 1;
	const int PictureNum = 33;
	
	//02 ��ʼ��ͼƬ
	string name = "picture" + to_string(t) + ".jpg";
	Mat src = imread(name);
	
	resize(src, src, Size(1024, 1024));
	
	double value0 = VarianceEvaluate(src);
	double value1;

	//03 ����
	while (!rst)
	{
		//03-1 �����������ƶ�
		t += symbol*step;
		if (t > PictureNum)t = PictureNum;
		if (t < 1)t = 1;

		//03-2 �����ʼֵ
		name = "picture" + to_string(t) + ".jpg";
		src = imread(name);
		resize(src, src, Size(512, 512));
		value1 = VarianceEvaluate(src);
		
		

		//03-3�����ж�ֵ��С�仯������ж����������Ͳ���
		//��һ��ֵ����һ��ֵС��ʱ��˵�����˼�ֵ����
		if (value1 <=value0)
		{
			//ÿ����������������
			step =step / 2;
			
			
			
			//��������
			symbol = -symbol;
		}
		//�ƽ���ֵ
		value0 = value1;
		
		//04��ֹ�����ж�
		if (step<1)
		{
			rst = true;
		}
		
	}
	cout << (t+1*symbol) << endl;
	return 0;
}

