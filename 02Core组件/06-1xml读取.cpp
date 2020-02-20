#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

	
	FileStorage fs;
	fs.open("abc.xml", FileStorage::READ);

	//��ȡ����
	int num;
	fs["Num"] >> num;
	cout << num << endl;

	//��ȡMat
	Mat R;
	fs["R"] >> R;
	cout << R << endl;

	////д��vector
	//fs << "strings" << "[";
	//fs << "image1.jpg" << "A" << "B";
	//fs << "]";

	////д��map
	//fs << "mapping";
	//fs << "{" << "one" << 1;
	//fs << "two" << 2 << "}";

	//��ȡVector
	FileNode n = fs["strings"];
	FileNodeIterator it = n.begin(), end = n.end();
	for (; it != end; it++)
	{
		cout << (string)(*it)<<endl;
	}

	//�ļ��ͷ�,Ҳ���Բ�ʹ�������������
	fs.release();





	return 0;
}
