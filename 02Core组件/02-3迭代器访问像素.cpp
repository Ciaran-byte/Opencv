#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void colorReduce(Mat& srcImg, Mat& dstImg, int dividedValue)
{
	//�������ұ�
	char table[256];
	for (int i = 0; i < 256; i++)
	{
		table[i] = i / dividedValue * dividedValue;
	}
	//��¼ͼƬ����
	int row = srcImg.rows;
	int col = srcImg.cols;
	int channel = srcImg.channels();
	srcImg.copyTo(dstImg);

	switch (channel)
	{
		//����ͨ���Ļ�ɫͼ
	case 1:
	{
		MatIterator_<uchar> it, end;//����������
	for (it = dstImg.begin<uchar>(), end = dstImg.end<uchar>(); it != end; it++)
	{
		(*it) = table[(*it)];
	}
	break;
	}
	//������ͨ���Ĳ�ɫͼ
	case 3:
	{
		cv::Mat_<cv::Vec3b>::iterator it = dstImg.begin<Vec3b>();//����������
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