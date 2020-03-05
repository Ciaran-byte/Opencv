
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	
	
	//01灰度化
	Mat src = imread("tree.jpg");
	Mat src_gray;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	imshow("src", src);


	//02二值化
	Mat bin;
	threshold(src_gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	//imshow("bin", bin);

	//03去噪点
	Mat bin_close;
	Mat kernal = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(bin, bin_close, MORPH_CLOSE, kernal, Point(-1, -1), 1);
	//imshow("bin_close", bin_close);

	//04距离变换
	Mat distance;
	distanceTransform(bin_close, distance, DIST_L1, 3, 5);


	//imshow("dis", distance); 
	//距离变换之后的颜色似乎与原来是一样的，这是因为，返回值的色彩空间是浮点数类型的，大于1默认就是白色，所以，经过归一化
	//范围进入0-1之后，才能够看到差别
	
	
	
	//05归一化
	normalize(distance, distance, 1, 0, CV_MINMAX);
	//imshow("dis", distance);
	
	
	//06二值化
	Mat dis_bin;
	threshold(distance, dis_bin, 0.4, 1, THRESH_BINARY);
	//imshow("dis_bin", dis_bin);


	//07寻找边界
	//fincontours必须是8位单通道的，而距离变换返回的是个CV_32S1类型的，不兼容，必须做图像深度转换
	dis_bin.convertTo(dis_bin, CV_8UC1);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dis_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	
	


	//08填充边界
	
	Mat mask = Mat::zeros(src.rows, src.cols, CV_32SC1);

	
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(mask, contours, i, Scalar::all(i+1),-1);
		
	}

	circle(mask, Point(10, 10), 3, Scalar::all(255), -1); //不填充这里，图像会少一个图案

	//imshow("mask", mask); //mask必须是CV_32S类型的并且是单通道的

	//09分水岭算法
	watershed(src, mask);


	

	//10色彩填充
	vector<Vec3b> colors;
	Vec3b s;
	int64 t = getTickCount();
	RNG rng(t);
	for (int i = 0; i < contours.size(); i++)
	{
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);

		s = Vec3b(b,g,r);
		colors.push_back(s);
	}

	Mat water_mask(mask.size(),CV_8UC3);
	for (int i = 0; i < water_mask.rows; i++)
	{

		for (int j = 0; j < water_mask.cols; j++)
		{
			int index = mask.at<int>(i, j);
			if (index > 0 && index <= contours.size())
			{
				water_mask.at<Vec3b>(i, j) = colors[index - 1];
					
			}
			else
			{
				water_mask.at<Vec3b>(i, j) = Vec3b(0,0,0);
			}
		}
	}
	imshow("water_mask", water_mask);



	waitKey(0);
	return 0;
}

