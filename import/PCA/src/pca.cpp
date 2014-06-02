/*
 * Copyright (c) 2012. Philipp Wagner <bytefish[at]gmx[dot]de>.
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http://www.opensource.org/licenses/bsd-license>
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <map>
#include "../lib/PathGenerate.h"
#include "../lib/ImageData.h"
#include "../lib/NearestList.hpp"
#include "../lib/Statistic.hpp"
#include "../lib/FaceRecogniontPCA.h"
using namespace cv;
using namespace std;

extern int g_nValue;
extern vector<string> result_test;


NearestList * findNearest(Mat data, Mat test, vector<string> label) {
    NearestList * nearest = new NearestList();
    //double leastDistSq = 0;
    for (int i = 0; i < data.rows; i++) {
        double euclidean = 0.0f;
        //cout << "size: " << data.cols << endl;
        for (int j = 0; j < data.cols; j++) {
            double temp = test.at<double>(0, j) - data.at<double>(i, j);
            euclidean = euclidean + temp * temp;
        }
        
    }



    return nearest;
}

int findNearestAndPrint(Mat data, Mat test, vector<string> label_train, string label_test) {
    int result = 0;
    double leastDistSq = 1.0f;
    int __nearlest = 0;
    for (int i = 0; i < data.rows; i++) {
        double euclidean = 0.0f;
        euclidean = cv::norm(data.row(i), test, cv::NORM_L2);
        if (i == 0) {
            leastDistSq = euclidean;
            __nearlest = i;
        } else if (euclidean < leastDistSq) {
            leastDistSq = euclidean;
            __nearlest = i;
        }
        //nearest->addElement(label.at(i), i + 1, cbh);

    }

    if (label_train.at(__nearlest).compare(label_test) == 0) {
        //cout << "chinh xac: " << label_train.at(__nearlest) << "---" << label_test << endl;
        result = 1;
    } else {
        //cout << "sai: " << label_train.at(__nearlest) << "---" << label_test << endl;
        result = 0;
    }
    return result;
}

int findThreeNearest(Mat data, Mat test, vector<string> label_train, string label_test) {
    int result = 0;
    //double leastDistSq = 1.0f;
    double nearest_three[3] = {0.0f, 0.0f, 0.0f};
    int __nearest_three[3] = {0, 0, 0};
    //int __nearlest = 0;
    for (int i = 0; i < data.rows; i++) {
        double euclidean = 0.0f, temp = 0.0f;
        int __temp = 0;
        euclidean = cv::norm(data.row(i), test, cv::NORM_L2);
        if (i == 0) {
            nearest_three[0] = euclidean;
            nearest_three[1] = euclidean;
            nearest_three[2] = euclidean;
            __nearest_three[0] = i;
            __nearest_three[1] = i;
            __nearest_three[2] = i;
        } else if (euclidean < nearest_three[2]) {
            nearest_three[2] = euclidean;
            __nearest_three[2] = i;
            if (euclidean < nearest_three[1]) {
                //doi cho
                temp = nearest_three[1];
                __temp = __nearest_three[1];

                nearest_three[1] = nearest_three[2];
                __nearest_three[1] = __nearest_three[2];

                nearest_three[2] = temp;
                __nearest_three[2] = __temp;
                if (euclidean < nearest_three[0]) {
                    temp = nearest_three[0];
                    __temp = __nearest_three[0];

                    nearest_three[0] = nearest_three[1];
                    __nearest_three[0] = __nearest_three[1];

                    nearest_three[1] = temp;
                    __nearest_three[1] = __temp;
                }
            }
        }
        //nearest->addElement(label.at(i), i + 1, cbh);

    }

    for (int i = 0; i < 3; i++) {
        cout << "result of " << i << ": " << __nearest_three[i] << "--" << nearest_three[i] << endl;
        if (label_train.at(__nearest_three[i]).compare(label_test) == 0) {
            cout << "chinh xac: " << label_train.at(__nearest_three[i]) << "---" << label_test << endl;
            result = 1;
        } else {
            
        }
    }
    cout << "sai "<< endl;
    return result;
}

void printfRow(Mat matrix, int i) {
    std::cout << "Matrix content:" << std::endl;
    for (int j = 0; j < matrix.cols; j++) {
        cout << matrix.at<double>(i, j) << "  ";
    }

    cout << endl;
}

Mat formatImagesForPCA(const vector<Mat> &data) {
    Mat dst(static_cast<int> (data.size()), data[0].rows * data[0].cols, CV_32F);
    for (unsigned int i = 0; i < data.size(); i++) {
        Mat image_row = data[i].clone().reshape(1, 1);
        Mat row_i = dst.row(i);
        image_row.convertTo(row_i, CV_32F);
    }

    return dst;
}

int main(int argc, const char *argv[]) {
    FaceRecogniontPCA * pca_test = new FaceRecogniontPCA();
    Mat test;
    pca_test->recognition("/home/tabk30/GR/Image_data/training/668574886/100002325878730_1073741978.jpg");
}