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

		//02 扩充边界
		
		Mat srcMakeBorder;
		copyMakeBorder(src, srcMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);
		//03 求roberts梯度和


		double value = 0;
		for (int row = 0; row < src.rows; row++)
		{
			for (int col = 0; col < src.cols; col++)
			{
				value += abs(srcMakeBorder.at<uchar>(row, col)- srcMakeBorder.at<uchar>(row+1, col+1))
					+ abs(srcMakeBorder.at<uchar>(row, col+1) - srcMakeBorder.at<uchar>(row + 1, col ));
			}
		}
		value = value / (src.rows * src.cols);
		cout << value << endl;

		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

