/* 
 * File:   pca_test.cpp
 * Author: tabk30
 *
 * Created on February 28, 2014, 11:21 AM
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../lib/PathGenerate.h"
#include "../lib/ImageData.h"

using namespace cv;
using namespace std;

///////////////////////
// Functions
//static void read_imgList(const string& filename, vector<Mat>& images) {
//    std::ifstream file(filename.c_str(), ifstream::in);
//    if (!file) {
//        string error_message = "No valid input file was given, please check the given filename.";
//        CV_Error(Error::StsBadArg, error_message);
//    }
//    string line;
//    while (getline(file, line)) {
//        images.push_back(imread(line, 0));
//    }
//}

static  Mat formatImagesForPCA(const vector<Mat> &data)
{
    Mat dst(static_cast<int>(data.size()), data[0].rows*data[0].cols, CV_32F);
    for(unsigned int i = 0; i < data.size(); i++)
    {
        Mat image_row = data[i].clone().reshape(1,1);
        Mat row_i = dst.row(i);
        image_row.convertTo(row_i,CV_32F);
    }
    return dst;
}

static Mat toGrayscale(InputArray _src) {
    Mat src = _src.getMat();
    // only allow one channel
    if(src.channels() != 1) {
        //CV_Error(Error::StsBadArg, "Only Matrices with one channel are supported");
        return src;
    }
    // create and return normalized image
    Mat dst;
    cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
    return dst;
}

struct params
{
    Mat data;
    int ch;
    int rows;
    PCA pca;
    string winName;
};

static void onTrackbar(int pos, void* ptr)
{
    cout << "Retained Variance = " << pos << "%   ";
    cout << "re-calculating PCA..." << std::flush;

    double var = pos / 100.0;

    struct params *p = (struct params *)ptr;

    p->pca = PCA(p->data, cv::Mat(), CV_PCA_DATA_AS_ROW, var);

    Mat point = p->pca.project(p->data.row(0));
    Mat reconstruction = p->pca.backProject(point);
    reconstruction = reconstruction.reshape(p->ch, p->rows);
    reconstruction = toGrayscale(reconstruction);

    imshow(p->winName, reconstruction);
    cout << "done!   # of principal components: " << p->pca.eigenvectors.rows << endl;
}


///////////////////////
// Main
int main(int argc, char** argv)
{
    

    // Get the path to your CSV.
    //string imgList = string(argv[1]);

    // vector to hold the images
    vector<Mat> images;
    ImageData * image_process = new ImageData(100, 100);
    PathGenerate * path = new PathGenerate("/home/tabk30/programming/c++/PCA/Image/orl_faces/train/", "Info/train.txt");
    path->generate();
    delete path;
    path = new PathGenerate("/home/tabk30/programming/c++/PCA/Image/orl_faces/test/", "Info/test.txt");
    path->generate();
    delete path;

    vector<Mat> db, test;
    vector<string> labels, truth;
    image_process->loadImage("Info/train.txt", images, labels);
    image_process->loadImage("Info/test.txt", test, truth);
    
    // Read in the data. This can fail if not valid
//    try {
//        read_imgList(imgList, images);
//    } catch (cv::Exception& e) {
//        cerr << "Error opening file \"" << imgList << "\". Reason: " << e.msg << endl;
//        exit(1);
//    }

    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        //CV_Error(Error::StsError, error_message);
    }

    // Reshape and stack images into a rowMatrix
    Mat data = formatImagesForPCA(images);

    // perform PCA
    PCA pca(data, cv::Mat(), CV_PCA_DATA_AS_ROW, 0.95); // trackbar is initially set here, also this is a common value for retainedVariance

    
    
    
    // Demonstration of the effect of retainedVariance on the first image
//    Mat point = pca.project(data.row(0)); // project into the eigenspace, thus the image becomes a "point"
//    Mat reconstruction = pca.backProject(point); // re-create the image from the "point"
//    reconstruction = reconstruction.reshape(images[0].channels(), images[0].rows); // reshape from a row vector into image shape
//    reconstruction = toGrayscale(reconstruction); // re-scale for displaying purposes
//
//    // init highgui window
//    string winName = "Reconstruction | press 'q' to quit";
//    namedWindow(winName, WINDOW_NORMAL);
//
//    // params struct to pass to the trackbar handler
//    params p;
//    p.data = data;
//    p.ch = images[0].channels();
//    p.rows = images[0].rows;
//    p.pca = pca;
//    p.winName = winName;
//
//    // create the tracbar
//    int pos = 95;
//    createTrackbar("Retained Variance (%)", winName, &pos, 100, onTrackbar, (void*)&p);
//
//    // display until user presses q
//    imshow(winName, reconstruction);
//
//    int key = 0;
//    while(key != 'q')
//        key = waitKey();

   return 0;
}