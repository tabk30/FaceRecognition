#include "mainscreen.h"
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <map>
#include "import/PCA/lib/PathGenerate.h"
#include "import/PCA/lib/ImageData.h"
#include "import/PCA/lib/NearestList.hpp"
#include "import/PCA/lib/Statistic.hpp"


using namespace cv;
using namespace std;

Mat formatImagesForPCA(const vector<Mat> &data) {
    Mat dst(static_cast<int> (data.size()), data[0].rows * data[0].cols, CV_32F);
    for (unsigned int i = 0; i < data.size(); i++) {
        Mat image_row = data[i].clone().reshape(1, 1);
        Mat row_i = dst.row(i);
        image_row.convertTo(row_i, CV_32F);
    }

    return dst;
}

void PCAProcess(){
    //prepare data training:
    //load data train 
    
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
    
    PCA pca(train, cv::Mat(), CV_PCA_DATA_AS_ROW, 0.95);
    Mat train_compress, test_compressed;
    test_compressed.create(test.rows, db.size(), test.type());
    train_compress.create(train.rows, db.size(), train.type());
    for (int i = 0; i < train_compress.rows; i++) {
        Mat vec = train.row(i), coeffs = train_compress.row(i);
        pca.project(vec, coeffs);
    }
    
    bool write_success = cv::imwrite("import/PCA/data/pca", train_compress);
    if(write_success){
        cout << "Save data success" << endl;
    }else{
        cout << "Save data fail" << endl;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScreen w;
    w.show();

    return a.exec();
}
