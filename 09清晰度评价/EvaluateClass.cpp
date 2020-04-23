#include<iostream>
#include<opencv2/opencv.hpp>
#include "EvaluateClass.h"
using namespace cv;
using namespace std;



//�����������ۺ���
 double VarianceClass::evaluate() const
{
	 //01�����м����
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

	 //02 ͼƬԤ����
	 PreProcess(gray);
	 //03 ����Ҷ�ͼƽ��ֵ
	 for (int row = 0; row < gray.rows; row++)
	 {
		 for (int col = 0; col < gray.cols; col++)
		 {
			 mean += gray.at<uchar>(row, col);
		 }
	 }
	 mean = mean / (static_cast<double>(gray.rows)* static_cast<double>(gray.cols));

	 //04 ���㷽��
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

//DCT����������ۺ���
 double DCTClass::evaluate() const
 {

	 //01�����м����
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

	 //02 ͼƬԤ����
	 PreProcess(gray);

	 //03 ͼƬ�ָ�Ϊ8x8��С�������
	 //03-1 �Ȱ�ͼƬ�߳��任Ϊ8�ı���
	 int num_x = gray.cols / 8;
	 int num_y = gray.rows / 8;
	 int num = (num_x > num_y ? num_y : num_x);

	 //03-2 ͼƬ��ȡ8�ı����ı߳�
	 gray = gray(Rect(0, 0, num * 8, num * 8));

	 //04 ��ÿһ������������ɢ���ұ任,��ȡ�Խ��ߵ�ƽ������Ϊ���ۺ���

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

	 //������
	 value = value / (static_cast<double>(_src.rows)* static_cast<double>(_src.cols));
	 value = log(value + 1);
	 return value;
 }

//�����ݶȺ���������ۺ���
 double EnergyGradClass::evaluate() const
 {
	 //01�����м����
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

	 //02 ͼƬԤ����
	 PreProcess(gray);
	 //03 ����ͼ��߽�
	 Mat GrayMakeBorder;
	 copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	 //04 �������ݶȺ�����������������
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

 //��̬�����ۺ���
 double dstEvaluate(const EvaluateBaseClass& rhs)
 {
	 return rhs.evaluate();
 }


 //���ȹ�һ������
void LightNormalize( Mat& src)
 {

	
	 Mat mat_mean, mat_stddev;
	// ����ԭͼƬ��ƽ��ֵ�ͷ���ĺ���
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

 //Ԥ������
 void PreProcess(Mat& src)
 {
	 //�ı��С
	 resize(src, src, Size(512, 512));

	 //��˹�˲�
	 GaussianBlur(src, src, Size(3, 3), 0);

	 //���ȹ�һ��
	 LightNormalize(src);
 }
