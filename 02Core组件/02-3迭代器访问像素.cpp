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

	switch (channel)
	{
		//处理单通道的灰色图
	case 1:
	{
		MatIterator_<uchar> it, end;//创建迭代器
	for (it = dstImg.begin<uchar>(), end = dstImg.end<uchar>(); it != end; it++)
	{
		(*it) = table[(*it)];
	}
	break;
	}
	//处理三通道的彩色图
	case 3:
	{
		cv::Mat_<cv::Vec3b>::iterator it = dstImg.begin<Vec3b>();//创建迭代器
		cv::Mat_<cv::Vec3b>::iterator end = dstImg.end<Vec3b>();
		for (; it != end; it++)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];

		}
		break;
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