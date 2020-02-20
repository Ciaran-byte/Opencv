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
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				dstImg.at<uchar>(i, j) = table[dstImg.at<uchar>(i, j)];
			}
		}
		break;
	}
	//处理三通道的彩色图
	case 3:
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				dstImg.at<Vec3b>(i, j)[0] = table[dstImg.at<Vec3b>(i, j)[0]]; 
				dstImg.at<Vec3b>(i, j)[1] = table[dstImg.at<Vec3b>(i, j)[1]];
				dstImg.at<Vec3b>(i, j)[2] = table[dstImg.at<Vec3b>(i, j)[2]];
			}
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