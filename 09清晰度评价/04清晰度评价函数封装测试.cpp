#include<iostream>
#include<opencv2/opencv.hpp>
#include "evaluate.h"
using namespace cv;
using namespace std;


int main()
{
	
	const int picture_num = 33;
	
	for (int t = 1; t <= picture_num; t++)
	{
		double t1 = (double)getTickCount();
		//01读入图片
		string name = "picture" + to_string(t) + ".jpg";
		Mat src = imread(name);

		//02 清晰度评价函数

		double value = TenenGradEvaluate(src);
		//03 输出结果


		cout << value << endl;
		

		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
		
	}
	
	
	return 0;
}

