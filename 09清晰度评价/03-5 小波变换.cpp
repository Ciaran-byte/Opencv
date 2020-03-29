#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	//01 设定参数
	const int picture_num = 33;
	float value;
	Mat kernal = (
		Mat_<double>(3, 3) <<
		-1.0 / 16, -1.0 / 8, -1.0 / 16,
		-1.0 / 8, 3.0 / 4, -1.0 / 8, 
		-1.0 / 16, -1.0 / 8, -1.0 / 16
		);

	for (int t = 1; t <= picture_num; t++)
	{
		double t1 = (double)getTickCount();

		//02 读入尺度金字塔
		string name = "picture" + to_string(t) + ".jpg";
		Mat m = imread(name);
		cvtColor(m, m, COLOR_BGR2GRAY);
		
		//03 图像与高通滤波器kernal卷积
		Mat dst;
		
		filter2D(m, dst, CV_32F, kernal);
		

		//04 计算评价值
		value = 0;
		for (int i = 0; i < dst.rows; i++)
		{
			for (int j = 0; j < dst.cols; j++)
			{
				value += pow((dst.at<float>(i, j)), 2);
			}
		}
		value = log(value+1);
		cout << value << endl;
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}
	return 0;
}
