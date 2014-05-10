/* 
 * File:   FaceRecogniontPCA.h
 * Author: tabk30
 *
 * Created on May 10, 2014, 3:42 PM
 */

#ifndef FACERECOGNIONTPCA_H
#define	FACERECOGNIONTPCA_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class FaceRecogniontPCA {
public:
    FaceRecogniontPCA();
    FaceRecogniontPCA(const FaceRecogniontPCA& orig);
    virtual ~FaceRecogniontPCA();
    vector<string> recognition(Mat& image_input);
private:
    Mat formatImagesForPCA(const vector<Mat> &data);

};

#endif	/* FACERECOGNIONTPCA_H */

