#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
#include <cmath>
using namespace cv;
using namespace std;
/*
RGBת���ɻҶ�ͼ���һ�����ù�ʽ�ǣ�
Gray = R*0.299 + G*0.587 + B*0.114
*/
//******************�Ҷ�ת������*************************  
//��һ������image����Ĳ�ɫRGBͼ������ã�  
//�ڶ�������imageGray��ת��������ĻҶ�ͼ������ã�  
//*******************************************************
void ConvertRGB2GRAY(const Mat& image, Mat& imageGray);

//******************Sobel������Ӽ���X��Y�����ݶȺ��ݶȷ����********************  
//��һ������imageSourcԭʼ�Ҷ�ͼ��  
//�ڶ�������imageSobelX��X�����ݶ�ͼ��  
//����������imageSobelY��Y�����ݶ�ͼ��  
//���ĸ�����pointDrection���ݶȷ��������ָ��  
//*************************************************************  
void SobelGradDirction(Mat& imageSource, Mat& imageSobelX, Mat& imageSobelY);

//******************����Sobel��X�����ݶȷ�ֵ��ƽ��*************************  
//��һ������imageGradX��X�����ݶ�ͼ��    
//�ڶ�������SobelAmpXX�������X�����ݶ�ͼ���ƽ��  
//*************************************************************  
void SobelXX(const Mat imageGradX, Mat_<float>& SobelAmpXX);

//******************����Sobel��Y�����ݶȷ�ֵ��ƽ��*************************    
//��һ������imageGradY��Y�����ݶ�ͼ��  
//�ڶ�������SobelAmpXX�������Y�����ݶ�ͼ���ƽ��  
//*************************************************************  
void SobelYY(const Mat imageGradY, Mat_<float>& SobelAmpYY);

//******************����Sobel��XY�����ݶȷ�ֵ�ĳ˻�*************************    
//��һ������imageGradX��X�����ݶ�ͼ��
//�ڶ�������imageGradY��Y�����ݶ�ͼ��
//�ڶ�������SobelAmpXY�������XY�����ݶ�ͼ�� 
//*************************************************************  
void SobelXY(const Mat imageGradX, const Mat imageGradY, Mat_<float>& SobelAmpXY);

//****************����һά��˹��Ȩֵ����*****************
//��һ������size�Ǵ���ľ���˵ı߳��Ĵ�С
//�ڶ�������sigma��ʾ����sigma�Ĵ�С
//*******************************************************
double* getOneGuassionArray(int size, double sigma);

//****************��˹�˲�������ʵ��*****************
//��һ������srcImage�Ǵ���������ԭͼ
//�ڶ�������dst��ʾ���������ͼ
//����������size��ʾ���Ǿ���˵ı߳��Ĵ�С
//*******************************************************
void MyGaussianBlur(Mat_<float>& srcImage, Mat_<float>& dst, int size);

//****����ֲ����ǽ������M������ֵ����Ӧ����H = (A*B - C) - k*(A+B)^2******
//M
//A  C
//C  B
//Tr(M)=a+b=A+B
//Det(M)=a*b=A*B-C^2
//���������Ӧ������ֵ�þ���
//****************************************************************************
void harrisResponse(Mat_<float>& GaussXX, Mat_<float>& GaussYY, Mat_<float>& GaussXY, Mat_<float>& resultData, float k);


//***********�Ǽ���ֵ���ƺ�������ֵ��ĳ�����ڵľֲ�����ֵΪ�ǵ�**************
//��һ����������Ӧ�����ľ���
//�ڶ�������������ĻҶ�ͼ��
//������������ʾ��������Ľǵ��⵽�Ľ��ͼ
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
	//����Soble��XY�ݶ�
	SobelGradDirction(srcGray, imageSobelX, imageSobelY);
	//����X������ݶȵ�ƽ��
	SobelXX(imageSobelX, imageSobelXX);
	SobelYY(imageSobelY, imageSobelYY);
	SobelXY(imageSobelX, imageSobelY, imageSobelXY);
	//�����˹ģ��XX YY XY
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
	//����һ�ŵ�ͨ���ĻҶ�ͼ��
	imageGray = Mat::zeros(image.size(), CV_8UC1);
	//ȡ���洢ͼ�����ص������ָ��
	uchar* pointImage = image.data;
	uchar* pointImageGray = imageGray.data;
	//ȡ��ͼ��ÿ����ռ���ֽ���
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


//�洢�ݶ�Ĥ��
void SobelGradDirction(Mat& imageSource, Mat& imageSobelX, Mat& imageSobelY)
{
	imageSobelX = Mat::zeros(imageSource.size(), CV_32SC1);
	imageSobelY = Mat::zeros(imageSource.size(), CV_32SC1);
	//ȡ��ԭͼ��X��Y�ݶ�ͼ��������׵�ַ
	uchar* P = imageSource.data;
	uchar* PX = imageSobelX.data;
	uchar* PY = imageSobelY.data;

	//ȡ��ÿ����ռ�ݵ��ֽ���
	int step = imageSource.step;
	int stepXY = imageSobelX.step;

	int index = 0;//�ݶȷ���ǵ�����
	for (int i = 1; i < imageSource.rows - 1; ++i)
	{
		for (int j = 1; j < imageSource.cols - 1; ++j)
		{
			//ͨ��ָ�����ͼ����ÿһ������   
			double gradY = P[(i + 1) * step + j - 1] + P[(i + 1) * step + j] * 2 + P[(i + 1) * step + j + 1] - P[(i - 1) * step + j - 1] - P[(i - 1) * step + j] * 2 - P[(i - 1) * step + j + 1];
			PY[i * stepXY + j * (stepXY / step)] = abs(gradY);

			double gradX = P[(i - 1) * step + j + 1] + P[i * step + j + 1] * 2 + P[(i + 1) * step + j + 1] - P[(i - 1) * step + j - 1] - P[i * step + j - 1] * 2 - P[(i + 1) * step + j - 1];
			PX[i * stepXY + j * (stepXY / step)] = abs(gradX);
		}
	}
	//���ݶ�����ת����8λ�޷�������
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



//����һά��˹��Ȩֵ����
double* getOneGuassionArray(int size, double sigma)
{
	double sum = 0.0;
	//�����˹�˰뾶
	int kerR = size / 2;

	//����һ��size��С�Ķ�̬һά����
	double* arr = new double[size];
	for (int i = 0; i < size; i++)
	{

		// ��˹����ǰ�ĳ������Բ��ü��㣬���ڹ�һ���Ĺ����и���ȥ
		arr[i] = exp(-((i - kerR) * (i - kerR)) / (2 * sigma * sigma));
		sum += arr[i];//�����е�ֵ�������

	}
	//���й�һ��	
	for (int i = 0; i < size; i++)
	{
		arr[i] /= sum;
		cout << arr[i] << endl;
	}
	return arr;
}

void MyGaussianBlur(Mat_<float>& srcImage, Mat_<float>& dst, int size)
{
	CV_Assert(srcImage.channels() == 1 || srcImage.channels() == 3); // ֻ����ͨ��������ͨ��ͼ��
	int kerR = size / 2;
	dst = srcImage.clone();
	int channels = dst.channels();
	double* arr;
	arr = getOneGuassionArray(size, 1);//�������˹����

									   //����ͼ�� ˮƽ����ľ��
	for (int i = kerR; i < dst.rows - kerR; i++)
	{
		for (int j = kerR; j < dst.cols - kerR; j++)
		{
			float GuassionSum[3] = { 0 };
			//����������ɸ�˹��ƽ��
			for (int k = -kerR; k <= kerR; k++)
			{

				if (channels == 1)//���ֻ�ǵ�ͨ��
				{
					GuassionSum[0] += arr[kerR + k] * dst.at<float>(i, j + k);//�в��䣬�б任������ˮƽ����ľ��
				}
				else if (channels == 3)//�������ͨ�������
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

	//��ֱ����
	for (int i = kerR; i < dst.rows - kerR; i++)
	{
		for (int j = kerR; j < dst.cols - kerR; j++)
		{
			float GuassionSum[3] = { 0 };
			//����������ɸ�˹��ƽ��
			for (int k = -kerR; k <= kerR; k++)
			{

				if (channels == 1)//���ֻ�ǵ�ͨ��
				{
					GuassionSum[0] += arr[kerR + k] * dst.at<float>(i + k, j);//�б䣬�в�����������ֱ����ľ��
				}
				else if (channels == 3)//�������ͨ�������
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
	//����һ����Ӧ��������ľ���
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


//�Ǽ���ֵ����
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
