#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(){
Mat src = imread("pic/girl.jpg", IMREAD_UNCHANGED),dst;
Mat kernel = (Mat_<char>(3,3) << 1, -1, 1, -1, 5, -1, 1, -1, 1);

imshow("Orignal",src);

filter2D(src, dst, src.depth(), kernel);
imshow("filter1",dst);

kernel = (Mat_<char>(3,3) << 1, -2, 3, -4, 5, -6, 7, -8, 9);

filter2D(src, dst, src.depth(), kernel);
imshow("filter2",dst);

waitKey(0);

return 0;
}
