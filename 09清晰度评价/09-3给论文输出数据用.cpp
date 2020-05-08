#include<iostream>
#include<opencv2/opencv.hpp>
#include"EvaluateClass.h"
using namespace std;
using namespace cv;
int main()
{
	double t0 = (double)getTickCount();
	double t1;
	//01初始化参数
	bool rst = false;  //用于判断爬山搜索是否搜索到最后结果
	int step = 11;     //每次搜索的步长，步长缩减到最小值时，认为搜索到了终点
	int t = 3;         //设置用于搜索的第一张图片
	int symbol = 1;     //正向搜索还是反向搜索的标志，搜索过了极值点以后开始反向搜索
	double minStep = 1;  //步长的最小精度
	const int PictureNum = 33; //模拟图片组的数量

	//02 读入模拟图片组的灰度图
	string name = "impulseNoise" + to_string(t) + ".jpg";
	Mat src = imread(name, 0);
	//错误处理
	if (!src.data)return -1;

	//03 定义清晰度评价类

	EnergyGradClass Eng(src);


	//04搜索
	//04-1 搜索的初值
	double value0 = dstEvaluate(Eng);
	double value1;
	std::cout << "图片编号" << t << endl;
	std::cout << "评价值" << value0 << endl;
	t1 = ((double)getTickCount() - t0) / getTickFrequency();
	cout << "对焦时间" << t1*1000 << endl;
	cout << endl;
	while (!rst)
	{
		
		//04-2 往正焦方向移动
		t += symbol * step;
		if (t > PictureNum)t = PictureNum;
		if (t < 1)t = 1;

		//04-3 送入初始值
		name = "picture" + to_string(t) + ".jpg";
		src = imread(name, 0);
		//错误处理
		if (!src.data)return -1;

		Eng.reset(src);


		value1 = dstEvaluate(Eng);

		std::cout << "图片编号" << t << endl;
		std::cout << "评价值" << value1 << endl;
		t1 = ((double)getTickCount() - t0) / getTickFrequency();
		cout << "对焦时间" << t1*1000 << endl;
		cout << endl;

		//04-4根据判定值大小变化情况，判断搜索轮数和步长
		//下一个值比上一个值小的时候，说明过了极值点了
		if (value1 <= value0)
		{
			//每轮搜索步长都减半
			step = step / 2;
			//反向搜索
			symbol = -symbol;
		}
		//移交数值
		value0 = value1;

		//04终止条件判断
		if (step < 1)
		{
			rst = true;
		}
		
	}

	//05 输出最后的结果
	std::cout << (t + 1 * symbol) << endl;
	return 0;
}