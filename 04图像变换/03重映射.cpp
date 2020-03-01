#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{
	
	Mat m = imread("1.jpg");
	Mat dst;
	imshow("1", m);
	Mat map_x, map_y;
	map_x.create(m.cols, m.rows, CV_32FC1);
	map_y.create(m.cols, m.rows, CV_32FC1);

	for (int j = 0; j < m.rows; j++)
	{
		for (int i = 0; i < m.cols; i++)
		{
			if (i > m.cols * 0.25 && i<m.cols * 0.75 && j>m.rows * 0.25 && j < m.rows * 0.75)
			{
				map_x.at<float>(j, i) = static_cast<float>(2*(i-m.cols*0.25)+0.5);
				map_y.at<float>(j, i) = static_cast<float>(2*(j-m.rows*0.25)+0.5);
			}
			
		}
	}

	remap(m, dst, map_x, map_y, INTER_LINEAR);
	imshow("2", dst);

	for (int j = 0; j < m.rows; j++)
	{
		for (int i = 0; i < m.cols; i++)
		{
			if (i > m.cols * 0.25 && i<m.cols * 0.75 && j>m.rows * 0.25 && j < m.rows * 0.75)
			{
				map_x.at<float>(j, i) = static_cast<float>(2 * (i - m.cols * 0.25) );
				map_y.at<float>(j, i) = static_cast<float>(2 * (j - m.rows * 0.25) );
			}

		}
	}

	remap(m, dst, map_x, map_y, INTER_LINEAR);
	imshow("3", dst);
	waitKey(0);
	return 0;
}
