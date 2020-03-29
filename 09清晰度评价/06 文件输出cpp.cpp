#include<iostream>
#include<opencv2/opencv.hpp>
#include "evaluate.h"
#include<fstream>
using namespace cv;
using namespace std;


int main()
{

	const int picture_num = 33;
	vector<double> Values;
	double time = 0;
	ofstream outfile("variance.txt", ios_base::app);

		

	for (int t = 1; t <= picture_num; t++)
	{

		//01����ͼƬ
		string name = "impulseNoise" + to_string(t) + ".jpg";
		Mat src = imread(name,0);
		resize(src, src, Size(1024,1024));
		double t1 = (double)getTickCount();
		//02 ���������ۺ���
		
		
		GaussianBlur(src, src, Size(3, 3), 0);	
		src = LightNormalize(src);
		
		double value = EnergyGradEvaluate(src);
		//03 ������
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		time += t1;
		cout << t << endl;

		

		Values.push_back(value);

		


	}
	
	//04���ƽ��ʱ��
	outfile << time / picture_num << "\t";
	
	
	//05 ���������
	double s = 0;
	double s1;
	for (int i = 1; i < picture_num - 1; i++)
	{
		s1 = (abs(2 * Values[i] - Values[i - 1] - Values[i + 1])) / 2;
		s += s1;
	}
	s = s / (picture_num - 2);
	outfile <<  s << "\t";
	//06 �����һ�����������
	normalize(Values, Values, 0, 100, NORM_MINMAX);
	for (int i = 0; i < picture_num; i++)
	{
		outfile << Values[i];
		if (i != picture_num-1)
		{
			outfile << "\t";
		}
		else
		{
			outfile << "\n";
		}
	}
	

	
	
	return 0;
}

