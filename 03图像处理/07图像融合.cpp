//�ó�������ʵ��ͼ��ƴ��

#include<iostream>
#include<opencv2/opencv.hpp>
#include<algorithm>
using namespace std;
using namespace cv;

int main()
{
	//01��ͼ���������ʱ��һ��Ҫע����2�ı�����ÿ��������߳��������������������5���������Ҫ��32�ı���
	Mat m = imread("apple.png");
	Mat n = imread("orange.png");
	m = m(Rect(0, 0, 224, 224));
	n = n(Rect(0, 0, 224, 224));


	//02��5���˹��������������vector������m��n�У���ͼ��ǰ��Сͼ�ں�,������ǰ��ߴ��1/2
	Mat temp,temp1;
	vector<Mat> Vm{ m };
	vector<Mat> Vn{ n };
	for (int i = 0; i < 5; i++)
	{
		pyrDown(Vm[i], temp);
		Vm.push_back(temp);
		
		pyrDown(Vn[i], temp1);
		Vn.push_back(temp1);
	}
	//03��������˹������,��һ��ͼ�ŵ��Ǹ�˹��������ײ����С������ͼƬ��Ȼ�����ϲ�����ԭͼ��ȥ�²�������������˹������
	vector<Mat> laplacem{ Vm[4] };
	vector<Mat>laplacen{ Vn[4] };
	
	
	for (int i = 0; i < 4; i++)
	{
		pyrUp(Vm[4- i], temp);
		subtract(Vm[3 - i], temp, temp);
		laplacem.push_back(temp);

		pyrUp(Vn[4 - i], temp1);
		subtract(Vn[3 - i], temp1, temp1);
		laplacen.push_back(temp1);
	}
	

	//05ƴ��������˹������,Сͼ��ǰ����ͼ�ں�
	vector<Mat> lpConnected;
	
	for (int i = 0; i < 5; i++)
	{
		temp = Mat::zeros(laplacem[i].cols, laplacen[i].rows, CV_8UC3);
		Mat Roi1 = laplacem[i](Rect(0, 0, temp.cols / 2, temp.rows));
		Mat Roi2 = laplacen[i](Rect(temp.cols / 2, 0, temp.cols / 2, temp.rows));

		hconcat(Roi1, Roi2, temp);
		lpConnected.push_back(temp);

	}
	


	
	//06ƴ����ͷֱ��ʵĸ�˹�����������ҹ����ϼ���������������ƴ��������˹������
	vector<Mat> gauConnected;
	temp = Mat::zeros(Vm[4].cols, Vm[4].rows, CV_8UC3);
	Mat Roi1 = Vm[4](Rect(0, 0, temp.cols / 2, temp.rows));
	Mat Roi2 = Vn[4](Rect(temp.cols / 2, 0, temp.cols / 2, temp.rows));
	hconcat(Roi1, Roi2, temp);
	gauConnected.push_back(temp);
	
	
	for (int i = 0; i < 4; i++)
	{
		
	
		pyrUp(gauConnected[i], temp);
		add(temp, lpConnected[i+1],temp);
		gauConnected.push_back(temp);
		
	}
	
	
	imshow("a", gauConnected[4]);
	
	
	waitKey(0);
	return 0;
}


