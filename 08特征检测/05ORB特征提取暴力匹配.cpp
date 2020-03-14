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
	//01 ��ȡͼƬ
	Mat src1 = imread("1.jpg");
	Mat src2 = imread("4.jpg");
	imshow("src1", src1);
	imshow("src2", src2);

	//02 �����ؼ���

	//02-1ʹ��orb�����жϹؼ���
	
	
	
	Ptr<ORB> detector = ORB::create(10);
	vector<KeyPoint> keyPoint1, keyPoint2;
	detector->detect(src1, keyPoint1);
	detector->detect(src2, keyPoint2);



	//03 Ϊ�ؼ����������ֵ
	Mat descriptor1, descriptor2;
	detector->compute(src1, keyPoint1, descriptor1);
	detector->compute(src2, keyPoint2, descriptor2);


	//04 ���ƹؼ���
	Mat dst1, dst2;
	drawKeypoints(src1, keyPoint1, dst1);
	drawKeypoints(src2, keyPoint2, dst2);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	
	//05 ƥ��
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptor1, descriptor2, matches);

	//06��ͼ
	Mat out;
	drawMatches(src1, keyPoint1, src2, keyPoint2, matches, out);
	imshow("out", out);

	waitKey(0);

	return 0;
}


