#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	const int picture_num =33;
	for (int t = 1; t <= picture_num; t++)
	{
		double t1 = (double)getTickCount();

		//01 ����ͼƬ��
		string name = "picture" + to_string(t) + ".jpg";
		Mat src = imread(name, 0);

		//02 ����߽�
		Mat srcMakeBorder;
		int addBorder = 3;
		copyMakeBorder(src, srcMakeBorder, addBorder, addBorder, addBorder, addBorder, BORDER_DEFAULT);


		//03 susan��������������

		//03-1 ����Բ�ε�����
		int OffSetX[37] =
		{
				-1, 0, 1,
			-2, -1, 0, 1, 2,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
			-2, -1, 0, 1, 2,
				-1, 0, 1
		};
		int OffSetY[37] =
		{
				-3, -3, -3,
			-2, -2, -2, -2, -2,
		-1, -1, -1, -1, -1, -1, -1,
			 0, 0, 0, 0, 0, 0, 0,
			 1, 1, 1, 1, 1, 1, 1,
				2, 2, 2, 2, 2,
				   3, 3, 3
		};

		//03 -2 ����ÿһ�����ص��������Ϊǰ���ͼ���������Ҿ�������2���㣬���Ա�����ʱ���
		//��3,3������㿪ʼ����Ϊ����ԭʼͼ���ԭ��
		
		double value = 0;
		for (int row = addBorder; row < src.rows/10; row++)
		{
			for (int col = addBorder; col < src.cols/10; col++)
			{
				int num = 0;//���ڼ���37�����������ĵ��ֵ����Ҫ��ĵ������
				int thres_t = 6;
				int thres_g = 30;
				for (int i = 0; i < 37; i++)
				{
					if (abs(srcMakeBorder.at<uchar>(row, col) -
						srcMakeBorder.at<uchar>(row + OffSetY[i], col + OffSetX[i]) )<= thres_t)
					{
						num++; //�����������������ز�ֵС��thres_t��ʱ����Ϊ���������أ�ͳ���������صĸ�������Ϊ�����������
					}
				}

				//���Ƹ�������С��thres_g��ʱ����Ϊ����Ч���ص㣬���ۼ���Ч���ص�������������
				if (num < thres_g)
				{
					//��Ϊ�����������ԽС��˵�����ص�֮�����Խ������ֵ-��������������Ӳ����ĵ��Ȩ��
					num = thres_g - num;
				}
				else
				{
					num = 0;
				}
				value += num;

			}
		}
		value = log(value+1);
		
		cout << value << endl;
		
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

