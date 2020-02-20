#include<opencv2/opencv.hpp>
#include<iostream>



using namespace cv;
using namespace std;
int main()
{
	
	double t1 = (double)getTickCount();
	//创建数值表
	uchar table[256];
	int dividedValue = 100;
	for (int i = 0; i < 256; i++)
	{
		table[i] = i / dividedValue * dividedValue;
	}

	//定义图片
	Mat srcImg, lut, dstImg;
	srcImg = imread("1.png");

	//创建查找表
	lut.create(1, 256, CV_8UC1); //查找表一个通道就可以，处理三通道图片的时候，会把三个通道都安装lut的规则进行变换
	uchar* p = lut.data;
	for (int i = 0; i < 256; i++)
	{
		p[i] = table[i];
	}
	
	//查找表函数
	imshow("a", srcImg);
	LUT(srcImg, lut, dstImg);
	imshow("b", dstImg);

	 t1 = ((double)getTickCount()-t1)/getTickFrequency();
	 cout << t1 << endl;


	waitKey(0);
}