#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
	
	Mat m = imread("1.jfif");
	imshow("����ͼƬ", m);
	waitKey(6000);
	return 0;
	
}

