#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
using namespace std;
using namespace cv;
using namespace xfeatures2d;//特征检测必须指定该命名空间

int main()
{
	Mat m = imread("1.jpg");
	Mat n = imread("3.jpg");
	imshow("m", m);
	imshow("n", n);
	int minHessian = 800;
	
	

	Ptr<SURF>detector = SURF::create(minHessian);

	//以下两种写法也能用
	//Ptr<Feature2D>detector = xfeatures2d::SURF::create(minHessian);
	//Ptr<DescriptorExtractor>detector = xfeatures2d::SURF::create(minHessian);

	vector<KeyPoint> keyPoint1, keyPoint2;

	detector->detect(m, keyPoint1);
	detector->detect(n, keyPoint2);

	Mat mp1, np2;
	drawKeypoints(m, keyPoint1, mp1, Scalar::all(-1), 4);
	drawKeypoints(n, keyPoint2, np2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	imshow("m1", mp1);
	imshow("n1", np2);


	waitKey(0);



	return 0;
}


