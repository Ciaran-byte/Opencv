#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat g_src, g_dst;
int g_TrackbarNum=0;//��ʴ0������1
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
	imshow("Ч��ͼ", g_dst);
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
	
	
	//��ʾԭͼ
	g_src = imread("1.jpg");
	imshow("ԭͼ", g_src);
	namedWindow("Ч��ͼ", 1);

	g_dst = g_src.clone();
	Mat n = getStructuringElement(MORPH_RECT, Size(g_StructureSize * 2 + 1, g_StructureSize * 2 + 1), Point(-1, -1));
	dilate(g_src, g_dst, n);
	imshow("Ч��ͼ",g_dst);


	//ѡ��ʴ�����͵ĺ���
	createTrackbar( "��ʴ/����", "Ч��ͼ", &g_TrackbarNum, 1, Select);
	createTrackbar( "�ں˴�С", "Ч��ͼ", &g_StructureSize, 10, on_TrackbarSizeChange);

	waitKey(0);

	return 0;
}



