#pragma once
#ifndef EvaluateClass_H_
#define EvaluateClass_H_

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


class EvaluateBaseClass  //����
{
public:
	
	//���캯��,���е�ͼƬ����ֱ�Ӹ��Ƽ��ɣ����洦���������⿪��ͼƬ���и��ƴ�����˴˴�����ԭͼ��ַ���Ե�
	EvaluateBaseClass(const Mat &src):_src(src){}
	//���ۺ�������Ϊ�麯��
	virtual double evaluate() const { return 0.0; }
	//��������������Ϊ�麯��
	virtual ~EvaluateBaseClass(){}
	//����ͼƬ����
	void reset(const Mat& src)
	{
		
		_src = src;
	}

protected:
	Mat _src;
}; 

class VarianceClass :public EvaluateBaseClass //���������
{
public:
	//���캯��
	VarianceClass(const Mat&src):EvaluateBaseClass(src){}
	

	//������ۺ���
	virtual double evaluate()const;
	
	//�����������
	virtual ~VarianceClass(){}
protected:
	
};

class DCTClass :public EvaluateBaseClass //DCT��������
{
public:
	//���캯��
	DCTClass(const Mat& src) :EvaluateBaseClass(src) {}
	//������ۺ���
	virtual double evaluate()const;
	//�����������
	virtual ~DCTClass(){}
protected:

};

class EnergyGradClass :public EvaluateBaseClass //�����ݶȺ�������
{
public:
	//���캯��
	EnergyGradClass(const Mat& src) :EvaluateBaseClass(src) {}

	//������ۺ���
	virtual double evaluate() const;
	//�����������
	virtual ~EnergyGradClass(){}
protected:

};

//��̬�����ۺ���
double dstEvaluate(const EvaluateBaseClass& rhs);


//���ȹ�һ������
void LightNormalize(Mat& src);

//Ԥ������
void PreProcess(Mat& src);
#endif
