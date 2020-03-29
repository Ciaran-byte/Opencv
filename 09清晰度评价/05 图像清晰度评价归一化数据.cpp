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
		
		//01读入图片
		string name = "impulseNoise" + to_string(t) + ".jpg";
		Mat src = imread(name);
		resize(src, src, Size(512, 512));
		double t1 = (double)getTickCount();
		//02 清晰度评价函数
		GaussianBlur(src, src, Size(3, 3), 0);
		double value = EnergyGradEvaluate(src);
		//03 输入结果
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		time += t1;
		cout << t << endl;

		//cout << value << endl;

		Values.push_back(value);
		
		//cout << t1 << endl << endl;
		

	}
	//04输出平均时间
	cout << endl;
	cout << "平均每张图片耗时" << time / picture_num << endl;
	cout << endl;
	//05 输出灵敏度
	double s = 0;
	double s1;
	for (int i = 1; i < picture_num - 1; i++)
	{
		s1 = (abs(2 * Values[i] - Values[i - 1] - Values[i + 1])) / 2;
		s += s1;
	}
	s = s / (picture_num - 2);
	cout << "灵敏度值" << s << endl;
	//06 输出归一化后的清晰度
	normalize(Values, Values, 0, 100, NORM_MINMAX);
	for (int i = 0; i < picture_num; i++)
	{
		cout <<"第"<<i+1<<"图片的清晰度为:  "<< Values[i] << endl;
	}
	cout << endl;
	
	
	
	return 0;
}

