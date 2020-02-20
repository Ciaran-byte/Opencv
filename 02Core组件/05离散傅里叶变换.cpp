#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	//1.����ͼƬ:Ӧ���ǻҶ�ͼ

	Mat m = imread("1.png",0);
	
	

	//2��������ѵı߽糤��
	Size dftsize;
	dftsize.width = getOptimalDFTSize(m.cols);
	dftsize.height = getOptimalDFTSize(m.rows);

	//3������߽�
	Mat Re(dftsize, CV_8UC1);
	copyMakeBorder(m, Re, 0, dftsize.height - m.rows, 0, dftsize.width - m.cols, BORDER_CONSTANT);
	
	//4������ͨ��
	Mat Im(dftsize, CV_8UC1, Scalar::all(0));

	//5���ϲ�ʵ�����鲿
	vector<Mat> temp = { Mat_<float>(Re),Mat_<float>(Im) };//Ҫ����������ת������uchar���float
	Mat out(dftsize, CV_32FC2);
	merge(temp, out);
	
	cout << out << endl << endl;
   //6��������ɢ����Ҷ�任
	dft(out,out,0,0);
	cout << out << endl<<endl;
	
	//7���Ӹ���ͼ�з����ʵ�����鲿�����������ǵķ�ֵ
	vector<Mat> channels;
	split(out, channels);
	Mat rst;
	magnitude(channels.at(0), channels.at(1), rst);
	cout << rst << endl<<endl;

	//8.������ȡ��������С
	log(Scalar::all(1) + rst,rst);
	cout << rst << endl<<endl;
	//9.��һ��
	normalize(rst, rst, 0, 1, NORM_MINMAX);
	imshow("a", rst);
	cout << rst << endl<<endl;

	//10���ü���ż��������ԭ��ת�Ƶ�������
	rst = rst(Rect(0, 0, rst.cols & -2, rst.rows & -2));

	int width = rst.cols / 2;
	int height = rst.rows / 2;
	Mat roi1 = rst(Rect(0, 0, width, height));
	Mat roi2 = rst(Rect(width, 0, width , height));
	Mat roi3 = rst(Rect(0, height, width , height));
	Mat roi4 = rst(Rect(width, height, width , height));

	Mat exchange;
	roi4.copyTo(exchange);
	roi1.copyTo(roi4);
	exchange.copyTo(roi1);
	cout << rst << endl;

	roi2.copyTo(exchange);
	roi3.copyTo(roi2);
	exchange.copyTo(roi3);
	imshow("c", rst);

	
	



	waitKey(0);


	return 0;
}

