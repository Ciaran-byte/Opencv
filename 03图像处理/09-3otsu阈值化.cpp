#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;



int main()
{


	Mat m = imread("1.jpg",0);
	Mat n;
	//01创建用来统计图像中各个灰度值的数量以及比例的数组
	int nNum[256];
	double nPro[256];

	//定义A组比例，B组比例，A组平均灰度，B组平均灰度，总的平均灰度
	double w0=0, w1=0, u0=0, u1=0, ut=0;
	double maxVal = 0;
	int maxNum = 0;
	double sigma = 0;


	for (int i = 0; i < 256; i++)
	{

		nNum[i] = 0;
		nPro[i] = 0.0;

	}

	//02统计每个灰度值的数量
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			nNum[m.at<uchar>(i, j)] += 1;
		}
	}

	//03统计每个灰度值的比例
	for (int i = 0; i < 256; i++)
	{
		nPro[i] = 1.0*nNum[i] / (m.cols * m.rows);
		ut += i * nPro[i];
		
	}

	//04开始穷举
	
	for (int i = 0; i < 256; i++)
	{
		

		w0 = w1 = u0 = u1 =sigma= 0;
		for (int j = 0; j < 255; j++)
		{
			
			
			if (j < i)
			{
				w0 += nPro[j];
				u0 += nPro[j] * j;
			}
			else
			{
				w1 += nPro[j];
				u1 += nPro[j] * j;
			}
		
		
		}

		u0 = u0 / w0;
		u1 = u1 / w1;
		
		sigma = w0 * pow((u0 - ut), 2) + w1 * pow((u1 - ut), 2);
	
		
		if (sigma > maxVal)
		{
			maxVal = sigma;
			maxNum = i;
			
		}
		
		

	}
	threshold(m, n, maxNum, 255, THRESH_BINARY);
	imshow("a", n);
	threshold(m, n, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("b", n);
	waitKey(0);


	return 0;
}



