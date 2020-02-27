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
	imshow("�������˲���", g_dst1);

}

void track_blur(int, void*)
{
	blur(g_src, g_dst2,Size(g_blur, g_blur));
	imshow("����ֵ�˲���", g_dst2);
}


void track_gaussian(int, void*)
{
	GaussianBlur(g_src, g_dst3, Size(g_gaussian*2+1,g_gaussian*2+1), (g_gaussian*2+1) /3.0, (g_gaussian*2+1) /3.0);
	imshow("����˹�˲���", g_dst3);
}




int main()
{

	g_src = imread("1.jpg");
	if (!g_src.data)return false;
	g_dst1 = g_src.clone();
	g_dst2 = g_src.clone();
	g_dst3 = g_src.clone();


	namedWindow("��ԭʼͼƬ��");
	imshow("��ԭʼͼƬ��", g_src);

	namedWindow("�������˲���");
	namedWindow("����ֵ�˲���");
	namedWindow("����˹�˲���");

	track_boxblur(g_boxblur,0);
	track_blur(g_blur, 0);
	track_gaussian(g_gaussian, 0);



	createTrackbar("�����˲�", "�������˲���", &g_boxblur, 40, track_boxblur);
	createTrackbar("��ֵ�˲�", "����ֵ�˲���", &g_blur, 40, track_blur);
	createTrackbar("��˹�˲�", "����˹�˲���", &g_gaussian, 40, track_gaussian);



	



	waitKey(0);
	return 0;
}



