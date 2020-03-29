#pragma once
#ifndef evaluate_H_
#define evaluate_H_

#include<opencv2/opencv.hpp>
using namespace cv;


//01 tenengrad�ݶ����ӽ�������������
double TenenGradEvaluate(const Mat& src);

//02 �����ݶ����ӽ�������������
double EnergyGradEvaluate(const Mat& src);

//03 brenner�ݶ����ӽ�������������
double BrennerGradEvaluate(const Mat& src);

//04 �������ۺ���
double VarianceEvaluate(const Mat& src);

//05 С���任���ۺ���
double WaveletEvaluate(const Mat& src);

//06 ��ɢ���ұ任���ۺ���
 double DctEvaluate(const Mat& src);


//07 �Ľ���sobel�������ۺ���
//����Ľ����ӵ�����ŵ����ڣ��ܹ����ڲ�ͬͼƬ�����������ۣ���������������ͬһ��ͼƬ
double ModifiedSobelEvaluate(const Mat& src);

//08 ����غ������ۺ���
double AutoCorrelationEvaluate(const Mat& src);

//09 ����Աȶ����ۺ���
double ContrastEvaluate(const Mat& src);

//10 susan�������
double SusanEvaluate(const Mat& src);

//11 ������˹�������
double LaplacianEvaluate(const Mat& src);

//12 Roberts����
double RobertsEvaluate(const Mat& src);

//13 prewitt����
double PrewittEvaluate(const Mat& src);

//14 ������㷨
double SharpnessEvaluate(const Mat& src);
//15 ���ȹ�һ������
Mat LightNormalize(const Mat& src);
#endif
