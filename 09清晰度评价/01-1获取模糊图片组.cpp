#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
using namespace cv;
using namespace std;

int main()
{
	//01��ȡԭʼͼƬ
	Mat src = imread("cell1.jpg");
	
	if (!src.data)return -1;

	//02�ο�surf������ȡ����ͼ��������ķ����������߶ȿռ�������߶ȿռ�ѡ��4��4��ĸ��
	int octave = 4;
	int level = 4;
	double sigma;
	vector<vector<int>> scale{ {9,15,21,27},{33,45,57,69 },{81,99,117,135 },{153,177,201,225} };
	vector<vector<int>> inverse_scale{ {225,201,177,153},{135,117,99,81},{69,57,45,33},{27,21,15,9} };

	//03 ������������ʹ�ø�˹�˲�������ԭͼ��,�����߶ȿռ�

	//ģ����Ӱ��Զ�����Ĺ���
	int num = 1;
	vector<Mat> pictures;
	Mat dst;

	for (int i = 0; i < octave; i++)
	{
		for (int j = 0; j < level; j++)
		{
			
			sigma = 1.2 * inverse_scale[i][j] / 9;
			GaussianBlur(src, dst, Size(inverse_scale[i][j], inverse_scale[i][j]), sigma, sigma);
			pictures.push_back(dst);
			
			
			string name = "picture" +to_string(num)+".jpg";
			
			imwrite(name, dst);
			num++;
		
		}
		
	}

	//ģ�����λ��
	dst = src.clone();
	pictures.push_back(dst);
	string name = "picture" + to_string(num) + ".jpg";
	imwrite(name, dst);
	num++;

	//ģ��ӽ���Զ�Ĺ���
	for (int i = 0; i < octave; i++)
	{
		for (int j = 0; j < level; j++)
		{

			sigma = 1.2 * scale[i][j] / 9;
			GaussianBlur(src, dst, Size(scale[i][j],scale[i][j]), sigma, sigma);
			pictures.push_back(dst);


			string name = "picture" + to_string(num) + ".jpg";

			imwrite(name, dst);
			num++;

		}

	}

	waitKey(0);

	

	return 0;
}

