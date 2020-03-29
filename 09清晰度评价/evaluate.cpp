#include<iostream>
#include "evaluate.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


double TenenGradEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	Mat sobel_x;
	Mat sobel_y;
	Mat sobel_magnitude;
	double value = 0;
	//02 将图片变为灰度图
	
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//03 求x方向sobel算子
	Sobel(gray, sobel_x, CV_32F, 1, 0);

	//04 求y方向sobel算子
	Sobel(gray, sobel_y, CV_32F, 0, 1);

	//05 求幅值
	magnitude(sobel_x, sobel_y, sobel_magnitude);

	////06 计算sobel算子的平方和
	for (int row = 0; row < sobel_magnitude.rows; row++)
	{
		for (int col = 0; col < sobel_magnitude.cols; col++)
		{
			
			value += static_cast<double>(sobel_magnitude.at<float>(row, col)) * static_cast<double>(sobel_magnitude.at<float>(row,col));
		}
	}
	value = value / (static_cast<double>(src.rows) * static_cast<double>(src.cols));
	return value;
}

double EnergyGradEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	double value = 0;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}
	//02 扩充图像边界
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 用能量梯度函数进行清晰度评价
	for (int row = 0; row < gray.rows; row++)
	{

		for (int col = 0; col < gray.cols; col++)
		{
			value += pow(GrayMakeBorder.at<uchar>(row + 1, col) - GrayMakeBorder.at<uchar>(row, col), 2) +
				pow(GrayMakeBorder.at<uchar>(row, col + 1) - GrayMakeBorder.at<uchar>(row, col), 2);
		}

	}
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double BrennerGradEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	double value = 0;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 扩充图像边界
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 应用brenner梯度函数计算评价值
	
	for (int row = 0; row < src.rows; row++)
	{

		for (int col = 0; col < src.cols; col++)
		{
			value += pow(GrayMakeBorder.at<uchar>(row, col+2) - GrayMakeBorder.at<uchar>(row, col), 2);

		}

	}
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
	
}

double VarianceEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	double value = 0;
	double mean=0;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 计算灰度图平均值
	for (int row = 0; row < gray.rows; row++)
	{
		for (int col = 0; col < gray.cols; col++)
		{
			mean += gray.at<uchar>(row, col);
		}
	}
	mean = mean / (static_cast<double>(gray.rows)* static_cast<double>(gray.cols));
	
	//03 计算方差
	for (int row = 0; row < gray.rows; row++)
	{
		for (int col = 0; col < gray.cols; col++)
		{
			value += pow((gray.at<uchar>(row, col) - mean), 2);
		}
	}
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double WaveletEvaluate(const Mat& src)
{

	//01定义中间变量
	Mat gray;
	double value = 0;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 定义特殊的高通滤波器
	Mat kernal = (
		Mat_<double>(3, 3) <<
		-1.0 / 16, -1.0 / 8, -1.0 / 16,
		-1.0 / 8, 3.0 / 4, -1.0 / 8,
		-1.0 / 16, -1.0 / 8, -1.0 / 16
		);

	//03 图像与高通滤波器卷积
	Mat dst;
	filter2D(gray, dst, CV_32F, kernal);

	//04 计算评价值
	for (int row = 0; row < dst.rows; row++)
	{
		for (int col = 0; col < dst.cols; col++)
		{
			value += pow((dst.at<float>(row, col)), 2);
		}
	}
	value = log(value+1);
	return value;
}

double DctEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	double value = 0;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}
	gray.convertTo(gray, CV_32FC1);
	//02 图片分割为8x8大小的区域块
	//02-1 先把图片边长变换为8的倍数
	int num_x = gray.cols / 8;
	int num_y = gray.rows / 8;
	int num = (num_x > num_y ? num_y : num_x);

	//02-2 图片截取8的倍数的边长
	gray = gray(Rect(0, 0, num * 8, num * 8));

	//03 对每一个区域块进行离散余弦变换,截取对角线的平方和作为评价函数
	
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
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	value = log(value + 1);
	return value;
}


double ModifiedSobelEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	Mat sobel_x;
	Mat sobel_y;
	Mat sobel_r1;
	Mat sobel_r2;
	
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}
	
	//02 求四个方向的sobel梯度
	Sobel(gray, sobel_x, CV_32F, 1, 0);

	Sobel(gray, sobel_y, CV_32F, 0, 1);

	Mat r1 = (Mat_<float>(3, 3) << 0, 1, 2, -1, 0, 1, -2, -1, 0);
	filter2D(gray, sobel_r1, CV_32F, r1);

	Mat r2 = (Mat_<float>(3, 3) << -2, -1, 0, -1, 0, 1, 0, 1, 2);
	filter2D(gray, sobel_r2, CV_32F, r2);

	//03 求四个梯度的L1范数构成的矩阵，并且把矩阵值进行阈值化
	float sum;
	Mat sobel_magnitude(src.cols, src.rows, CV_32FC1);
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			sum = abs(sobel_x.at<float>(row, col)) + abs(sobel_y.at<float>(row, col))
				+ abs(sobel_r1.at<float>(row, col)) + abs(sobel_r2.at<float>(row, col));
			if (sum > 255)sum = 255;
			sobel_magnitude.at<float>(row, col) = sum;
		}

	}

	//04 寻找0-200像素值中的最大值作为阈值,通过直方图的方法寻找前200个像素中的非零值，即可找到这个最大值
	const int channels[] = { 0 };
	Mat hist;
	int size = 256;
	const int histSize[] = { size };
	float range[] = { 0,256 };
	const float* histRange[] = { range };
	calcHist(&sobel_magnitude, 1, channels, Mat(), hist, 1, histSize, histRange, true, false);

	int thres;
	for (int i = 0; i <= 200; i++)
	{

		if (hist.at<float>(i, 0) != 0)  thres = i;
	}

	//06 大于阈值的像素求平均值,作为最终的评价值
	int num = 0;
	double value = 0;
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			if (sobel_magnitude.at<float>(row, col) >= thres)
			{
				value += sobel_magnitude.at<float>(row, col);
				num++;
			}
		}

	}
	//07 输出结果
	double result = value / num;
	return result;
}

double AutoCorrelationEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 扩充图像边界
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 计算自相关函数以进行清晰度评价
	double value1 = 0;
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols - 1; col++)
		{
			value1 += static_cast<double>(GrayMakeBorder.at<uchar>(row, col))* static_cast<double > (GrayMakeBorder.at<uchar>(row, col + 1));
		}
	}
	
	double value2 = 0;
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols - 2; col++)
		{
			value2 += static_cast<double>(GrayMakeBorder.at<uchar>(row, col))* static_cast<double>(GrayMakeBorder.at<uchar>(row, col + 2));
		}
	}
	
	double value = value1 - value2;

	//输出结果
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}


double ContrastEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 扩充边界
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 2, 2, 2, 2, BORDER_DEFAULT);

	//03 计算自相关函数以进行清晰度评价

		//区域对比度计算原理是搜索图像中所有像素点及其邻域的范围内的最大值和最小值
		// 每个像素的评价值为max-min/max
		//所有像素的评价值相加就是最终的评价值
		// 该计算方法计算量比较大，运行速度比较慢

	vector<vector<int>> shift = { {-1,0},{0,0},{1,0},{-1,1}, {0,1},{1,1} };
	double value = 0;

	for (int row = 2; row < gray.rows; row++)
	{
		for (int col = 2; col < gray.cols; col++)
		{
			double max = 0;
			double min = 255;
			double rst = 0;

			for (int i = 0; i < 6; i++)
			{
				double pixel = GrayMakeBorder.at<uchar>(row + shift[i][1], col + shift[i][0]);
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
		//输出结果
	value = log(value + 1);
		return value;
	
}

double SusanEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 扩充边界
	Mat GrayMakeBorder;
	int addBorder = 3;
	copyMakeBorder(gray, GrayMakeBorder, addBorder, addBorder, addBorder, addBorder, BORDER_DEFAULT);

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
	//03 -2 遍历每一个像素点的邻域，因为前面对图像上下左右均扩充了3个点，所以遍历的时候从
			//（3,3）这个点开始，因为这是原始图像的原点

	double value = 0;
	for (int row = addBorder; row < gray.rows; row++)
	{
		for (int col = addBorder; col < gray.cols ; col++)
		{
			int num = 0;//用于计算37邻域内与中心点差值满足要求的点的数量
			int thres_t = 5;
			int thres_g = 30;
			for (int i = 0; i < 37; i++)
			{
				if (abs(GrayMakeBorder.at<uchar>(row, col) -
					GrayMakeBorder.at<uchar>(row + OffSetY[i], col + OffSetX[i])) <= thres_t)
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

	value = log(value + 1);
	return value;
}

double LaplacianEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 对图片与拉普拉斯算子进行卷积
	Mat dst;
	Laplacian(gray, dst, CV_32F, 3);
	convertScaleAbs(dst, dst);

	//03 求拉普拉斯算子的平方和
	double value = 0;
	for (int row = 0; row < dst.rows; row++)
	{
		for (int col = 0; col < dst.cols; col++)
		{
			value += dst.at<uchar>(row, col);
		}
	}
	
	//输出结果
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double RobertsEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 扩充图像边界
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 求roberts梯度和
	double value = 0;
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			value += abs(static_cast<double>(GrayMakeBorder.at<uchar>(row, col)) - static_cast<double>(GrayMakeBorder.at<uchar>(row + 1, col + 1)))
				+ abs(static_cast<double>(GrayMakeBorder.at<uchar>(row, col + 1)) - static_cast<double>(GrayMakeBorder.at<uchar>(row + 1, col)));
		}
	}
	//输出结果
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double PrewittEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 定义prewitt算子卷积核
	Mat kernal_x = (Mat_<float>(3, 3) <<
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
	filter2D(gray, prewitt_x, CV_32F, kernal_x);
	filter2D(gray, prewitt_y, CV_32F, kernal_y);

	double value = 0;
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
	//输出结果
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double SharpnessEvaluate(const Mat& src)
{
	//01定义中间变量
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 定义偏移量
	vector<vector<int>> shift = { {-1,0},{1,0},{0,-1},{0,1}, {-1,1},{1,-1},{1,1},{1,-1} };

	//03 扩充边界
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 2, 2, 2, 2, BORDER_DEFAULT);

	//04 计算清晰度评价函数
	double value = 0;
	for (int row = 2; row < src.rows ; row++)
	{
		for (int col = 2; col < src.cols; col++)
		{
			//每个像素点8个方向的梯度
			double P = 0;
			for (int i = 0; i < 4; i++)
			{
				P += static_cast<float>(abs(GrayMakeBorder.at<uchar>(row, col) - GrayMakeBorder.at<uchar>(row + shift[i][1], col + shift[i][0])));
			}
			for (int i = 4; i < 8; i++)
			{
				P += static_cast<float>(abs(GrayMakeBorder.at<uchar>(row, col) - GrayMakeBorder.at<uchar>(row + shift[i][1], col + shift[i][0]))) / pow(2, 0.5);
			}
			value += P;
		}
	}
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}


Mat LightNormalize(const Mat& src)
{
	
	Mat mat_mean, mat_stddev;
	Mat dst = src.clone();
	meanStdDev(src, mat_mean, mat_stddev);
	

	if (src.channels() == 1)
	{
		double mean = mat_mean.at<double>(0);
		for (int row = 0; row < src.rows; row++)
		{
			for (int col = 0; col < src.cols; col++)
			{
				dst.at<uchar>(row, col) = dst.at<uchar>(row, col) / static_cast<uchar>(mean);
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
				dst.at<Vec3b>(row, col)[0] = dst.at<Vec3b>(row, col)[0]/static_cast<uchar>(mean1);
				dst.at<Vec3b>(row, col)[1] = dst.at<Vec3b>(row, col)[1] / static_cast<uchar>(mean2);
				dst.at<Vec3b>(row, col)[2] = dst.at<Vec3b>(row, col)[2] / static_cast<uchar>(mean3);

			}
		}
	}
	return dst;
}
