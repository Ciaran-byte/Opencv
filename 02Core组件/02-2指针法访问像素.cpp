#include<opencv2/opencv.hpp>
#include<iostream>



using namespace cv;
using namespace std;

void colorReduce(Mat& srcImg, Mat& dstImg, int dividedValue)
{
	//创建查找表
	char table[256];
	for (int i = 0; i < 256; i++)
	{
		table[i] = i / dividedValue * dividedValue;
	}
	//记录图片数据
	int row = srcImg.rows;
	int col = srcImg.cols;
	int channel = srcImg.channels();
	srcImg.copyTo(dstImg);

	//使用二重指针的方法访问像素
	for (int i = 0; i < row; i++)
	{
		uchar* p = dstImg.ptr<uchar>(i);  //ptr是mat类的一个模板函数，返回值是第i行的头指针，尖括号里放的是返回值类型
		for (int j = 0; j < col * channel; j++)
		{
			p[j] = table[p[j]];
		}
	}

}
int main()
{

	
	Mat srcImg, dstImg;
	
	srcImg = imread("1.png");
	srcImg.copyTo(dstImg);
	imshow("a", dstImg);
	colorReduce(srcImg, dstImg, 100);
	imshow("b", dstImg);

	
	waitKey(0);
}