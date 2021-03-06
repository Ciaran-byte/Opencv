#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
#include <cmath>
using namespace cv;
using namespace std;
/*
RGB转换成灰度图像的一个常用公式是：
Gray = R*0.299 + G*0.587 + B*0.114
*/
//******************灰度转换函数*************************  
//第一个参数image输入的彩色RGB图像的引用；  
//第二个参数imageGray是转换后输出的灰度图像的引用；  
//*******************************************************
void ConvertRGB2GRAY(const Mat& image, Mat& imageGray);

//******************Sobel卷积因子计算X、Y方向梯度和梯度方向角********************  
//第一个参数imageSourc原始灰度图像；  
//第二个参数imageSobelX是X方向梯度图像；  
//第三个参数imageSobelY是Y方向梯度图像；  
//第四个参数pointDrection是梯度方向角数组指针  
//*************************************************************  
void SobelGradDirction(Mat& imageSource, Mat& imageSobelX, Mat& imageSobelY);

//******************计算Sobel的X方向梯度幅值的平方*************************  
//第一个参数imageGradX是X方向梯度图像；    
//第二个参数SobelAmpXX是输出的X方向梯度图像的平方  
//*************************************************************  
void SobelXX(const Mat imageGradX, Mat_<float>& SobelAmpXX);

//******************计算Sobel的Y方向梯度幅值的平方*************************    
//第一个参数imageGradY是Y方向梯度图像；  
//第二个参数SobelAmpXX是输出的Y方向梯度图像的平方  
//*************************************************************  
void SobelYY(const Mat imageGradY, Mat_<float>& SobelAmpYY);

//******************计算Sobel的XY方向梯度幅值的乘积*************************    
//第一个参数imageGradX是X方向梯度图像；
//第二个参数imageGradY是Y方向梯度图像；
//第二个参数SobelAmpXY是输出的XY方向梯度图像 
//*************************************************************  
void SobelXY(const Mat imageGradX, const Mat imageGradY, Mat_<float>& SobelAmpXY);

//****************计算一维高斯的权值数组*****************
//第一个参数size是代表的卷积核的边长的大小
//第二个参数sigma表示的是sigma的大小
//*******************************************************
double* getOneGuassionArray(int size, double sigma);

//****************高斯滤波函数的实现*****************
//第一个参数srcImage是代表的输入的原图
//第二个参数dst表示的是输出的图
//第三个参数size表示的是卷积核的边长的大小
//*******************************************************
void MyGaussianBlur(Mat_<float>& srcImage, Mat_<float>& dst, int size);

//****计算局部特涨结果矩阵M的特征值和响应函数H = (A*B - C) - k*(A+B)^2******
//M
//A  C
//C  B
//Tr(M)=a+b=A+B
//Det(M)=a*b=A*B-C^2
//计算输出响应函数的值得矩阵
//****************************************************************************
void harrisResponse(Mat_<float>& GaussXX, Mat_<float>& GaussYY, Mat_<float>& GaussXY, Mat_<float>& resultData, float k);


//***********非极大值抑制和满足阈值及某邻域内的局部极大值为角点**************
//第一个参数是响应函数的矩阵
//第二个参数是输入的灰度图像
//第三个参数表示的是输出的角点检测到的结果图
void LocalMaxValue(Mat_<float>& resultData, Mat& srcGray, Mat& ResultImage, int kSize);

int main()
{
	const Mat srcImage = imread("house.jpg");
	if (!srcImage.data)
	{
		printf("could not load image...\n");
		return -1;
	}
	imshow("srcImage", srcImage);
	Mat srcGray;
	ConvertRGB2GRAY(srcImage, srcGray);
	Mat imageSobelX;
	Mat imageSobelY;
	Mat resultImage;
	Mat_<float> imageSobelXX;
	Mat_<float> imageSobelYY;
	Mat_<float> imageSobelXY;
	Mat_<float> GaussianXX;
	Mat_<float> GaussianYY;
	Mat_<float> GaussianXY;
	Mat_<float> HarrisRespond;
	//计算Soble的XY梯度
	SobelGradDirction(srcGray, imageSobelX, imageSobelY);
	//计算X方向的梯度的平方
	SobelXX(imageSobelX, imageSobelXX);
	SobelYY(imageSobelY, imageSobelYY);
	SobelXY(imageSobelX, imageSobelY, imageSobelXY);
	//计算高斯模糊XX YY XY
	MyGaussianBlur(imageSobelXX, GaussianXX, 3);
	MyGaussianBlur(imageSobelYY, GaussianYY, 3);
	MyGaussianBlur(imageSobelXY, GaussianXY, 3);
	harrisResponse(GaussianXX, GaussianYY, GaussianXY, HarrisRespond, 0.05);
	LocalMaxValue(HarrisRespond, srcGray, resultImage, 3);
	imshow("imageSobelX", imageSobelX);
	imshow("imageSobelY", imageSobelY);
	imshow("resultImage", resultImage);
	waitKey(0);
	return 0;
}
void ConvertRGB2GRAY(const Mat& image, Mat& imageGray)
{
	if (!image.data || image.channels() != 3)
	{
		return;
	}
	//创建一张单通道的灰度图像
	imageGray = Mat::zeros(image.size(), CV_8UC1);
	//取出存储图像像素的数组的指针
	uchar* pointImage = image.data;
	uchar* pointImageGray = imageGray.data;
	//取出图像每行所占的字节数
	size_t stepImage = image.step;
	size_t stepImageGray = imageGray.step;
	for (int i = 0; i < imageGray.rows; i++)
	{
		for (int j = 0; j < imageGray.cols; j++)
		{
			pointImageGray[i * stepImageGray + j] = (uchar)(0.114 * pointImage[i * stepImage + 3 * j] + 0.587 * pointImage[i * stepImage + 3 * j + 1] + 0.299 * pointImage[i * stepImage + 3 * j + 2]);
		}
	}
}


//存储梯度膜长
void SobelGradDirction(Mat& imageSource, Mat& imageSobelX, Mat& imageSobelY)
{
	imageSobelX = Mat::zeros(imageSource.size(), CV_32SC1);
	imageSobelY = Mat::zeros(imageSource.size(), CV_32SC1);
	//取出原图和X和Y梯度图的数组的首地址
	uchar* P = imageSource.data;
	uchar* PX = imageSobelX.data;
	uchar* PY = imageSobelY.data;

	//取出每行所占据的字节数
	int step = imageSource.step;
	int stepXY = imageSobelX.step;

	int index = 0;//梯度方向角的索引
	for (int i = 1; i < imageSource.rows - 1; ++i)
	{
		for (int j = 1; j < imageSource.cols - 1; ++j)
		{
			//通过指针遍历图像上每一个像素   
			double gradY = P[(i + 1) * step + j - 1] + P[(i + 1) * step + j] * 2 + P[(i + 1) * step + j + 1] - P[(i - 1) * step + j - 1] - P[(i - 1) * step + j] * 2 - P[(i - 1) * step + j + 1];
			PY[i * stepXY + j * (stepXY / step)] = abs(gradY);

			double gradX = P[(i - 1) * step + j + 1] + P[i * step + j + 1] * 2 + P[(i + 1) * step + j + 1] - P[(i - 1) * step + j - 1] - P[i * step + j - 1] * 2 - P[(i + 1) * step + j - 1];
			PX[i * stepXY + j * (stepXY / step)] = abs(gradX);
		}
	}
	//将梯度数组转换成8位无符号整型
	convertScaleAbs(imageSobelX, imageSobelX);
	convertScaleAbs(imageSobelY, imageSobelY);
}


void SobelXX(const Mat imageGradX, Mat_<float>& SobelAmpXX)
{
	SobelAmpXX = Mat_<float>(imageGradX.size(), CV_32FC1);
	for (int i = 0; i < SobelAmpXX.rows; i++)
	{
		for (int j = 0; j < SobelAmpXX.cols; j++)
		{
			SobelAmpXX.at<float>(i, j) = imageGradX.at<uchar>(i, j) * imageGradX.at<uchar>(i, j);
		}
	}
	//convertScaleAbs(SobelAmpXX, SobelAmpXX);
}

void SobelYY(const Mat imageGradY, Mat_<float>& SobelAmpYY)
{
	SobelAmpYY = Mat_<float>(imageGradY.size(), CV_32FC1);
	for (int i = 0; i < SobelAmpYY.rows; i++)
	{
		for (int j = 0; j < SobelAmpYY.cols; j++)
		{
			SobelAmpYY.at<float>(i, j) = imageGradY.at<uchar>(i, j) * imageGradY.at<uchar>(i, j);
		}
	}
	//convertScaleAbs(SobelAmpYY, SobelAmpYY);
}

void SobelXY(const Mat imageGradX, const Mat imageGradY, Mat_<float>& SobelAmpXY)
{
	SobelAmpXY = Mat_<float>(imageGradX.size(), CV_32FC1);
	for (int i = 0; i < SobelAmpXY.rows; i++)
	{
		for (int j = 0; j < SobelAmpXY.cols; j++)
		{
			SobelAmpXY.at<float>(i, j) = imageGradX.at<uchar>(i, j) * imageGradY.at<uchar>(i, j);
		}
	}
	//convertScaleAbs(SobelAmpXY, SobelAmpXY);
}



//计算一维高斯的权值数组
double* getOneGuassionArray(int size, double sigma)
{
	double sum = 0.0;
	//定义高斯核半径
	int kerR = size / 2;

	//建立一个size大小的动态一维数组
	double* arr = new double[size];
	for (int i = 0; i < size; i++)
	{

		// 高斯函数前的常数可以不用计算，会在归一化的过程中给消去
		arr[i] = exp(-((i - kerR) * (i - kerR)) / (2 * sigma * sigma));
		sum += arr[i];//将所有的值进行相加

	}
	//进行归一化	
	for (int i = 0; i < size; i++)
	{
		arr[i] /= sum;
		cout << arr[i] << endl;
	}
	return arr;
}

void MyGaussianBlur(Mat_<float>& srcImage, Mat_<float>& dst, int size)
{
	CV_Assert(srcImage.channels() == 1 || srcImage.channels() == 3); // 只处理单通道或者三通道图像
	int kerR = size / 2;
	dst = srcImage.clone();
	int channels = dst.channels();
	double* arr;
	arr = getOneGuassionArray(size, 1);//先求出高斯数组

									   //遍历图像 水平方向的卷积
	for (int i = kerR; i < dst.rows - kerR; i++)
	{
		for (int j = kerR; j < dst.cols - kerR; j++)
		{
			float GuassionSum[3] = { 0 };
			//滑窗搜索完成高斯核平滑
			for (int k = -kerR; k <= kerR; k++)
			{

				if (channels == 1)//如果只是单通道
				{
					GuassionSum[0] += arr[kerR + k] * dst.at<float>(i, j + k);//行不变，列变换，先做水平方向的卷积
				}
				else if (channels == 3)//如果是三通道的情况
				{
					Vec3f bgr = dst.at<Vec3f>(i, j + k);
					auto a = arr[kerR + k];
					GuassionSum[0] += a * bgr[0];
					GuassionSum[1] += a * bgr[1];
					GuassionSum[2] += a * bgr[2];
				}
			}
			for (int k = 0; k < channels; k++)
			{
				if (GuassionSum[k] < 0)
					GuassionSum[k] = 0;
				else if (GuassionSum[k] > 255)
					GuassionSum[k] = 255;
			}
			if (channels == 1)
				dst.at<float>(i, j) = static_cast<float>(GuassionSum[0]);
			else if (channels == 3)
			{
				Vec3f bgr = { static_cast<float>(GuassionSum[0]), static_cast<float>(GuassionSum[1]), static_cast<float>(GuassionSum[2]) };
				dst.at<Vec3f>(i, j) = bgr;
			}

		}
	}

	//竖直方向
	for (int i = kerR; i < dst.rows - kerR; i++)
	{
		for (int j = kerR; j < dst.cols - kerR; j++)
		{
			float GuassionSum[3] = { 0 };
			//滑窗搜索完成高斯核平滑
			for (int k = -kerR; k <= kerR; k++)
			{

				if (channels == 1)//如果只是单通道
				{
					GuassionSum[0] += arr[kerR + k] * dst.at<float>(i + k, j);//行变，列不换，再做竖直方向的卷积
				}
				else if (channels == 3)//如果是三通道的情况
				{
					Vec3f bgr = dst.at<Vec3f>(i + k, j);
					auto a = arr[kerR + k];
					GuassionSum[0] += a * bgr[0];
					GuassionSum[1] += a * bgr[1];
					GuassionSum[2] += a * bgr[2];
				}
			}
			for (int k = 0; k < channels; k++)
			{
				if (GuassionSum[k] < 0)
					GuassionSum[k] = 0;
				else if (GuassionSum[k] > 255)
					GuassionSum[k] = 255;
			}
			if (channels == 1)
				dst.at<float>(i, j) = static_cast<float>(GuassionSum[0]);
			else if (channels == 3)
			{
				Vec3f bgr = { static_cast<float>(GuassionSum[0]), static_cast<float>(GuassionSum[1]), static_cast<float>(GuassionSum[2]) };
				dst.at<Vec3f>(i, j) = bgr;
			}

		}
	}
	delete[] arr;
}

void harrisResponse(Mat_<float>& GaussXX, Mat_<float>& GaussYY, Mat_<float>& GaussXY, Mat_<float>& resultData, float k)
{
	//创建一张响应函数输出的矩阵
	resultData = Mat_<float>(GaussXX.size(), CV_32FC1);
	for (int i = 0; i < resultData.rows; i++)
	{
		for (int j = 0; j < resultData.cols; j++)
		{
			float a = GaussXX.at<float>(i, j);
			float b = GaussYY.at<float>(i, j);
			float c = GaussXY.at<float>(i, j);
			resultData.at<float>(i, j) = a * b - c * c - k * (a + b) * (a + b);
		}
	}
}


//非极大值抑制
void LocalMaxValue(Mat_<float>& resultData, Mat& srcGray, Mat& ResultImage, int kSize)
{
	int r = kSize / 2;
	ResultImage = srcGray.clone();
	for (int i = r; i < ResultImage.rows - r; i++)
	{
		for (int j = r; j < ResultImage.cols - r; j++)
		{
			if (resultData.at<float>(i, j) > resultData.at<float>(i - 1, j - 1) &&
				resultData.at<float>(i, j) > resultData.at<float>(i - 1, j) &&
				resultData.at<float>(i, j) > resultData.at<float>(i - 1, j - 1) &&
				resultData.at<float>(i, j) > resultData.at<float>(i - 1, j + 1) &&
				resultData.at<float>(i, j) > resultData.at<float>(i, j - 1) &&
				resultData.at<float>(i, j) > resultData.at<float>(i, j + 1) &&
				resultData.at<float>(i, j) > resultData.at<float>(i + 1, j - 1) &&
				resultData.at<float>(i, j) > resultData.at<float>(i + 1, j) &&
				resultData.at<float>(i, j) > resultData.at<float>(i + 1, j + 1))
			{
				if ((int)resultData.at<float>(i, j) > 23000)
				{
					circle(ResultImage, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
				}
			}

		}
	}
}
