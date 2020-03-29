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
		copyMakeBorder(src, srcMakeBorder, 2, 2, 2, 2, BORDER_DEFAULT);
		


		//03 计算自相关函数以进行清晰度评价

		//区域对比度计算原理是搜索图像中所有像素点及其邻域的范围内的最大值和最小值
		// 每个像素的评价值为max-min/max
		//所有像素的评价值相加就是最终的评价值
		// 该计算方法计算量比较大，运行速度比较慢
		vector<vector<int>> shift = { {-1,0},{0,0},{1,0},{-1,1}, {0,1},{1,1} };
		double value = 0;
		
		for (int row = 2; row < src.rows; row++)
		{
			for (int col = 2; col < src.cols ; col++)
			{
				double max = 0;
				double min = 255;
				double rst = 0;
				
				for (int i = 0; i < 6; i++)
				{
					double pixel = srcMakeBorder.at<uchar>(row + shift[i][1], col + shift[i][0]);
					if (pixel > max)max = pixel;
					if (pixel < min)min = pixel;
				}
				if (max == 0)rst = 0;
				else
				{
					rst = (max - min) / max;
				}
				
				value += rst;
				
				
			}
		}
		value = log(value);
		cout << value << endl;
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

