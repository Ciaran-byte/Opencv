#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace cv;
using namespace std;

int main()
{
	//01获取原始图片
	Mat src = imread("cell1.jpg");
	
	if (!src.data)return -1;

	//02参考surf特征提取构建图像金字塔的方法，构建尺度空间参数，尺度空间选用4组4层的格局
	int octave = 4;
	int level = 4;
	double sigma;
	vector<vector<int>> scale{ {9,15,21,27},{33,45,57,69 },{81,99,117,135 },{153,177,201,225} };
	vector<vector<int>> inverse_scale{ {225,201,177,153},{135,117,99,81},{69,57,45,33},{27,21,15,9} };

	//03 构建金字塔，使用高斯滤波器处理原图像,构建尺度空间

	//模拟摄影从远到近的过程
	int num = 1;
	vector<Mat> pictures;
	Mat dst;

	for (int i = 0; i < octave; i++)
	{
		for (int j = 0; j < level; j++)
		{
			
			sigma = 1.2 * inverse_scale[i][j] / 9;
			GaussianBlur(src, dst, Size(inverse_scale[i][j], inverse_scale[i][j]), sigma, sigma);
			pictures.push_back(dst);
			
			
			string name = "picture" +to_string(num)+".jpg";
			
			imwrite(name, dst);
			num++;
		
		}
		
	}

	//模拟最佳位置
	dst = src.clone();
	pictures.push_back(dst);
	string name = "picture" + to_string(num) + ".jpg";
	imwrite(name, dst);
	num++;

	//模拟从近到远的过程
	for (int i = 0; i < octave; i++)
	{
		for (int j = 0; j < level; j++)
		{

			sigma = 1.2 * scale[i][j] / 9;
			GaussianBlur(src, dst, Size(scale[i][j],scale[i][j]), sigma, sigma);
			pictures.push_back(dst);


			string name = "picture" + to_string(num) + ".jpg";

			imwrite(name, dst);
			num++;

		}

	}

	waitKey(0);

	

	return 0;
}

