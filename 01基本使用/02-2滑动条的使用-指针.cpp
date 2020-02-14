
//这个例子的功能是，我们要将两幅图片进行线性混合，通过滑动条来控制线性混合的比例
//这里要注意的是，用于线性混合的两张图片大小必须是一样的，否则无法成功
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class MyPicture
    //定义了一个类，用来作为滑动条的第六个参数进行传递数据，而没有使用全局变量的方式进行
{
public:
    double alpha;//线性混合的alpha值
    double beta;//线性混合的beta值
    Mat m1, m2;//用于存放用于线性混合的两张图片
    const int Max=100;//滑动条的最大值

    MyPicture(double aplha, double beta, Mat m1, Mat m2) :alpha(alpha), beta(beta), m1(m1), m2(m2) {}
    //构造函数，并且使用初始化列表的方法进行变量的初始化

};
void Track(int nowValue, void* p)//回调函数
{
    MyPicture mp = *(MyPicture*)p; //将void*类型的指针变成我们需要的类型，接受参数
    Mat m3;//线性混合的最后的输出结果
    double gamma = 0.0;//线性混合的参数
    mp.alpha = 1.0 * nowValue / mp.Max;
    mp.beta = 1 - mp.alpha;
    addWeighted(mp.m1, mp.alpha, mp.m2, mp.beta, gamma, m3);//线性混合
     //线性混合的公式为 输出图片m3 = m1*alpha + m2*beta + gamma; 
    imshow("window", m3);
}

int main()
{
    int nowValue = 100; //用于记录滑动条的当前数值
    Mat m1 = imread("1.jpg");//用于线性混合的第一张图
    Mat m2 = imread("2.jpg");//用于线性混合的第二张图
    MyPicture mp(1.0, 0.0, m1, m2);//初始化函数
    Track(nowValue, &mp);//初始化图片显示
    string TrackName = "透明值100";
    namedWindow("window", WINDOW_NORMAL);
    createTrackbar(TrackName, "window", &nowValue, mp.Max, Track, &mp);//创建滑动条
    waitKey(0);



    return 0;
}

