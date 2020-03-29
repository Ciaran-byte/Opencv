#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace cv;
using namespace std;

int main()
{
	const int picture_num = 33;
	for (int t = 1; t <= picture_num; t++)
	{
		string name = "picture" + to_string(t) + ".jpg";
		Mat src = imread(name);
		
		Mat dst;

		//01 ÃÌº”Ω∑—Œ‘Î…˘
		dst = src.clone();
		string name1 = "impulseNoise" + to_string(t) + ".jpg";
		int num = 50000;
		for (int k = 0; k < num; k++)
		{
			int i = rand() % dst.rows;
			int j = rand() % dst.cols;
			if (dst.channels() == 1)//–ﬁ∏ƒœÒÀÿµ„(i,j)µƒœÒÀÿ÷µ
			{
				dst.at<uchar>(i, j) = 255;     //—Œ‘Î…˘
			}
			else
			{
				dst.at<Vec3b>(i, j)[0] = 255;
				dst.at<Vec3b>(i, j)[1] = 255;
				dst.at<Vec3b>(i, j)[2] = 255;
			}
		}
		for (int k = 0; k < num; k++)
		{
			int i = rand() % dst.rows;
			int j = rand() % dst.cols;
			if (dst.channels() == 1)//–ﬁ∏ƒœÒÀÿµ„(i,j)µƒœÒÀÿ÷µ
			{
				dst.at<uchar>(i, j) = 255;     //—Œ‘Î…˘
			}
			else
			{
				dst.at<Vec3b>(i, j)[0] = 0;
				dst.at<Vec3b>(i, j)[1] = 0;
				dst.at<Vec3b>(i, j)[2] = 0;
			}
		}
		

		imwrite(name1, dst);

		//02 ÃÌº”∏ﬂÀπ‘Î…˘
		string name2 = "gaussianNoise" + to_string(t) + ".jpg";
		dst = src.clone();
		Mat noise=Mat::zeros(src.size(),src.type());
		RNG rng(time(NULL));
		rng.fill(noise, RNG::NORMAL, 10, 36);
		add(dst, noise, dst);
		imwrite(name2, dst);

		
		
	}
	return 0;
}

