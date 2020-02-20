#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	//1.载入图片:应该是灰度图

	Mat m = imread("1.png",0);
	
	

	//2、计算最佳的边界长度
	Size dftsize;
	dftsize.width = getOptimalDFTSize(m.cols);
	dftsize.height = getOptimalDFTSize(m.rows);

	//3、扩充边界
	Mat Re(dftsize, CV_8UC1);
	copyMakeBorder(m, Re, 0, dftsize.height - m.rows, 0, dftsize.width - m.cols, BORDER_CONSTANT);
	
	//4、增加通道
	Mat Im(dftsize, CV_8UC1, Scalar::all(0));

	//5、合并实部和虚部
	vector<Mat> temp = { Mat_<float>(Re),Mat_<float>(Im) };//要做数据类型转换，从uchar变成float
	Mat out(dftsize, CV_32FC2);
	merge(temp, out);
	
	cout << out << endl << endl;
   //6、进行离散傅里叶变换
	dft(out,out,0,0);
	cout << out << endl<<endl;
	
	//7、从复数图中分离出实部和虚部，并且求他们的幅值
	vector<Mat> channels;
	split(out, channels);
	Mat rst;
	magnitude(channels.at(0), channels.at(1), rst);
	cout << rst << endl<<endl;

	//8.把数字取对数，变小
	log(Scalar::all(1) + rst,rst);
	cout << rst << endl<<endl;
	//9.归一化
	normalize(rst, rst, 0, 1, NORM_MINMAX);
	imshow("a", rst);
	cout << rst << endl<<endl;

	//10、裁剪成偶数，并把原点转移到中心来
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

