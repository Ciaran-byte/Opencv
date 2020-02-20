#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main()
{

	Mat m(500, 500, CV_8UC3, Scalar(255, 255, 0));
	Mat m2(500, 500, CV_8UC3);
	vector<Mat> channels;
	split(m, channels);
	imshow("m", m);
	imshow("0", channels.at(0));
	imshow("1", channels.at(1));
	imshow("2", channels.at(2));

	vector<int> fromTo = {0,2,1,1,2,0};
	mixChannels(m, m2, fromTo);
	vector<Mat> channels2;
	split(m2, channels2);
	imshow("/m", m2);
	imshow("/0", channels2.at(0));
	imshow("/1", channels2.at(1));
	imshow("/2", channels2.at(2));


	waitKey(0);




	return 0;
}
