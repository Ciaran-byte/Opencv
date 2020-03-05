

#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat src, mask;
Point previousPoint(-1, -1);

void On_Mouse(int event, int x, int y, int flags, void*)
{
	
	if (event == EVENT_FLAG_LBUTTON)
	{
		previousPoint = Point(x, y);
	}
	else if (event ==EVENT_MOUSEMOVE&&(flags&EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
		{
			previousPoint = pt;
		}
		line(src, previousPoint, pt, Scalar::all(255), 5);
		line(mask, previousPoint, pt, Scalar::all(255), 5);
		previousPoint = pt;
		imshow("src", src);
	}
	else
	{
		previousPoint = Point(-1, -1);
	}
}

int main(int argc, char** argv)
{


	Mat src1 = imread("1.jpg");
	mask = Mat::zeros(src1.rows, src1.cols, CV_8U);

	src = src1.clone();
	namedWindow("src");
	imshow("src", src);
	setMouseCallback("src", On_Mouse, 0);

	while (1)
	{
		char c= (char)waitKey();
		if (c == 27)
		{
			break;
		}

		if (c == '2')
		{
			mask = Mat::zeros(src1.rows, src1.cols, CV_8U);
			src = src1.clone();
			imshow("src", src);
		}
		if (c == '1')
		{
			Mat repaire;
			inpaint(src, mask, repaire, 3, INPAINT_TELEA);
			src = repaire.clone();
			imshow("src", repaire);
		}

	}






	waitKey(0);
	return 0;
}

