
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;


void my_print()
{
	cout << "��ESC���˳�" << endl;
	cout << "��1���л���ɫͼ/�Ҷ�ͼ" << endl;
	cout << "��2����ʾ/������Ĥ����" << endl;
	cout << "��3���ָ�ԭʼͼ��" << endl;
	cout << "��4���շ�Χ��ˮ���" << endl;
	cout << "��5���̶���Χ��ˮ���" << endl;
	cout << "��6��������Χ��ˮ���" << endl;
	cout << "��7��4λ����ģʽ" << endl;
	cout << "��8��8Ϊ����ģʽ" << endl;
}

Mat g_src, g_dst, g_gray,g_mask;
bool g_bIscolor = 1;   //1��ʾɫ��ͼ
bool g_bIsmask = 0;	//0��ʾ����ʾ��Ĥ
bool g_bFillmode = 1;//0��ʾ�շ�Χ
bool g_flag = 0;//flagΪ0��ʾ�̶���Χ��1��ʾ������Χ
int g_LowDifference=20, g_upDifference=20;
int g_NewMaskVal = 255;
int g_Connection = 4;



void Track(int, void*)
{

}
void MouseCall(int event, int x, int y, int flag, void* userdata)
{
	if (event != EVENT_LBUTTONDOWN)
	{
		return;
	}
	
	//Ϊ��ˮ���д����

	//�������ӵ�
	Point seed = Point(x, y);

	//���������ɫ
	Scalar newval;
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;


	if (g_bIscolor == 1)
	{
		newval = Scalar(b, g, r);
	}
	else
	{
		newval = Scalar(r * 0.299 + g * 0.587 + b * 0.114);
	}

	//�������ֵ����Сֵ��Χ
	int lowDiffenence, upDifference;
	if (g_bFillmode == 1)
	{
		lowDiffenence = g_LowDifference;
		upDifference = g_upDifference;
	}
	else
	{
		lowDiffenence = 0;
		upDifference = 0;
	}

	//���帡����Χ���ǹ̶���Χ���
	int flags;
	if (g_flag == 0)
	{
		flags = g_Connection | FLOODFILL_FIXED_RANGE|g_NewMaskVal<<8;
	}
	else
	{
		flags = g_Connection|g_NewMaskVal<<8;
	}

	//����Ч��ͼ
	Mat dst;
	Rect cc;

	//����������ص�
	int area;
	
	dst = g_bIscolor == 1 ? g_dst: g_gray;

	if (g_bIsmask==0)
	{
		area=floodFill(dst,seed, newval, &cc, Scalar(lowDiffenence, lowDiffenence, lowDiffenence), Scalar(upDifference, upDifference, upDifference), flags);
	}

	else
	{
		threshold(g_mask, g_mask, 1, 128, THRESH_BINARY);

		area = floodFill(dst,g_mask, seed, newval, &cc, Scalar(lowDiffenence, lowDiffenence, lowDiffenence), Scalar(upDifference, upDifference, upDifference), flags);
		imshow("mask", g_mask);
	}
	cout << "��" << area << "���ر����" << endl;
	
	imshow("Ч��ͼ", dst);
}

int main(int argc, char** argv)
{
	my_print();
	 g_src = imread("1.jpg");
	 g_dst = g_src.clone();
	 cvtColor(g_src, g_gray, COLOR_BGR2GRAY);
	 g_mask.create(g_src.rows + 2, g_src.cols + 2, CV_8UC1);
	 g_mask = Scalar::all(0);
	
	namedWindow("Ч��ͼ");
	

	setMouseCallback("Ч��ͼ", MouseCall, 0);
	createTrackbar("lowDifference", "Ч��ͼ", &g_LowDifference,100);
	createTrackbar("upDifference", "Ч��ͼ", &g_upDifference, 100);

	while (1)
	{
		Mat dst = g_bIscolor == 1 ? g_dst : g_gray;
		imshow("Ч��ͼ", dst);
		
		
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			break;
		}
		switch ((char)c)
		{
		case '1':
			if (g_bIscolor == 1)
			{
				g_bIscolor = 0;
				
				
				cvtColor(g_dst, g_gray, COLOR_BGR2GRAY);
			}
			else
			{
				g_bIscolor = 1;
				
				g_dst = g_src.clone();
				g_mask = Scalar::all(0);

			}
			
			

			break;
		case '2':
			if (g_bIsmask == 1)
			{
				destroyWindow("mask");
				g_bIsmask = 0;
			}
			else
			{
				namedWindow("mask");
				imshow("mask", g_mask);
				g_bIsmask = 1;
				
			}
			break;
		case '3':
			g_dst = g_src.clone();
			cvtColor(g_dst, g_gray, COLOR_BGR2BGRA);
			break;
		case '4':
			g_bFillmode = 0;
			break;
		case '5':
			g_bFillmode = 1;
			g_flag = 0;
			break;
		case '6':
			g_bFillmode = 1;
			g_flag = 1;
			break;
		case'7':
			g_Connection = 4;
			break;
		case'8':
			g_Connection = 8;
			break;

		}
	}

	


	return 0;
}





