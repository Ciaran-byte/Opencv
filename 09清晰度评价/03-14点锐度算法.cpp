#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	const int picture_num = 33;
	for (int t = 1; t <= picture_num; t++)
	{
		double t1 = (double)getTickCount();

		//01 ����ͼƬ��
		string name = "picture" + to_string(t) + ".jpg";
		Mat src = imread(name, 0);

		//02 ����ƫ����
		
		vector<vector<int>> shift = { {-1,0},{1,0},{0,-1},{0,1}, {-1,1},{1,-1},{1,1},{1,-1} };
		//03 ����߽�
		Mat srcMakeBorder;
		copyMakeBorder(src, srcMakeBorder, 2, 2, 2, 2, BORDER_DEFAULT);
		//04 �������������ۺ���
		float value=0;
		for (int row = 2; row < src.rows/5; row++)
		{
			for (int col = 2; col < src.cols/5; col++)
			{
				//ÿ�����ص�8��������ݶ�
				float P=0;
				for (int i = 0; i < 4; i++)
				{
					P += static_cast<float>(abs(srcMakeBorder.at<uchar>(row, col) - srcMakeBorder.at<uchar>(row + shift[i][1], col + shift[i][0])));
				}
				for (int i = 4; i < 8; i++)
				{
					P += static_cast<float>(abs(srcMakeBorder.at<uchar>(row, col) - srcMakeBorder.at<uchar>(row + shift[i][1], col + shift[i][0])))/ pow(2, 0.5);
				}
				value += P;
			}
		}
		
		value = 25*value / static_cast<float>(src.rows * src.cols);
		cout << value << endl;
		t1 = ((double)getTickCount() - t1) / getTickFrequency();
		cout << t1 << endl << endl;
	}

	return 0;
}

