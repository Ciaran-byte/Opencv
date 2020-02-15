#include<opencv2/opencv.hpp>
using namespace cv;

//程序说明：实现功能为鼠标按下后可以拖动进行绘制矩形框

bool g_value = false;//全局变量，用来判断什么时候开始画矩形框
Rect g_rect(-1,-1,0,0);//用来绘图的矩阵


void DrawRectangle(Mat& m, Rect r) //用来绘制矩形的函数
{
	Scalar s(255, 0, 255);//相当于定义三通道的颜色，三通道分别是255,0,255
	rectangle(m, g_rect, s);//用定义的颜色s，在图像m中绘制矩形g_rect
}
void MouseCallBack(int event,int x,int y,int flags,void* param)//回调函数
{
	Mat m = *(Mat*)param;
	switch (event)
	{
	case(EVENT_MOUSEMOVE):
		if (g_value)//如果鼠标左键按下，g_value变为真，运行进行绘图，绘图矩阵记录鼠标移动的距离，作为宽和高
		{
			g_rect.width = x - g_rect.x;
			g_rect.height = y - g_rect.y;
		}
		break;

	case(EVENT_LBUTTONDOWN):  //鼠标左键按下的时候，给矩阵重新定义初始位置
		g_value = true;
		g_rect = Rect(x, y, 0, 0);
		break;
	case(EVENT_LBUTTONUP): //鼠标左键放开的时候，把矩形画入srcImage。
		g_value = false;
		DrawRectangle(m, g_rect);
		
		
		break;

	}
}

int main()
{

	Mat srcImage, tempImage;  //两个用来存放图片的变量，在绘图中srcImage绘制最后的图片，tempImage绘制绘制中间过程的图片
	srcImage = imread("1.jpg");
	srcImage.copyTo(tempImage);
	namedWindow("a", WINDOW_AUTOSIZE);
	setMouseCallback("a", MouseCallBack, (void*)&srcImage); //鼠标函数

		while(1)
		{
			srcImage.copyTo(tempImage);
			if (g_value)
			{
				DrawRectangle(tempImage, g_rect); //这句话实际上是在记录整个鼠标的移动过程
			}
			imshow("a", tempImage);
			if (waitKey(10) == 27)break;
		}



	return 0;
}

