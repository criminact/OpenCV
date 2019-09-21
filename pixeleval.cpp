#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(){

Mat src = imread("pic/cat.jpg", IMREAD_COLOR);

Vec3b inten = src.at<Vec3b>(50,50);

cout << (int)inten.val[0] << ',' << (int)inten.val[1] << ',' << (int)inten.val[2];


imshow("src", src);

waitKey(0);
	
return 0;
}

