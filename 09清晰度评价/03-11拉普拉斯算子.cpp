#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	const int picture_num = 33;
	for (int t = 1; t <= picture_num; t++)
	{
		double t1 = (double)getTickCount();

		//01 读入图片组
		string name = "picture" + to_string(t) + ".jpg";
		Mat src = imread(name, 0);
		
		//02 对图片与拉普拉斯算子进行卷积
		Mat dst;
		Laplacian(src, dst, CV_32F,3);
		convertScaleAbs(dst, dst);

		//03 求拉普拉斯算子的平方和
		double value=0;
		for (int row = 0; row < dst.rows ; row++)
		{
			for (int col = 0; col < dst.cols ; col++)
			{
				value += dst.at<uchar>(row, col);
			}
		}
		value = value / (dst.rows * dst.cols);
		cout << value << endl;

		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

