
//������ӵĹ����ǣ�����Ҫ������ͼƬ�������Ի�ϣ�ͨ�����������������Ի�ϵı���
//����Ҫע����ǣ��������Ի�ϵ�����ͼƬ��С������һ���ģ������޷��ɹ�
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class MyPicture
    //������һ���࣬������Ϊ�������ĵ������������д������ݣ���û��ʹ��ȫ�ֱ����ķ�ʽ����
{
public:
    double alpha;//���Ի�ϵ�alphaֵ
    double beta;//���Ի�ϵ�betaֵ
    Mat m1, m2;//���ڴ���������Ի�ϵ�����ͼƬ
    const int Max=100;//�����������ֵ

    MyPicture(double aplha, double beta, Mat m1, Mat m2) :alpha(alpha), beta(beta), m1(m1), m2(m2) {}
    //���캯��������ʹ�ó�ʼ���б�ķ������б����ĳ�ʼ��

};
void Track(int nowValue, void* p)//�ص�����
{
    MyPicture mp = *(MyPicture*)p; //��void*���͵�ָ����������Ҫ�����ͣ����ܲ���
    Mat m3;//���Ի�ϵ�����������
    double gamma = 0.0;//���Ի�ϵĲ���
    mp.alpha = 1.0 * nowValue / mp.Max;
    mp.beta = 1 - mp.alpha;
    addWeighted(mp.m1, mp.alpha, mp.m2, mp.beta, gamma, m3);//���Ի��
     //���Ի�ϵĹ�ʽΪ ���ͼƬm3 = m1*alpha + m2*beta + gamma; 
    imshow("window", m3);
}

int main()
{
    int nowValue = 100; //���ڼ�¼�������ĵ�ǰ��ֵ
    Mat m1 = imread("1.jpg");//�������Ի�ϵĵ�һ��ͼ
    Mat m2 = imread("2.jpg");//�������Ի�ϵĵڶ���ͼ
    MyPicture mp(1.0, 0.0, m1, m2);//��ʼ������
    Track(nowValue, &mp);//��ʼ��ͼƬ��ʾ
    string TrackName = "͸��ֵ100";
    namedWindow("window", WINDOW_NORMAL);
    createTrackbar(TrackName, "window", &nowValue, mp.Max, Track, &mp);//����������
    waitKey(0);



    return 0;
}

