#include <iostream>
#include "opencv2/opencv.hpp"
#include <zbar.h>

using namespace std;
using namespace cv;
using namespace zbar;


typedef struct
{
  string type;
  string data;
  vector <Point> location;
} decodedObject;

  vector<decodedObject> decodedObjects;


Mat display(Mat &im, vector<decodedObject>&decodedObjects)
{
  // Loop over all decoded objects
  for(int i = 0; i < decodedObjects.size(); i++)
  {
    vector<Point> points = decodedObjects[i].location;
    vector<Point> hull;
     
    // If the points do not form a quad, find convex hull
    if(points.size() > 4)
      convexHull(points, hull);
    else
      hull = points;
     
    // Number of points in the convex hull
    int n = hull.size();
     
    for(int j = 0; j < n; j++)
    {
      line(im, hull[j], hull[ (j+1) % n], Scalar(255,0,0), 3);
    }
     
  }
  
return im;
}
void decode(Mat &im, vector<decodedObject>&decodedObjects)
{
   
  // Create zbar scanner
 ImageScanner scanner;
 
  // Configure scanner
  scanner.set_config(ZBAR_NONE,ZBAR_CFG_ENABLE, 1);
   
  // Convert image to grayscale
  Mat imGray;
  cvtColor(im, imGray,CV_BGR2GRAY);
 
  // Wrap image data in a zbar image
  Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);
 
  // Scan the image for barcodes and QRCodes
  int n = scanner.scan(image);
   
  // Print results
  for(SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
  {
    decodedObject obj;
     
    obj.type = symbol->get_type_name();
    obj.data = symbol->get_data();
     
    // Print type and data
    cout << "Type : " << obj.type << endl;
    cout << "Data : " << obj.data << endl << endl;
     
    // Obtain location
    for(int i = 0; i< symbol->get_location_size(); i++)
    {
      obj.location.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
    }
     
    decodedObjects.push_back(obj);
  }
}
int main(int argc, char* argv[])
{
Mat framed, frame;

VideoCapture cap(0);
if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

for(;;){
cap >> frame;
framed = frame;

decode(framed,decodedObjects);
framed = display(framed,decodedObjects);


imshow("input",frame);
imshow("output",framed);


decodedObjects.clear();

char c = waitKey(27);
if(c == 27)break;

}

  return 0;
}
