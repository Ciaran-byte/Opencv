#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


int g_ContrastValue;
int g_BrightValue;
Mat g_srcImg, g_dstImg;

void Trackbar(int, void*)
{
	g_dstImg = g_srcImg.clone();
	MatIterator_<Vec3b> it = g_dstImg.begin<Vec3b>();
	MatIterator_<Vec3b> end = g_dstImg.end<Vec3b>();
	for (; it != end; it++)
	{
		for (int c = 0; c < 3; c++)
		{
			(*it)[c] = saturate_cast<uchar>((*it)[c]*g_ContrastValue*0.01+g_BrightValue);
		}
	}
	imshow("a", g_dstImg);
}

int main()
{

	//读取图片
	g_srcImg = imread("r.jpg");
	if (!g_srcImg.data)
	{
		cout << "图片无法读取！" << endl;
		return -1;
	}
	g_ContrastValue = 70;
	g_BrightValue = 20;
	
	namedWindow("a", WINDOW_AUTOSIZE);
	
	
	createTrackbar("对比度", "a", &g_ContrastValue, 300, Trackbar);
	createTrackbar("亮度度", "a", &g_BrightValue, 200, Trackbar);

	Trackbar(g_ContrastValue, 0);


	
	
	
	waitKey(0);


	return 0;
}

