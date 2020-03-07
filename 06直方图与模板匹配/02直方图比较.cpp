#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	//01 取出基准图片和测试图片
	 Mat base,baseHsv;
	Mat baseBlur, baseBlurHsv;
	Mat baseWarp, baseWarpHsv;
	Mat baseHalf, baseHalfHsv;
	
	base = imread("1.jpg");
	baseBlur = imread("2.jpg");
	baseWarp = imread("3.jpg");
	baseHalf = imread("4.jpg");
	
	//02 转换色彩空间
	cvtColor(base, baseHsv, COLOR_BGR2HSV);
	cvtColor(baseBlur, baseBlurHsv, COLOR_BGR2HSV);
	cvtColor(baseWarp, baseWarpHsv, COLOR_BGR2HSV);
	cvtColor(baseHalf, baseHalfHsv, COLOR_BGR2HSV);

	//03 设置参数
	Mat histBase, histBlur, histWarp, histHalf;
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
	calcHist(&baseBlurHsv, 1, channels, Mat(), histBlur, 2, histSize, histRange, uniform, accumulate);
	calcHist(&baseWarpHsv, 1, channels, Mat(), histWarp, 2, histSize, histRange, uniform, accumulate);
	calcHist(&baseHalfHsv, 1, channels, Mat(), histHalf, 2, histSize, histRange, uniform, accumulate);


	//05归一化
	normalize(histBase, histBase, 0, 1, NORM_MINMAX);
	normalize(histBlur, histBlur, 0, 1, NORM_MINMAX);
	normalize(histWarp, histWarp, 0, 1, NORM_MINMAX);
	normalize(histHalf, histHalf, 0, 1, NORM_MINMAX);

	//06 匹配、输出
	double base_base, base_blur, base_warp, base_half;
	for (int i = 0; i < 4; i++)
	{
		base_base = compareHist(histBase, histBase, i);
		base_blur = compareHist(histBase, histBlur, i);
		base_warp = compareHist(histBase, histWarp, i);
		base_half = compareHist(histBase, histHalf, i);
		cout << "base_base:" << base_base << endl;
		cout << "base_blur:" << base_blur << endl;
		cout << "base_warp:" << base_warp << endl;
		cout << "base_half:" << base_half << endl;
		cout << endl;
	}
	

	waitKey(0);
	return 0;
}

