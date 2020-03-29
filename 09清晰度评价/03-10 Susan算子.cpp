#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	const int picture_num =33;
	for (int t = 1; t <= picture_num; t++)
	{
		double t1 = (double)getTickCount();

		//01 读入图片组
		string name = "picture" + to_string(t) + ".jpg";
		Mat src = imread(name, 0);

		//02 扩充边界
		Mat srcMakeBorder;
		int addBorder = 3;
		copyMakeBorder(src, srcMakeBorder, addBorder, addBorder, addBorder, addBorder, BORDER_DEFAULT);


		//03 susan算子清晰度评价

		//03-1 定义圆形的邻域
		int OffSetX[37] =
		{
				-1, 0, 1,
			-2, -1, 0, 1, 2,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
			-2, -1, 0, 1, 2,
				-1, 0, 1
		};
		int OffSetY[37] =
		{
				-3, -3, -3,
			-2, -2, -2, -2, -2,
		-1, -1, -1, -1, -1, -1, -1,
			 0, 0, 0, 0, 0, 0, 0,
			 1, 1, 1, 1, 1, 1, 1,
				2, 2, 2, 2, 2,
				   3, 3, 3
		};

		//03 -2 遍历每一个像素点的邻域，因为前面对图像上下左右均扩充了2个点，所以遍历的时候从
		//（3,3）这个点开始，因为这是原始图像的原点
		
		double value = 0;
		for (int row = addBorder; row < src.rows/10; row++)
		{
			for (int col = addBorder; col < src.cols/10; col++)
			{
				int num = 0;//用于计算37邻域内与中心点差值满足要求的点的数量
				int thres_t = 6;
				int thres_g = 30;
				for (int i = 0; i < 37; i++)
				{
					if (abs(srcMakeBorder.at<uchar>(row, col) -
						srcMakeBorder.at<uchar>(row + OffSetY[i], col + OffSetX[i]) )<= thres_t)
					{
						num++; //邻域像素与中心像素差值小于thres_t的时候，认为是相似像素，统计相似像素的个数，作为相似区域面积
					}
				}

				//相似个数数量小于thres_g的时候，认为是有效像素点，就累加有效像素点的相似区域面积
				if (num < thres_g)
				{
					//因为相似区域面积越小，说明像素点之间差异越大，用阈值-相似面积，是增加差异大的点的权重
					num = thres_g - num;
				}
				else
				{
					num = 0;
				}
				value += num;

			}
		}
		value = log(value+1);
		
		cout << value << endl;
		
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

