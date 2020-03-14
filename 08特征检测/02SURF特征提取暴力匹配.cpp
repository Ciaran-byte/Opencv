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
	//01����ͼ��
	Mat srcImage1 = imread("1.jpg");
	Mat srcImage2 = imread("2.jpg");
	imshow("m", srcImage1);
	imshow("n", srcImage2);


	//02ʹ��SURF�������Ѱ�ҹؼ���
	int minHessian = 8000;
	Ptr<SURF>detector = SURF::create(minHessian);
	
	vector<KeyPoint> keyPoint1, keyPoint2;

	//03�������ͼ��Ĺؼ���
	detector->detect(srcImage1, keyPoint1);
	detector->detect(srcImage2, keyPoint2);

	//04 ����������
	Ptr<DescriptorExtractor> extractor= xfeatures2d::SURF::create();
	Mat description1, description2;
	extractor->compute(srcImage1, keyPoint1, description1);
	extractor->compute(srcImage2, keyPoint2, description2);
	
	//05 ƥ��
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
	vector< DMatch > matches;
	matcher->match(description1, description2, matches);

	//06����ƥ���
	Mat imgMatches;

	drawMatches(srcImage1, keyPoint1, srcImage2, keyPoint2, matches, imgMatches);//���л���
	
	//07��ʾƥ����
	imshow("ƥ��ͼ", imgMatches);

	waitKey(0);



	return 0;
}


