#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	//01 �趨����
	const int picture_num = 33;
	
	for (int t = 1; t <= picture_num; t++)
	{
		double t1 = (double)getTickCount();
		//02 ����߶Ƚ�����
		string name = "picture" + to_string(t) + ".jpg";
		Mat src = imread(name,0);
		//src.convertTo(src, CV_32FC1, 1.0 / 255);
		src.convertTo(src, CV_32FC1);
		//03 ͼƬ�ָ�Ϊ8x8��С�������

		//03-1 �Ȱ�ͼƬ�߳��任Ϊ8�ı���
		int num_x = src.cols / 8;
		int num_y = src.rows / 8;
		int num = (num_x > num_y ? num_y : num_x);
		//cout << num_x << " " << num_y << " " << num << endl;

		//03-2 ͼƬ��ȡ8�ı����ı߳�
		src = src(Rect(0, 0, num * 8, num * 8));

		


		//04 ��ÿһ������������ɢ���ұ任,��ȡ�Խ��ߵ�ƽ������Ϊ���ۺ���
		float value = 0;
		for (int row = 0; row < num; row++)
		{
			for (int col = 0; col < num; col++)
			{
				Mat ROI = src(Rect(col * 8, row * 8, 8, 8));
				dct(ROI, ROI);
				for (int i = 0; i < 8; i++)
				{
					value += pow(ROI.at<float>(i, i), 2);
				}
			}
		}

		//05 ������ۺ���
		value = value/(src.rows*src.cols);
		value = log(value+1);
		cout << value << endl;
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;

	}
	waitKey(0);
	return 0;
}
