#include<opencv2/opencv.hpp>
#include<iostream>;
using namespace cv;
using namespace std;
int main()
{
	



	Mat srcImg, logo, mask;
	srcImg = imread("dota.jpg");
	logo = imread("dog.jpg");
	mask = imread("dog.jpg",0);
	
	

	
	for (int i = 0; i < mask.rows; i++)
	{
		uchar* pt = mask.ptr<uchar>(i);
		for (int j = 0; j < mask.cols * mask.channels(); j++)
		{
			pt[j] = 255-pt[j];
		}
	}
	
	imshow("mask", mask);


	
	
	
	Mat srcROI (srcImg(Rect(100, 100, logo.cols, logo.rows)));
	
	logo.copyTo(srcROI,mask);
	
	imshow("b", srcImg);
	


	

	waitKey(0);



	return 0;
}

