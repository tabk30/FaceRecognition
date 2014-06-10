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
#include "../lib/PathGenerate.h"
#include "../lib/ImageData.h"
#include "../lib/FaceDetect.h"

using namespace std;
using namespace cv;

class FaceRecogniontPCA {
public:
    FaceRecogniontPCA();
    FaceRecogniontPCA(const FaceRecogniontPCA& orig);
    virtual ~FaceRecogniontPCA();
    vector<string> recognition(string path_name);
    string recognitionAFace(Mat origin);
    void SaveData(Mat eigenvalues, Mat eigenvectors, Mat mean);
    void LoadData();
    string findNearest(Mat input);
    Mat synchronizationImage(Mat image);
    string getLabel(string label);
    Mat norm_0_255(const Mat& src);
    Mat tan_triggs_preprocessing(InputArray src,
            float alpha, float tau , float gamma, int sigma0,
            int sigma1);
    IplImage * face_detect;
    IplImage * face_recognition;
private:
    const static double MAX_DISTENCE = 2700.0;
    Mat formatImagesForPCA(const vector<Mat> &data);
    Mat data;
    PCA pca;
    vector<string> label_train;
    double caculateLimit(string label);
    double caculateALimit(vector<Mat> tmp_Mlist);
    double distance;
    //map<string, double> tmp_Dlist;
};

#endif	/* FACERECOGNIONTPCA_H */

