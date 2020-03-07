#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	//01 取出基准图片和测试图片
	Mat base, baseHsv;
	

	base = imread("hand.jpg");
	

	//02 转换色彩空间
	cvtColor(base, baseHsv, COLOR_BGR2HSV);
	

	//03 设置参数
	Mat histBase;
	const int channels[] = { 0,1 };

	int hSize = 50;
	int sSize = 60;
	const int histSize[] = { hSize,sSize };

	float hRange[] = { 0,180 };
	float sRange[] = { 0,255 };
	const float* histRange[] = { hRange,sRange };

	bool uniform = true;
	bool accumulate = false;

	//04 计算直方图
	calcHist(&baseHsv, 1, channels, Mat(), histBase, 2, histSize, histRange, uniform, accumulate);
	
	//05 直方图归一化--方便产生能够查看的反向投影图
	
	normalize(histBase, histBase, 0, 255, NORM_MINMAX);
	imshow("h", histBase);
	
	//06制作与其相似的图片
	Mat backProj;
	Mat baseWarp ;
	Mat baseWarpHsv;
	Mat warp = getRotationMatrix2D(Point(0, 0), 30, 1);
	warpAffine(base, baseWarp, warp, base.size());

	
	cvtColor(baseWarp, baseWarpHsv, COLOR_BGR2HSV);

	//07反向投影
	calcBackProject(&baseWarpHsv, 1, channels, histBase, backProj, histRange, 1, true);

	//08查看图像
	imshow("backProj", backProj);

	waitKey(0);
	return 0;
}

