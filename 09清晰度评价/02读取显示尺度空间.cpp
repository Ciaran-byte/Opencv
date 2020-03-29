#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace cv;
using namespace std;

int main()
{
for (int i = 1; i <= 33; i++)
{
	string str = "picture" + to_string(i) + ".jpg";
	Mat m = imread(str);
	namedWindow("picture", WINDOW_NORMAL);
	imshow("picture", m);
	waitKey(500);
}
return 0;
}