#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
using namespace std;
using namespace cv;
using namespace xfeatures2d;
int main()
{
	//01输入图像
	Mat srcImage1 = imread("1.jpg");
	Mat srcImage2 = imread("2.jpg");
	imshow("m", srcImage1);
	imshow("n", srcImage2);


	//02使用SURF特征检测寻找关键点
	int minHessian = 8000;
	Ptr<SURF>detector = SURF::create(minHessian);
	
	vector<KeyPoint> keyPoint1, keyPoint2;

	//03检测两幅图像的关键点
	detector->detect(srcImage1, keyPoint1);
	detector->detect(srcImage2, keyPoint2);

	//04 计算描述符
	Ptr<DescriptorExtractor> extractor= xfeatures2d::SURF::create();
	Mat description1, description2;
	extractor->compute(srcImage1, keyPoint1, description1);
	extractor->compute(srcImage2, keyPoint2, description2);
	
	//05 匹配
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
	vector< DMatch > matches;
	matcher->match(description1, description2, matches);

	//06绘制匹配点
	Mat imgMatches;

	drawMatches(srcImage1, keyPoint1, srcImage2, keyPoint2, matches, imgMatches);//进行绘制
	
	//07显示匹配结果
	imshow("匹配图", imgMatches);

	waitKey(0);



	return 0;
}


