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

using namespace cv;
using namespace std;

// Reads the images and labels from a given CSV file, a valid file would
// look like this:
//
//      /path/to/person0/image0.jpg;0
//      /path/to/person0/image1.jpg;0
//      /path/to/person1/image0.jpg;1
//      /path/to/person1/image1.jpg;1
//      ...
//

// Normalizes a given image into a value range between 0 and 255.

//int truth_number = 0, wrong_number = 0;

extern int g_nValue;
extern vector<string> result_test;

Mat norm_0_255(const Mat& src) {
    // Create and return normalized image:
    Mat dst;
    switch (src.channels()) {
        case 1:
            cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
            break;
        case 3:
            cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
            break;
        default:
            src.copyTo(dst);
            break;
    }
    return dst;
}

void printfMatrix(Mat matrix) {
    std::cout << "Matrix content:" << std::endl;
    cout << "matrix row: " << matrix.rows << "matrix cols: " << matrix.cols << endl;

    for (int i = 0; i < matrix.rows; i++) {

        for (int j = 0; j < matrix.cols; j++) {
            cout << matrix.at<double>(i, j) << "  ";
        }

        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    std::cout << "END" << std::endl;
}

Mat copyMatrix(Mat from) {
    Mat to;
    to.create(1, from.cols * from.rows, from.type());

    for (int i = 0; i < from.rows; i++) {

        for (int j = 0; j < from.cols; j++) {
            to.at<double>(0, j + i * j) = from.at<double>(i, j);
            //cout << "from: " << from.at<double>(i, j) << " to: " << to.at<double>(0, j + i*j) << endl;
        }
    }
    return to;
}

// Converts the images given in src into a row matrix.

Mat asRowMatrix(const vector<Mat>& src, int rtype, double alpha = 1, double beta = 0) {
    // Number of samples:
    size_t n = src.size();
    // Return empty matrix if no matrices given:
    if (n == 0)
        return Mat();
    // dimensionality of (reshaped) samples
    size_t d = src[0].total();
    // Create resulting data matrix:
    Mat data(n, d, rtype);
    // Now copy data:
    for (unsigned int i = 0; i < n; i++) {
        //
        if (src[i].empty()) {
            string error_message = format("Image number %d was empty, please check your input data.", i);
            CV_Error(CV_StsBadArg, error_message);
        }
        // Make sure data can be reshaped, throw a meaningful exception if not!
        if (src[i].total() != d) {
            string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src[i].total());
            CV_Error(CV_StsBadArg, error_message);
        }
        // Get a hold of the current row:
        Mat xi = data.row(i);
        // Make reshape happy by cloning for non-continuous matrices:
        if (src[i].isContinuous()) {
            //src[i].reshape(1, 1).convertTo(xi, rtype, alpha, beta);
            xi = copyMatrix(src[i]);
        } else {
            //src[i].clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
            xi = copyMatrix(src[i]);
        }


    }
    //waitKey(0);
    return data;
}

//find nearest

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
        //cbh = sqrt(euclidean);

        //        if (euclidean < leastDistSq) {
        //            leastDistSq = euclidean;
        //            nearest = i;
        //        }
        //nearest->addElement(label.at(i), i + 1, cbh);

    }



    return nearest;
}

int findNearestAndPrint(Mat data, Mat test, vector<string> label_train, string label_test) {
    int result = 0;
    double leastDistSq = 1.0f;
    int __nearlest = 0;
    for (int i = 0; i < data.rows; i++) {
        double euclidean = 0.0f;
        //cout << "size: " << data.cols << endl;
        //        for (int j = 0; j < data.cols; j++) {
        //            double temp = test.at<double>(0, j) - data.at<double>(i, j);
        //            euclidean = euclidean + temp * temp;
        //        }
        //        euclidean = sqrt(euclidean);
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
        cout << "chinh xac: " << label_train.at(__nearlest) << "---" << label_test << endl;
        result = 1;
    } else {
        cout << "sai: " << label_train.at(__nearlest) << "---" << label_test << endl;
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

//PCA compressPCA(InputArray pcaset, int maxComponents,
//        const Mat& testset, Mat compressed) {
//    PCA pca(pcaset, // pass the data
//            Mat(), // there is no pre-computed mean vector,
//            // so let the PCA engine to compute it
//            CV_PCA_DATA_AS_ROW, // indicate that the vectors
//            // are stored as matrix rows
//            // (use CV_PCA_DATA_AS_COL if the vectors are
//            // the matrix columns)
//            maxComponents // specify how many principal components to retain
//            );
//    // if there is no test data, just return the computed basis, ready-to-use
//    if (!testset.data)
//        return pca;
//    CV_Assert(testset.cols == pcaset.cols);
//
//    compressed.create(testset.rows, maxComponents, testset.type());
//
//    Mat reconstructed;
//    for (int i = 0; i < testset.rows; i++) {
//        Mat vec = testset.row(i), coeffs = compressed.row(i);
//        // compress the vector, the result will be stored
//        // in the i-th row of the output matrix
//        pca.project(vec, coeffs);
//        // and then reconstruct it
//        pca.backProject(coeffs, reconstructed);
//        // and measure the error
//        printf("%d. diff = %g\n", i, norm(vec, reconstructed, NORM_L2));
//    }
//    return pca;
//}

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

    ImageData * image_process = new ImageData(100, 100);
    PathGenerate * path = new PathGenerate("/home/tabk30/programming/c++/PCA/Image/PGM/profie_face/train", "Info/train.txt");
    path->generate();
    delete path;

    path = new PathGenerate("/home/tabk30/programming/c++/PCA/Image/PGM/profie_face/test", "Info/test.txt");
    path->generate();
    delete path;
    //Statistic * statistic = new Statistic();
    ///////////////////////////////////////////////////////////////////
    vector<Mat> db, test_db;
    vector<string> labels, truth;
    image_process->loadImage("Info/train.txt", db, labels);
    image_process->loadImage("Info/test.txt", test_db, truth);
    Mat train = formatImagesForPCA(db);
    Mat test = formatImagesForPCA(test_db);
    //image_process->saveImage("/home/tabk30/programming/c++/PCA/Image/PGM/frontal face/train", db, labels);
    //image_process->saveImage("/home/tabk30/programming/c++/PCA/Image/PGM/frontal face/test", test_db, truth);
    ///////////////////////////////////////////////////////////////////


    //int component = 50;
    PCA pca(train, cv::Mat(), CV_PCA_DATA_AS_ROW, 0.95);
    Mat train_compress, test_compressed;
    test_compressed.create(test.rows, db.size(), test.type());
    train_compress.create(train.rows, db.size(), train.type());
    for (int i = 0; i < train_compress.rows; i++) {
        Mat vec = train.row(i), coeffs = train_compress.row(i);
        // compress the vector, the result will be stored
        // in the i-th row of the output matrix
        pca.project(vec, coeffs);
        // and then reconstruct it
        //pca.backProject(coeffs, reconstructed);
        // and measure the error
        //printf("%d. diff = %g\n", i, norm(vec, reconstructed, NORM_L2));
        //printfRow(coeffs, i);
    }
    
    for (int i = 0; i < test.rows; i++) {
        Mat vec = test.row(i), coeffs = test_compressed.row(i);
        // compress the vector, the result will be stored
        // in the i-th row of the output matrix
        pca.project(vec, coeffs);
        //pca.eigenvalues.cols;
        // and then reconstruct it
        //pca.backProject(coeffs, reconstructed);
        // and measure the error
        //printf("%d. diff = %g\n", i, norm(vec, reconstructed, NORM_L2));
        //printfRow(coeffs, i);
    }


    //printfRow(db_supspace, 0);
    int truth_number = 0, wrong_number = 0;
    vector<int> test_result_label;
    for (int i = 0; i < test_compressed.rows; i++) {
        Mat temp = test_compressed.row(i);
        int test_result = 0;
        test_result = findThreeNearest(train_compress, temp, labels, truth.at(i));
        cout << i;
        if (test_result == 0) {
            wrong_number++;
        } else {
            truth_number++;
        }
        //cout << "truth: " << truth.at(i) << endl;
        //nearest->printList();
        //statistic->addTest(truth.at(i), i + 1, nearest);
    }
    cout << "test sum: " << test_compressed.rows << endl;
    cout << "   truth: " << truth_number << endl << "  wrong: " << wrong_number;
    //statistic->printStatistic();
    return 0;
}