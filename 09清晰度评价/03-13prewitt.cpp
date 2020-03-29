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

		//02 定义prewitt算子卷积核
		Mat kernal_x = (Mat_<float>(3,3)<<
			1, 0, -1, 
			1, 0, -1, 
			1, 0, -1);
		Mat kernal_y = (Mat_<float>(3, 3) <<
			-1, -1, -1,
			0, 0, 0,
			1, 1, 1);

		Mat prewitt_x;
		Mat prewitt_y;
		
		//03 保留两个梯度方向更大的那个作为梯度值，用于清晰度评价参数
		filter2D(src, prewitt_x, CV_32F, kernal_x);
		filter2D(src, prewitt_y, CV_32F, kernal_y);


		float value = 0;
		for (int row = 0; row < src.rows; row++)
		{
			for (int col = 0; col < src.cols; col++)
			{
				float px = prewitt_x.at<float>(row, col);
				float py = prewitt_y.at<float>(row, col);
				float cmp;
				if (px > py)cmp = px;
				else cmp = py;
				value += cmp;
			}
		}
		value = value / (src.rows * src.cols);
		cout << value << endl;

		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

