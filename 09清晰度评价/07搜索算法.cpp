#include<iostream>
#include<opencv2/opencv.hpp>
#include "evaluate.h"
using namespace std;
using namespace cv;
int main()
{
	//01初始化参数
	bool rst = false;
	int step = 11;
	int t = 3;
	int symbol = 1;
	double minStep = 1;
	const int PictureNum = 33;
	
	//02 初始化图片
	string name = "picture" + to_string(t) + ".jpg";
	Mat src = imread(name);
	
	resize(src, src, Size(1024, 1024));
	
	double value0 = VarianceEvaluate(src);
	double value1;

	//03 搜索
	while (!rst)
	{
		//03-1 往正焦方向移动
		t += symbol*step;
		if (t > PictureNum)t = PictureNum;
		if (t < 1)t = 1;

		//03-2 送入初始值
		name = "picture" + to_string(t) + ".jpg";
		src = imread(name);
		resize(src, src, Size(512, 512));
		value1 = VarianceEvaluate(src);
		
		

		//03-3根据判定值大小变化情况，判断搜索轮数和步长
		//下一个值比上一个值小的时候，说明过了极值点了
		if (value1 <=value0)
		{
			//每轮搜索步长都减半
			step =step / 2;
			
			
			
			//反向搜索
			symbol = -symbol;
		}
		//移交数值
		value0 = value1;
		
		//04终止条件判断
		if (step<1)
		{
			rst = true;
		}
		
	}
	cout << (t+1*symbol) << endl;
	return 0;
}

