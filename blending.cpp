#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(){
Mat src1 = imread("pic/cat.jpg", IMREAD_COLOR);
Mat src2 = imread("pic/girl.jpg", IMREAD_COLOR);

double alpha = 0.5, beta, gamma = 0; 
beta = 1-alpha;
Mat dst;
addWeighted(src1,alpha,src2,beta,gamma,dst);
imshow("Image belnded", dst);

waitKey(0);

return 0;
}
