#include<iostream>
#include "evaluate.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


double TenenGradEvaluate(const Mat& src)
{
	//01�����м����
	Mat gray;
	Mat sobel_x;
	Mat sobel_y;
	Mat sobel_magnitude;
	double value = 0;
	//02 ��ͼƬ��Ϊ�Ҷ�ͼ
	
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//03 ��x����sobel����
	Sobel(gray, sobel_x, CV_32F, 1, 0);

	//04 ��y����sobel����
	Sobel(gray, sobel_y, CV_32F, 0, 1);

	//05 ���ֵ
	magnitude(sobel_x, sobel_y, sobel_magnitude);

	////06 ����sobel���ӵ�ƽ����
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
	//01�����м����
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
	//02 ����ͼ��߽�
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 �������ݶȺ�����������������
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
	//01�����м����
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

	//02 ����ͼ��߽�
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 Ӧ��brenner�ݶȺ�����������ֵ
	
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
	//01�����м����
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

	//02 ����Ҷ�ͼƽ��ֵ
	for (int row = 0; row < gray.rows; row++)
	{
		for (int col = 0; col < gray.cols; col++)
		{
			mean += gray.at<uchar>(row, col);
		}
	}
	mean = mean / (static_cast<double>(gray.rows)* static_cast<double>(gray.cols));
	
	//03 ���㷽��
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

	//01�����м����
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

	//02 ��������ĸ�ͨ�˲���
	Mat kernal = (
		Mat_<double>(3, 3) <<
		-1.0 / 16, -1.0 / 8, -1.0 / 16,
		-1.0 / 8, 3.0 / 4, -1.0 / 8,
		-1.0 / 16, -1.0 / 8, -1.0 / 16
		);

	//03 ͼ�����ͨ�˲������
	Mat dst;
	filter2D(gray, dst, CV_32F, kernal);

	//04 ��������ֵ
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
	//01�����м����
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
	//02 ͼƬ�ָ�Ϊ8x8��С�������
	//02-1 �Ȱ�ͼƬ�߳��任Ϊ8�ı���
	int num_x = gray.cols / 8;
	int num_y = gray.rows / 8;
	int num = (num_x > num_y ? num_y : num_x);

	//02-2 ͼƬ��ȡ8�ı����ı߳�
	gray = gray(Rect(0, 0, num * 8, num * 8));

	//03 ��ÿһ������������ɢ���ұ任,��ȡ�Խ��ߵ�ƽ������Ϊ���ۺ���
	
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
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	value = log(value + 1);
	return value;
}


double ModifiedSobelEvaluate(const Mat& src)
{
	//01�����м����
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
	
	//02 ���ĸ������sobel�ݶ�
	Sobel(gray, sobel_x, CV_32F, 1, 0);

	Sobel(gray, sobel_y, CV_32F, 0, 1);

	Mat r1 = (Mat_<float>(3, 3) << 0, 1, 2, -1, 0, 1, -2, -1, 0);
	filter2D(gray, sobel_r1, CV_32F, r1);

	Mat r2 = (Mat_<float>(3, 3) << -2, -1, 0, -1, 0, 1, 0, 1, 2);
	filter2D(gray, sobel_r2, CV_32F, r2);

	//03 ���ĸ��ݶȵ�L1�������ɵľ��󣬲��ҰѾ���ֵ������ֵ��
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

	//04 Ѱ��0-200����ֵ�е����ֵ��Ϊ��ֵ,ͨ��ֱ��ͼ�ķ���Ѱ��ǰ200�������еķ���ֵ�������ҵ�������ֵ
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

	//06 ������ֵ��������ƽ��ֵ,��Ϊ���յ�����ֵ
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
	//07 ������
	double result = value / num;
	return result;
}

double AutoCorrelationEvaluate(const Mat& src)
{
	//01�����м����
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 ����ͼ��߽�
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 ��������غ����Խ�������������
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

	//������
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}


double ContrastEvaluate(const Mat& src)
{
	//01�����м����
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 ����߽�
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 2, 2, 2, 2, BORDER_DEFAULT);

	//03 ��������غ����Խ�������������

		//����Աȶȼ���ԭ��������ͼ�����������ص㼰������ķ�Χ�ڵ����ֵ����Сֵ
		// ÿ�����ص�����ֵΪmax-min/max
		//�������ص�����ֵ��Ӿ������յ�����ֵ
		// �ü��㷽���������Ƚϴ������ٶȱȽ���

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
		//������
	value = log(value + 1);
		return value;
	
}

double SusanEvaluate(const Mat& src)
{
	//01�����м����
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 ����߽�
	Mat GrayMakeBorder;
	int addBorder = 3;
	copyMakeBorder(gray, GrayMakeBorder, addBorder, addBorder, addBorder, addBorder, BORDER_DEFAULT);

	//03 susan��������������
	//03-1 ����Բ�ε�����
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
	//03 -2 ����ÿһ�����ص��������Ϊǰ���ͼ���������Ҿ�������3���㣬���Ա�����ʱ���
			//��3,3������㿪ʼ����Ϊ����ԭʼͼ���ԭ��

	double value = 0;
	for (int row = addBorder; row < gray.rows; row++)
	{
		for (int col = addBorder; col < gray.cols ; col++)
		{
			int num = 0;//���ڼ���37�����������ĵ��ֵ����Ҫ��ĵ������
			int thres_t = 5;
			int thres_g = 30;
			for (int i = 0; i < 37; i++)
			{
				if (abs(GrayMakeBorder.at<uchar>(row, col) -
					GrayMakeBorder.at<uchar>(row + OffSetY[i], col + OffSetX[i])) <= thres_t)
				{
					num++; //�����������������ز�ֵС��thres_t��ʱ����Ϊ���������أ�ͳ���������صĸ�������Ϊ�����������
				}
			}

			//���Ƹ�������С��thres_g��ʱ����Ϊ����Ч���ص㣬���ۼ���Ч���ص�������������
			if (num < thres_g)
			{
				//��Ϊ�����������ԽС��˵�����ص�֮�����Խ������ֵ-��������������Ӳ����ĵ��Ȩ��
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
	//01�����м����
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 ��ͼƬ��������˹���ӽ��о��
	Mat dst;
	Laplacian(gray, dst, CV_32F, 3);
	convertScaleAbs(dst, dst);

	//03 ��������˹���ӵ�ƽ����
	double value = 0;
	for (int row = 0; row < dst.rows; row++)
	{
		for (int col = 0; col < dst.cols; col++)
		{
			value += dst.at<uchar>(row, col);
		}
	}
	
	//������
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double RobertsEvaluate(const Mat& src)
{
	//01�����м����
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 ����ͼ��߽�
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 0, 2, 0, 2, BORDER_DEFAULT);

	//03 ��roberts�ݶȺ�
	double value = 0;
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			value += abs(static_cast<double>(GrayMakeBorder.at<uchar>(row, col)) - static_cast<double>(GrayMakeBorder.at<uchar>(row + 1, col + 1)))
				+ abs(static_cast<double>(GrayMakeBorder.at<uchar>(row, col + 1)) - static_cast<double>(GrayMakeBorder.at<uchar>(row + 1, col)));
		}
	}
	//������
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double PrewittEvaluate(const Mat& src)
{
	//01�����м����
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 ����prewitt���Ӿ����
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

	//03 ���������ݶȷ��������Ǹ���Ϊ�ݶ�ֵ���������������۲���
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
	//������
	value = value / (static_cast<double>(src.rows)* static_cast<double>(src.cols));
	return value;
}

double SharpnessEvaluate(const Mat& src)
{
	//01�����м����
	Mat gray;
	if (src.channels() == 3)
	{

		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	if (src.channels() == 1)
	{
		gray = src.clone();
	}

	//02 ����ƫ����
	vector<vector<int>> shift = { {-1,0},{1,0},{0,-1},{0,1}, {-1,1},{1,-1},{1,1},{1,-1} };

	//03 ����߽�
	Mat GrayMakeBorder;
	copyMakeBorder(gray, GrayMakeBorder, 2, 2, 2, 2, BORDER_DEFAULT);

	//04 �������������ۺ���
	double value = 0;
	for (int row = 2; row < src.rows ; row++)
	{
		for (int col = 2; col < src.cols; col++)
		{
			//ÿ�����ص�8��������ݶ�
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
