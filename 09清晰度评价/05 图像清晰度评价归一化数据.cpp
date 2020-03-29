#include<iostream>
#include<opencv2/opencv.hpp>
#include "evaluate.h"
using namespace cv;
using namespace std;


int main()
{

	const int picture_num = 33;
	vector<double> Values;
	double time=0;

	for (int t = 1; t <= picture_num; t++)
	{
		
		//01����ͼƬ
		string name = "impulseNoise" + to_string(t) + ".jpg";
		Mat src = imread(name);
		resize(src, src, Size(512, 512));
		double t1 = (double)getTickCount();
		//02 ���������ۺ���
		GaussianBlur(src, src, Size(3, 3), 0);
		double value = EnergyGradEvaluate(src);
		//03 ������
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		time += t1;
		cout << t << endl;

		//cout << value << endl;

		Values.push_back(value);
		
		//cout << t1 << endl << endl;
		

	}
	//04���ƽ��ʱ��
	cout << endl;
	cout << "ƽ��ÿ��ͼƬ��ʱ" << time / picture_num << endl;
	cout << endl;
	//05 ���������
	double s = 0;
	double s1;
	for (int i = 1; i < picture_num - 1; i++)
	{
		s1 = (abs(2 * Values[i] - Values[i - 1] - Values[i + 1])) / 2;
		s += s1;
	}
	s = s / (picture_num - 2);
	cout << "������ֵ" << s << endl;
	//06 �����һ�����������
	normalize(Values, Values, 0, 100, NORM_MINMAX);
	for (int i = 0; i < picture_num; i++)
	{
		cout <<"��"<<i+1<<"ͼƬ��������Ϊ:  "<< Values[i] << endl;
	}
	cout << endl;
	
	
	
	return 0;
}

