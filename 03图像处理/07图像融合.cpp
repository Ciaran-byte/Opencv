//该程序用于实现图像拼接

#include<iostream>
#include<opencv2/opencv.hpp>
#include<algorithm>
using namespace std;
using namespace cv;

int main()
{
	//01做图像金字塔的时候，一定要注意是2的倍数，每层金字塔边长都按两倍放缩，如果做5层金字塔，要是32的倍数
	Mat m = imread("apple.png");
	Mat n = imread("orange.png");
	m = m(Rect(0, 0, 224, 224));
	n = n(Rect(0, 0, 224, 224));


	//02做5层高斯金字塔，并放入vector变量的m和n中，大图在前，小图在后,后面是前面尺寸的1/2
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
	//03做拉普拉斯金字塔,第一个图放的是高斯金字塔最底层的最小的那张图片，然后向上采样，原图减去下采样就是拉普拉斯金字塔
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
	

	//05拼接拉普拉斯金字塔,小图在前，大图在后
	vector<Mat> lpConnected;
	
	for (int i = 0; i < 5; i++)
	{
		temp = Mat::zeros(laplacem[i].cols, laplacen[i].rows, CV_8UC3);
		Mat Roi1 = laplacem[i](Rect(0, 0, temp.cols / 2, temp.rows));
		Mat Roi2 = laplacen[i](Rect(temp.cols / 2, 0, temp.cols / 2, temp.rows));

		hconcat(Roi1, Roi2, temp);
		lpConnected.push_back(temp);

	}
	


	
	//06拼接最低分辨率的高斯金字塔，并且构造上级金字塔，并加入拼接拉普拉斯金字塔
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


