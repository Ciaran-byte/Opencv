#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat a = (Mat_<uchar>(3,3) << 1, 2, 3, 1, 2, 3, 1, 2, 3);
	//Mat a = imread("1.jpg");
	Mat b;
	copyMakeBorder(a, b, 4, 4, 4, 4, BORDER_REFLECT);
	cout << b<<endl;
	//imshow("b", b);
	waitKey(0);

	return 0;
}

