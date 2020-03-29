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



		//03 计算自相关函数以进行清晰度评价
		double value1 = 0;
		for (int row = 0; row < src.rows; row++)
		{
			for (int col = 0; col < src.cols-1; col++)
			{
				value1 += static_cast<double>(srcMakeBorder.at<uchar>(row, col)) * static_cast<double>(srcMakeBorder.at<uchar>(row, col + 1));
			}
		}
		cout << value1 << endl;
		double value2 = 0;
		for (int row = 0; row < src.rows; row++)
		{
			for (int col = 0; col < src.cols -2; col++)
			{
				value2 += static_cast<double>(srcMakeBorder.at<uchar>(row, col))* static_cast<double>(srcMakeBorder.at<uchar>(row, col + 2));
			}
		}
		cout << value2 << endl;
		double value = value1 - value2;
		value = value / (static_cast<double>(src.rows) * static_cast<double>(src.cols));
		
		cout << value << endl;
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

