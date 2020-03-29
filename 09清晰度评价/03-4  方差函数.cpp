//#include<iostream>
//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main()
//{
//	//01 设定参数
//	const int picture_num = 33;
//	double ave;
//	double variance;
//
//	for (int t = 1; t <= picture_num; t++)
//	{
//		double t1 = (double)getTickCount();
//
//		//02 读入尺度金字塔
//		string name = "picture" + to_string(t) + ".jpg";
//		Mat m = imread(name);
//		cvtColor(m, m, COLOR_BGR2GRAY);
//
//		//03 计算平均值
//		ave=0;
//		for (int i = 0; i < m.rows; i++)
//		{
//			for (int j = 0; j < m.cols; j++)
//			{
//				ave += m.at<uchar>(i, j);
//			}
//		}
//		ave = ave /(static_cast<double>(m.rows) * static_cast<double>( m.cols));
//
//		//04 计算方差
//		variance = 0;
//		for (int i = 0; i < m.rows; i++)
//		{
//			for (int j = 0; j < m.cols; j++)
//			{
//				variance += pow((m.at<uchar>(i, j) - ave), 2);
//			}
//		}
//		//variance = log(variance + 1);
//		t1 = ((double)getTickCount() - t1) / getTickFrequency();
//		cout << variance<<endl;
//		cout << t1 << endl << endl;
//	}
//
//	
//	return 0;
//}
