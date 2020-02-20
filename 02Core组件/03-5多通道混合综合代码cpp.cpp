#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	//��ȡͼƬ��logo
	Mat srcImg = imread("dota.jpg");
	Mat logo = imread("dota_logo.jpg",0);
	

	//������ɫͨ��
	vector<Mat> channels;
	split(srcImg, channels);
	Mat blue = channels.at(0);
	

	//���Ի��
	Mat ROI = blue(Rect(500, 250, logo.cols, logo.rows)); //���Ի��ע���������⣨1������ͼƬ��СҪһ����2������ͼƬͨ����Ҫһ��
	
	
	addWeighted(ROI, 1.0, logo, 0.5, 0, ROI);
	
	
	//�ϲ�ͨ��
	merge(channels, srcImg);
	imshow("srcImg", srcImg);


	waitKey(0);

	return 0;
}




