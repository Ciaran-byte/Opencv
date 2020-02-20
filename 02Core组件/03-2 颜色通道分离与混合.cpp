#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	vector<Mat> channel;
	Mat B;
	Mat G;
	Mat R;
	Mat srcImg = imread("1.jpg");
	split(srcImg, channel);
	B = channel.at(0);
	G = channel.at(1);
	R = channel.at(2);
	imshow("B", B);
	imshow("G", G);
	imshow("R", R);
	imshow("M", srcImg);

	for (int i = 0; i < R.rows; i++)
	{
		for (int j = 0; j < R.cols; j++)
		{
			R.at<uchar>(i, j) =	R.at<uchar>(i, j)/200*200;
		}
	}
	imshow("R2", R);
	
	merge(channel, srcImg);
	imshow("M2", srcImg);

	waitKey(0);


	return 0;
}

