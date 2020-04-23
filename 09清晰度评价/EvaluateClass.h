#pragma once
#ifndef EvaluateClass_H_
#define EvaluateClass_H_

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


class EvaluateBaseClass  //基类
{
public:
	
	//构造函数,类中的图片采用直接复制即可，后面处理函数会另外开辟图片进行复制处理，因此此处保存原图地址可以的
	EvaluateBaseClass(const Mat &src):_src(src){}
	//评价函数定义为虚函数
	virtual double evaluate() const { return 0.0; }
	//析构函数，定义为虚函数
	virtual ~EvaluateBaseClass(){}
	//重置图片变量
	void reset(const Mat& src)
	{
		
		_src = src;
	}

protected:
	Mat _src;
}; 

class VarianceClass :public EvaluateBaseClass //方差函数处理
{
public:
	//构造函数
	VarianceClass(const Mat&src):EvaluateBaseClass(src){}
	

	//虚的评价函数
	virtual double evaluate()const;
	
	//虚的析构函数
	virtual ~VarianceClass(){}
protected:
	
};

class DCTClass :public EvaluateBaseClass //DCT函数处理
{
public:
	//构造函数
	DCTClass(const Mat& src) :EvaluateBaseClass(src) {}
	//虚的评价函数
	virtual double evaluate()const;
	//虚的析构函数
	virtual ~DCTClass(){}
protected:

};

class EnergyGradClass :public EvaluateBaseClass //能量梯度函数处理
{
public:
	//构造函数
	EnergyGradClass(const Mat& src) :EvaluateBaseClass(src) {}

	//虚的评价函数
	virtual double evaluate() const;
	//虚的析构函数
	virtual ~EnergyGradClass(){}
protected:

};

//多态的评价函数
double dstEvaluate(const EvaluateBaseClass& rhs);


//亮度归一化函数
void LightNormalize(Mat& src);

//预处理函数
void PreProcess(Mat& src);
#endif
