//#include<iostream>
//#include<opencv2/opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	
//	//FileStorage fs("abc.yml", FileStorage::WRITE);
//	FileStorage fs;
//	fs.open("abc.xml", FileStorage::WRITE);
//
//	//写入数字
//	fs << "Num" << 100;
//
//	//写入Mat
//	Mat R = Mat::eye(3, 3, CV_8UC1);
//	fs << "R" << R;
//
//
//	//写入vector
//	fs << "strings" << "[";
//	fs << "image1.jpg" << "A" << "B";
//	fs << "]";
//
//	//写入map
//	fs << "mapping";
//	fs << "{" << "one" << 1;
//	fs << "two" << 2 << "}";
//
//	
//
//
//
//
//	return 0;
//}
