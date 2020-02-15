


//����һ���ǳ��򵥵��Ҳ�ͬ����Ϸ���������֣�û���κμ�������
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int count1 = 1;
int count2 = 1;
int count3 = 1;
int count4 = 1;
int count5 = 1;
Mat a, b;
void DrawRect(Mat& m,Rect r)
{
	Scalar s(255, 0, 255);//�൱�ڶ�����ͨ������ɫ����ͨ���ֱ���255,0,255
	rectangle(m, r, s);//�ö������ɫs����ͼ��m�л��ƾ���g_rect
}

void Callback(int event, int x, int y, int flags, void* param)
{
	
	

	switch (event)
	{
	case(EVENT_LBUTTONDOWN):
		if (x >= 13 && x <= 45 && y >= 48 && y <= 71&&count1==1)
		{
			Rect r(13, 48, 32, 23);
			count1 = 0;
			DrawRect(a, r);
			DrawRect(b, r);
		}
		if (x >= 115 && x <= 136 && y >= 63 && y <= 70 && count2 == 1)
		{
			Rect r(115, 63, 20, 10);
			count2 = 0;
			DrawRect(a, r);
			DrawRect(b, r);
		}
		if (x >= 53 && x <= 93 && y >= 245 && y <= 263 && count3 == 1)
		{
			Rect r(53, 245, 40, 20);
			count3 = 0;
			DrawRect(a, r);
			DrawRect(b, r);
		}
		if (x >= 170 && x <= 195 && y >= 130 && y <= 155 && count4 == 1)
		{
			Rect r(170, 130, 25, 25);
			count4 = 0;
			DrawRect(a, r);
			DrawRect(b, r);
		}

		if (x >= 206 && x <= 220 && y >= 40 && y <= 60 && count5 == 1)
		{
			Rect r(206, 40, 14, 20);
			count5 = 0;
			DrawRect(a, r);
			DrawRect(b, r);
		}


		break;
	}
}
int main()
{
	namedWindow("a");
	namedWindow("b");
	
	
	 a = imread("compare_a.jpg");
	 b = imread("compare_b.jpg");
	imshow("a", a);
	imshow("b", b);

	
	
	setMouseCallback("a", Callback);
	setMouseCallback("b", Callback);
	while (1)
	{
		imshow("a", a);
		imshow("b", b);
		if (count1 + count2 + count3 + count4 + count5 == 0)break;
		if (waitKey(10) == 27)break;//��ESC���˳�
	}

	waitKey(1000);
	cout << "��ϲ��" << endl;
	
	return 0;
}
