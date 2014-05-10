/* 
 * File:   FaceRecogniontPCA.cpp
 * Author: tabk30
 * 
 * Created on May 10, 2014, 3:42 PM
 */

#include "../lib/FaceRecogniontPCA.h"

FaceRecogniontPCA::FaceRecogniontPCA() {
}

FaceRecogniontPCA::FaceRecogniontPCA(const FaceRecogniontPCA& orig) {
}

FaceRecogniontPCA::~FaceRecogniontPCA() {
}


Mat FaceRecogniontPCA::formatImagesForPCA(const vector<Mat> &data) {
    Mat dst(static_cast<int> (data.size()), data[0].rows * data[0].cols, CV_32F);
    for (unsigned int i = 0; i < data.size(); i++) {
        Mat image_row = data[i].clone().reshape(1, 1);
        Mat row_i = dst.row(i);
        image_row.convertTo(row_i, CV_32F);
    }

    return dst;
}
