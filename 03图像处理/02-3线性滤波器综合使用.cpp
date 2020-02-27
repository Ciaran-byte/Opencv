#include<opencv2/opencv.hpp>
#include<stdio.h>

using namespace std;
using namespace cv;

Mat g_src, g_dst1, g_dst2, g_dst3;
int g_boxblur = 3;
int g_blur = 3;
int g_gaussian=3;


void track_boxblur(int, void*)
{

	boxFilter(g_src, g_dst1, -1, Size(g_boxblur, g_boxblur));
	imshow("【方框滤波】", g_dst1);

}

void track_blur(int, void*)
{
	blur(g_src, g_dst2,Size(g_blur, g_blur));
	imshow("【均值滤波】", g_dst2);
}


void track_gaussian(int, void*)
{
	GaussianBlur(g_src, g_dst3, Size(g_gaussian*2+1,g_gaussian*2+1), (g_gaussian*2+1) /3.0, (g_gaussian*2+1) /3.0);
	imshow("【高斯滤波】", g_dst3);
}




int main()
{

	g_src = imread("1.jpg");
	if (!g_src.data)return false;
	g_dst1 = g_src.clone();
	g_dst2 = g_src.clone();
	g_dst3 = g_src.clone();


	namedWindow("【原始图片】");
	imshow("【原始图片】", g_src);

	namedWindow("【方框滤波】");
	namedWindow("【均值滤波】");
	namedWindow("【高斯滤波】");

	track_boxblur(g_boxblur,0);
	track_blur(g_blur, 0);
	track_gaussian(g_gaussian, 0);



	createTrackbar("方框滤波", "【方框滤波】", &g_boxblur, 40, track_boxblur);
	createTrackbar("均值滤波", "【均值滤波】", &g_blur, 40, track_blur);
	createTrackbar("高斯滤波", "【高斯滤波】", &g_gaussian, 40, track_gaussian);



	



	waitKey(0);
	return 0;
}



