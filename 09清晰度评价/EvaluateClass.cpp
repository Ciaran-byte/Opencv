#include<iostream>
#include<opencv2/opencv.hpp>
#include "EvaluateClass.h"
using namespace cv;
using namespace std;



//方差函数类的评价函数
 double VarianceClass::evaluate() const
{
	 //01定义中间变量
	 Mat gray;
	 double value = 0;
	 double mean = 0;
	 if (_src.channels() == 3)
	 {

		 cvtColor(_src, gray, COLOR_BGR2GRAY);
	 }
	 if (_src.channels() == 1)
	 {
		 gray = _src.clone();
	 }

	 //02 图片预处理
	 PreProcess(gray);
	 //03 计算灰度图平均值
	 for (int row = 0; row < gray.rows; row++)
	 {
		 for (int col = 0; col < gray.cols; col++)
		 {
			 mean += gray.at<uchar>(row, col);
		 }
	 }
	 mean = mean / (static_cast<double>(gray.rows)* static_cast<double>(gray.cols));

	 //04 计算方差
	 for (int row = 0; row < gray.rows; row++)
	 {
		 for (int col = 0; col < gray.cols; col++)
		 {
			 value += pow((gray.at<uchar>(row, col) - mean), 2);
		 }
	 }
	 value = value / (static_cast<double>(_src.rows)* static_cast<double>(_src.cols));
	 return value;
}

//DCT函数类的评价函数
 double DCTClass::evaluate() const
 {

	 //01定义中间变量
	 Mat gray;
	 double value = 0;
	 if (_src.channels() == 3)
	 {

		 cvtColor(_src, gray, COLOR_BGR2GRAY);
	 }
	 if (_src.channels() == 1)
	 {
		 gray = _src.clone();
	 }
	 gray.convertTo(gray, CV_32FC1);

	 //02 图片预处理
	 PreProcess(gray);

	 //03 图片分割为8x8大小的区域块
	 //03-1 先把图片边长变换为8的倍数
	 int num_x = gray.cols / 8;
	 int num_y = gray.rows / 8;
	 int num = (num_x > num_y ? num_y : num_x);

	 //03-2 图片截取8的倍数的边长
	 gray = gray(Rect(0, 0, num * 8, num * 8));

	 //04 对每一个区域块进行离散余弦变换,截取对角线的平方和作为评价函数

	 for (int row = 0; row < num; row++)
	 {
		 for (int col = 0; col < num; col++)
		 {
			 Mat ROI = gray(Rect(col * 8, row * 8, 8, 8));
			 dct(ROI, ROI);
			 for (int i = 0; i < 8; i++)
			 {
				 value += pow(ROI.at<float>(i, i), 2);
			 }
		 }
	 }

	 //输出结果
	 value = value / (static_cast<double>(_src.rows)* static_cast<double>(_src.cols));
	 value = log(value + 1);
	 return value;
 }

//能量梯度函数类的评价函数
 double EnergyGradClass::evaluate() const
 {
	 //01定义中间变量
	 Mat gray;
	 double value = 0;
	 if (_src.channels() == 3)
	 {

		 cvtColor(_src, gray, COLOR_BGR2GRAY);
	 }
	 if (_src.channels() == 1)
	 {
		 gray = _src.clone();
	 }

	 //02 图片预处理
	 PreProcess(gray);
	 //03 扩充图像边界
	 Mat GrayMakeBorder;
	 copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	 //04 用能量梯度函数进行清晰度评价
	 for (int row = 0; row < gray.rows; row++)
	 {

		 for (int col = 0; col < gray.cols; col++)
		 {
			 value += pow(GrayMakeBorder.at<uchar>(row + 1, col) - GrayMakeBorder.at<uchar>(row, col), 2) +
				 pow(GrayMakeBorder.at<uchar>(row, col + 1) - GrayMakeBorder.at<uchar>(row, col), 2);
		 }

	 }
	 value = value / (static_cast<double>(_src.rows)* static_cast<double>(_src.cols));
	 return value;
 }

 //多态的评价函数
 double dstEvaluate(const EvaluateBaseClass& rhs)
 {
	 return rhs.evaluate();
 }


 //亮度归一化函数
void LightNormalize( Mat& src)
 {

	
	 Mat mat_mean, mat_stddev;
	// 计算原图片的平均值和方差的函数
	 meanStdDev(src, mat_mean, mat_stddev);


	 if (src.channels() == 1)
	 {
		 double mean = mat_mean.at<double>(0);
		 for (int row = 0; row < src.rows; row++)
		 {
			 for (int col = 0; col < src.cols; col++)
			 {
				 src.at<uchar>(row, col) = src.at<uchar>(row, col) / static_cast<uchar>(mean);
			 }
		 }
	 }
	 if (src.channels() == 3)
	 {
		 double mean1 = mat_mean.at<double>(0);
		 double mean2 = mat_mean.at<double>(1);
		 double mean3 = mat_mean.at<double>(2);

		 for (int row = 0; row < src.rows; row++)
		 {
			 for (int col = 0; col < src.cols; col++)
			 {
				 src.at<Vec3b>(row, col)[0] = src.at<Vec3b>(row, col)[0] / static_cast<uchar>(mean1);
				 src.at<Vec3b>(row, col)[1] = src.at<Vec3b>(row, col)[1] / static_cast<uchar>(mean2);
				 src.at<Vec3b>(row, col)[2] = src.at<Vec3b>(row, col)[2] / static_cast<uchar>(mean3);

			 }
		 }
	 }
	
 }

 //预处理函数
 void PreProcess(Mat& src)
 {
	 //改变大小
	 resize(src, src, Size(512, 512));

	 //高斯滤波
	 GaussianBlur(src, src, Size(3, 3), 0);

	 //亮度归一化
	 LightNormalize(src);
 }
