#pragma once
#ifndef evaluate_H_
#define evaluate_H_

#include<opencv2/opencv.hpp>
using namespace cv;


//01 tenengrad梯度算子进行清晰度评价
double TenenGradEvaluate(const Mat& src);

//02 能量梯度算子进行清晰度评价
double EnergyGradEvaluate(const Mat& src);

//03 brenner梯度算子进行清晰度评价
double BrennerGradEvaluate(const Mat& src);

//04 方差评价函数
double VarianceEvaluate(const Mat& src);

//05 小波变换评价函数
double WaveletEvaluate(const Mat& src);

//06 离散余弦变换评价函数
 double DctEvaluate(const Mat& src);


//07 改进的sobel算子评价函数
//这个改进算子的最大优点在于，能够用于不同图片的清晰度评价，而不仅仅局限于同一张图片
double ModifiedSobelEvaluate(const Mat& src);

//08 自相关函数评价函数
double AutoCorrelationEvaluate(const Mat& src);

//09 区域对比度评价函数
double ContrastEvaluate(const Mat& src);

//10 susan检测算子
double SusanEvaluate(const Mat& src);

//11 拉普拉斯检测算子
double LaplacianEvaluate(const Mat& src);

//12 Roberts算子
double RobertsEvaluate(const Mat& src);

//13 prewitt算子
double PrewittEvaluate(const Mat& src);

//14 点锐度算法
double SharpnessEvaluate(const Mat& src);
//15 亮度归一化函数
Mat LightNormalize(const Mat& src);
#endif
