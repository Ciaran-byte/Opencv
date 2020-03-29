#include<iostream>
#include<opencv2/opencv.hpp>
#include "evaluate.h"
using namespace cv;
using namespace std;
int main()
{
	//01��ʼ������
	bool rst = false;  //�����ж���ɽ�����Ƿ������������
	int step = 11;     //ÿ�������Ĳ�����������������Сֵʱ����Ϊ���������յ�
	int t = 3;         //�������������ĵ�һ��ͼƬ
	int symbol = 1;     //�����������Ƿ��������ı�־���������˼�ֵ���Ժ�ʼ��������
	double minStep = 1;  //��������С����
	const int PictureNum = 33; //ģ��ͼƬ�������

	//02 ����ģ��ͼƬ��ĻҶ�ͼ
	string name = "GaussianNoise" + to_string(t) + ".jpg";  
	Mat src = imread(name,0);
	//������
	if (!src.data)return -1;
	
	//03 ͼƬԤ����
	
	//03-1 �߶ȱ任����Сԭͼ�ߴ������������ٶ�
	//resize(src, src, Size(1024, 1024));
	resize(src, src, Size(512, 512));
	//03-2 ��˹�˲�������㷨������������
	GaussianBlur(src, src, Size(3, 3), 0);
	//03-3 ���ȹ�һ��������������ʱ�䣬���ͼƬ�������Ȳ��䣬���Բ�ʹ��
	src = LightNormalize(src);


	//04����
	//04-1 �����ĳ�ֵ
	double value0 = EnergyGradEvaluate(src);
	double value1;

	while (!rst)
	{
		double t1 = (double)getTickCount();
		//04-2 �����������ƶ�
		t += symbol * step;
		if (t > PictureNum)t = PictureNum;
		if (t < 1)t = 1;

		//04-3 �����ʼֵ
		name = "picture" + to_string(t) + ".jpg";
		src = imread(name,0);
		//������
		if (!src.data)return -1;
		//�߶ȱ任
		resize(src, src, Size(512, 512));
		//��˹�˲�
		GaussianBlur(src, src, Size(3, 3), 0);
		//���ȹ�һ��
		src = LightNormalize(src);
		value1 = EnergyGradEvaluate(src);



		//04-4�����ж�ֵ��С�仯������ж����������Ͳ���
		//��һ��ֵ����һ��ֵС��ʱ��˵�����˼�ֵ����
		if (value1 <= value0)
		{
			//ÿ����������������
			step = step / 2;
			//��������
			symbol = -symbol;
		}
		//�ƽ���ֵ
		value0 = value1;

		//04��ֹ�����ж�
		if (step < 1)
		{
			rst = true;
		}
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl;
	}

	//05 ������Ľ��
	cout << (t + 1 * symbol) << endl;
	return 0;
}