#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

	
	FileStorage fs;
	fs.open("abc.xml", FileStorage::READ);

	//读取数字
	int num;
	fs["Num"] >> num;
	cout << num << endl;

	//读取Mat
	Mat R;
	fs["R"] >> R;
	cout << R << endl;

	////写入vector
	//fs << "strings" << "[";
	//fs << "image1.jpg" << "A" << "B";
	//fs << "]";

	////写入map
	//fs << "mapping";
	//fs << "{" << "one" << 1;
	//fs << "two" << 2 << "}";

	//读取Vector
	FileNode n = fs["strings"];
	FileNodeIterator it = n.begin(), end = n.end();
	for (; it != end; it++)
	{
		cout << (string)(*it)<<endl;
	}

	//文件释放,也可以不使用这个析构函数
	fs.release();





	return 0;
}
