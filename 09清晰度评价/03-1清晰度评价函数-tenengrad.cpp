//#include<iostream>
//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main()
//{
//	//01�������
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
//	//02���ļ��ж�����ǰ���ɺõĳ߶Ƚ����������������ǵ�sobel����
//	for (int t = 1; t <= picture_num; t++)
//	{
//		//�����������һ��ѭ����Ҫ��ʱ��
//		double t1 = (double)getTickCount();
//
//		//02-1 ����߶Ƚ�����
//		name = "picture" + to_string(t) + ".jpg";
//		Mat m = imread(name);
//		cvtColor(m, m, COLOR_BGR2GRAY);
//		
//
//		////02-2 ��x����sobel����
//		
//		Sobel(m, s_x, CV_32F, 1, 0);
//		
//		
//
//		////02-3 ��y����sobel����
//		Sobel(m, s_y, CV_32F, 0, 1);
//		
//
//		////02-4 ���ֵ
//		magnitude(s_x, s_y, magnitude_sobel);
//		
//
//		////02-5 ����sobel���ӵ�ƽ����
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
//		//02-6 sobel����ƽ����̫���ˣ�ȡһ�¶���
//		//value = log(value);
//		Values.push_back(value);
//		
//		cout << value << endl;
//		t1 = ((double)getTickCount() - t1) / getTickFrequency();
//		cout << t1 << endl<<endl;
//		
//	}
//
//	////03 ���sobel���ӵ�ƽ����
//	for (int i = 0; i < picture_num; i++)
//	{
//		cout << Values[i] << endl;
//		if (i % 4 == 0)cout << endl;
//	}
//
//	return 0;
//}
