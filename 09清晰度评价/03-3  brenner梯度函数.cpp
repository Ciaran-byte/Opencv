//#include<iostream>
//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main()
//{
//	//01 设定参数
//	const int picture_num = 33;
//	double value;
//	vector<double> Values;
//	for (int t = 1; t <= picture_num; t++)
//	{
//		double t1 = (double)getTickCount();
//
//		//02 读入尺度金字塔
//		string name = "picture" + to_string(t) + ".jpg";
//		Mat m = imread(name);
//		cvtColor(m, m, COLOR_BGR2GRAY);
//
//		//03 扩充图像边界
//		Mat m_make_border;
//		copyMakeBorder(m, m_make_border, 0, 2, 0, 2, BORDER_DEFAULT);
//
//		//04 应用能量梯度函数计算评价值
//		value = 0;
//		for (int i = 0; i < m.rows; i++)
//		{
//
//			for (int j = 0; j < m.cols; j++)
//			{
//				value += pow(m_make_border.at<uchar>(i + 2, j) - m_make_border.at<uchar>(i, j), 2);
//					
//			}
//
//		}
//		//value = log(value + 1);
//		Values.push_back(value);
//
//		t1 = ((double)getTickCount() - t1) / getTickFrequency();
//		cout << value << endl;
//		cout << t1 << endl << endl;
//	}
//
//	////05 输出sobel算子的平方和
//	/*for (int i = 0; i < picture_num; i++)
//	{
//		cout << Values[i] << endl;
//		if (i % 4 == 0)cout << endl;
//	}*/
//
//	return 0;
//}
