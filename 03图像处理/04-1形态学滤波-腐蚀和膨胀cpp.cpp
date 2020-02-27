#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat g_src, g_dst;
int g_TrackbarNum=0;//腐蚀0，膨胀1
int g_StructureSize=1;

void Process()
{
	g_dst = g_src.clone();
	Mat n=getStructuringElement(MORPH_RECT, Size(g_StructureSize*2+1, g_StructureSize*2+1), Point(-1, -1));
	if (g_TrackbarNum == 0)
	{
		dilate(g_src, g_dst, n);

	}
	else
	{
		erode(g_src, g_dst, n);
	}
	imshow("效果图", g_dst);
}


void Select(int, void*)
{
	Process();
}
void on_TrackbarSizeChange(int ,void*)
{
	Process();
}
int main()
{
	
	
	//显示原图
	g_src = imread("1.jpg");
	imshow("原图", g_src);
	namedWindow("效果图", 1);

	g_dst = g_src.clone();
	Mat n = getStructuringElement(MORPH_RECT, Size(g_StructureSize * 2 + 1, g_StructureSize * 2 + 1), Point(-1, -1));
	dilate(g_src, g_dst, n);
	imshow("效果图",g_dst);


	//选择腐蚀和膨胀的函数
	createTrackbar( "腐蚀/膨胀", "效果图", &g_TrackbarNum, 1, Select);
	createTrackbar( "内核大小", "效果图", &g_StructureSize, 10, on_TrackbarSizeChange);

	waitKey(0);

	return 0;
}



