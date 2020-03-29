//#include<iostream>
//#include<opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//int main()
//{
//	//01����洢����
//	Mat sobel_x;
//	Mat sobel_y;
//	Mat sobel_r1;
//	Mat sobel_r2;
//	const int picture_num = 33;
//	for (int t = 1; t <= picture_num; t++)
//	{
//		double t1 = (double)getTickCount();
//
//		//02 ����ͼƬ��
//		string name = "picture" + to_string(t) + ".jpg";
//		Mat src = imread(name, 0);
//
//		//03 ���ĸ������sobel�ݶ�
//		Sobel(src, sobel_x, CV_32F, 1, 0);
//
//
//		Sobel(src, sobel_y, CV_32F, 0, 1);
//
//
//		Mat r1 = (Mat_<float>(3, 3) << 0, 1, 2, -1, 0, 1, -2, -1, 0);
//		filter2D(src, sobel_r1, CV_32F, r1);
//
//
//
//		Mat r2 = (Mat_<float>(3, 3) << -2, -1, 0, -1, 0, 1, 0, 1, 2);
//		filter2D(src, sobel_r2, CV_32F, r2);
//
//
//		//03 ���ĸ��ݶȵ�L1�������ɵľ��󣬲��ҰѾ���ֵ������ֵ��
//		Mat sobel_magnitude(src.cols, src.rows, CV_32FC1);
//		float value;
//		for (int row = 0; row < src.rows; row++)
//		{
//			for (int col = 0; col < src.cols; col++)
//			{
//				value = abs(sobel_x.at<float>(row, col)) + abs(sobel_y.at<float>(row, col))
//					+ abs(sobel_r1.at<float>(row, col)) + abs(sobel_r2.at<float>(row, col));
//				if (value > 255)value = 255;
//				sobel_magnitude.at<float>(row, col) = value;
//			}
//
//		}
//
//		//05 Ѱ��0-200����ֵ�е����ֵ��Ϊ��ֵ
//		const int channels[] = { 0 };
//		Mat hist;
//		int size = 256;
//		const int histSize[] = { size };
//		float range[] = { 0,256 };
//		const float* histRange[] = { range };
//		calcHist(&sobel_magnitude, 1, channels, Mat(), hist, 1, histSize, histRange, true, false);
//
//		int thres;
//		for (int i = 0; i <= 200; i++)
//		{
//
//			if (hist.at<float>(i, 0) != 0)  thres = i;
//		}
//		//cout << thres << endl;
//
//		//06 ������ֵ��������ƽ��ֵ,��Ϊ���յ�����ֵ
//		int num = 0;
//		float sum = 0;
//		for (int row = 0; row < src.rows; row++)
//		{
//			for (int col = 0; col < src.cols; col++)
//			{
//				if (sobel_magnitude.at<float>(row, col) >= thres)
//				{
//					sum += sobel_magnitude.at<float>(row, col);
//					num++;
//				}
//			}
//
//		}
//		//07 ������۽��
//		float result = sum / num;
//		//cout << sum << endl;
//		//cout << num << endl;
//		cout << result << endl;
//		t1 = ((double)getTickCount() - t1) / getTickFrequency();
//		cout << t1 << endl << endl;
//	}
//	return 0;
//}
