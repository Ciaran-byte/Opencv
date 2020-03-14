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
	Mat src2 = imread("3.jpg");
	imshow("src1", src1);
	imshow("src2", src2);

	//02 �����ؼ���

	//02-1ʹ��surf�����жϹؼ���
	int minHessian = 800;//ʹ�ú�ɭ���������ֵ
	Ptr<SURF> detector =SURF::create(minHessian);

	vector<KeyPoint> keyPoint1, keyPoint2;
	detector->detect(src1, keyPoint1);
	detector->detect(src2, keyPoint2);

	//02-2 ���ƹؼ���
	/*Mat dst1, dst2;
	drawKeypoints(src1, keyPoint1, dst1);
	drawKeypoints(src2, keyPoint2, dst2);
	imshow("dst1", dst1);
	imshow("dst2", dst2);*/


	//03 Ϊ�ؼ����������ֵ
	Mat descriptor1, descriptor2;
	detector->compute(src1, keyPoint1, descriptor1);
	detector->compute(src2, keyPoint2, descriptor2);

	//03��ע��������һ�ֿ���ͬʱ���йؼ����������ֵ�����д��
	/*detector->detectAndCompute(src1, Mat(), keyPoint1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keyPoint2, descriptor2);*/

	//04 ƥ��ؼ���
	
	//04-1 flannƥ�䷽��

	//д��1
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptor1, descriptor2, matches);
	
	//д��2
	/*Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);*/
	
	
	//04-2 �Ա�һ�±���ƥ�䷨��д��1
	/*Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
	vector< DMatch > matches;
	matcher->match(descriptor1, descriptor2, matches);*/

	//����ƥ�䷨��д��2
	/*BFMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptor1, descriptor2, matches);*/

	//04-3 ���ƹؼ���ƥ��֮��Ľ��ͼ
	/*Mat m;
	drawMatches(src1, keyPoint1, src2, keyPoint2, matches, m);
	imshow("m", m);*/

	
	//05 ɸѡƥ��Ĺؼ���
	double min_dst = 100;
	double max_dst = 0;
	vector<DMatch> good_matches;
	for (int i = 0; i < matches.size(); i++)
	{
		double distance = matches[i].distance;
		if (distance > max_dst)
		{
			max_dst = distance;
		}
		if (distance < min_dst)
		{
			min_dst = distance;
		}
	}
	cout << max_dst << endl;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < 2 * min_dst)
		{
			good_matches.push_back(matches[i]);
		}
	}


	//06����ƥ����
	Mat out;
	drawMatches(
		src1, keyPoint1,
		src2, keyPoint2,
		good_matches, out,
		Scalar::all(-1), Scalar::all(-1),
		vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
		);
	imshow("out", out);
	waitKey(0);

	return 0;
}


