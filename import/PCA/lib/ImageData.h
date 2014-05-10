/* 
 * File:   ImageData.h
 * Author: tabk30
 *
 * Created on January 22, 2014, 8:49 AM
 */

#ifndef __IMAGEDATA_H__
#define	__IMAGEDATA_H__

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <sys/stat.h>

using namespace std;
using namespace cv;

class ImageData {
public:
    ImageData(int width, int height);
    ImageData(const ImageData& orig);
    virtual ~ImageData();
    int saveImage(const string& filename, vector<Mat>& images, vector<string>& labels);
    void loadImage(const string& filename, vector<Mat>& images, vector<string>& labels);
    string convertInt(int number);
    Mat resizeImage(Mat origin);
private:
    int width;
    int height;
};

#endif	/* IMAGEDATA_H */

