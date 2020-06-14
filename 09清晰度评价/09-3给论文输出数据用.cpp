#include<iostream>
#include<opencv2/opencv.hpp>
#include"EvaluateClass.h"
using namespace std;
using namespace cv;
int main()
{
	double t0 = (double)getTickCount();
	double t1;
	//01��ʼ������
	bool rst = false;  //�����ж���ɽ�����Ƿ������������
	int step = 11;     //ÿ�������Ĳ�����������������Сֵʱ����Ϊ���������յ�
	int t = 3;         //�������������ĵ�һ��ͼƬ
	int symbol = 1;     //�����������Ƿ��������ı�־���������˼�ֵ���Ժ�ʼ��������
	double minStep = 1;  //��������С����
	const int PictureNum = 33; //ģ��ͼƬ�������

	//02 ����ģ��ͼƬ��ĻҶ�ͼ
	string name = "impulseNoise" + to_string(t) + ".jpg";
	Mat src = imread(name, 0);
	//������
	if (!src.data)return -1;

	//03 ����������������

	EnergyGradClass Eng(src);


	//04����
	//04-1 �����ĳ�ֵ
	double value0 = dstEvaluate(Eng);
	double value1;
	std::cout << "ͼƬ���" << t << endl;
	std::cout << "����ֵ" << value0 << endl;
	t1 = ((double)getTickCount() - t0) / getTickFrequency();
	cout << "�Խ�ʱ��" << t1*1000 << endl;
	cout << endl;
	while (!rst)
	{
		
		//04-2 �����������ƶ�
		t += symbol * step;
		if (t > PictureNum)t = PictureNum;
		if (t < 1)t = 1;

		//04-3 �����ʼֵ
		name = "picture" + to_string(t) + ".jpg";
		src = imread(name, 0);
		//������
		if (!src.data)return -1;

		Eng.reset(src);


		value1 = dstEvaluate(Eng);

		std::cout << "ͼƬ���" << t << endl;
		std::cout << "����ֵ" << value1 << endl;
		t1 = ((double)getTickCount() - t0) / getTickFrequency();
		cout << "�Խ�ʱ��" << t1*1000 << endl;
		cout << endl;

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
		
	}

	//05 ������Ľ��
	std::cout << (t + 1 * symbol) << endl;
	return 0;
}