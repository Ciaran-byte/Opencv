#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	//获取图片和logo
	Mat srcImg = imread("dota.jpg");
	Mat logo = imread("dota_logo.jpg",0);
	

	//分离蓝色通道
	vector<Mat> channels;
	split(srcImg, channels);
	Mat blue = channels.at(0);
	

	//线性混合
	Mat ROI = blue(Rect(500, 250, logo.cols, logo.rows)); //线性混合注意两个问题（1）两个图片大小要一样（2）两个图片通道数要一样
	
	
	addWeighted(ROI, 1.0, logo, 0.5, 0, ROI);
	
	
	//合并通道
	merge(channels, srcImg);
	imshow("srcImg", srcImg);


	waitKey(0);

	return 0;
}




