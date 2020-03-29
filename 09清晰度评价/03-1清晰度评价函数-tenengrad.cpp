//#include<iostream>
//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main()
//{
//	//01定义变量
//	
//	vector<float> Values;
//
//	Mat s_x;
//	Mat s_y;
//	Mat magnitude_sobel;
//
//	const int picture_num=33;
//	float value;
//
//	string name;
//
//	//02从文件中读入提前生成好的尺度金字塔，并且求他们的sobel算子
//	for (int t = 1; t <= picture_num; t++)
//	{
//		//计算程序运行一个循环需要的时间
//		double t1 = (double)getTickCount();
//
//		//02-1 读入尺度金字塔
//		name = "picture" + to_string(t) + ".jpg";
//		Mat m = imread(name);
//		cvtColor(m, m, COLOR_BGR2GRAY);
//		
//
//		////02-2 求x方向sobel算子
//		
//		Sobel(m, s_x, CV_32F, 1, 0);
//		
//		
//
//		////02-3 求y方向sobel算子
//		Sobel(m, s_y, CV_32F, 0, 1);
//		
//
//		////02-4 求幅值
//		magnitude(s_x, s_y, magnitude_sobel);
//		
//
//		////02-5 计算sobel算子的平方和
//		value = 0;
//		
//		for (int i = 0; i < magnitude_sobel.rows; i++)
//		{
//			for (int j = 0; j < magnitude_sobel.cols; j++)
//			{
//				
//				value += magnitude_sobel.at<float>(i, j) * magnitude_sobel.at<float>(i, j);
//				
//				
//			}
//		}
//
//		//02-6 sobel算子平方和太大了，取一下对数
//		//value = log(value);
//		Values.push_back(value);
//		
//		cout << value << endl;
//		t1 = ((double)getTickCount() - t1) / getTickFrequency();
//		cout << t1 << endl<<endl;
//		
//	}
//
//	////03 输出sobel算子的平方和
//	for (int i = 0; i < picture_num; i++)
//	{
//		cout << Values[i] << endl;
//		if (i % 4 == 0)cout << endl;
//	}
//
//	return 0;
//}
