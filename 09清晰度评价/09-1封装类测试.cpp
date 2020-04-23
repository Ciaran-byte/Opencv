#include<iostream>
#include<opencv2/opencv.hpp>
#include"EvaluateClass.h"
using namespace std;
using namespace cv;

int main()
{
	int t = 3;
	string name = "picture" + to_string(t) + ".jpg";
	Mat src = imread(name, 0);
	if (!src.data)return -1;
	EnergyGradClass eng(src);
	cout << dstEvaluate(eng) << endl;
	
	return 0;
}

