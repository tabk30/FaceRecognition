/* 
 * File:   FaceRecogniontPCA.cpp
 * Author: tabk30
 * 
 * Created on May 10, 2014, 3:42 PM
 */

#include "../lib/FaceRecogniontPCA.h"

FaceRecogniontPCA::FaceRecogniontPCA() {
    //load data
    this->LoadData();
    if (this->data.cols <= 0) {
        ImageData * image_process = new ImageData(100, 100);
        PathGenerate * path = new PathGenerate("/home/tabk30/GR/Image_data/frontalface_filter_noise/train", "Info/train.txt");
        path->generate();
        delete path;

        vector<Mat> db;
        image_process->loadImage("import/PCA/Info/train.txt", db, this->label_train);
        //image_process->loadImage("Info/train.txt", db, this->label_train);
        Mat train = formatImagesForPCA(db);
        ///////////////////////////////////////////////////////////////////


        //int component = 50;
        this->pca(train, cv::Mat(), CV_PCA_DATA_AS_ROW, 0.95);
        Mat train_compress;
        train_compress.create(train.rows, db.size(), train.type());
        for (int i = 0; i < train_compress.rows; i++) {
            Mat vec = train.row(i), coeffs = train_compress.row(i);
            this->pca.project(vec, coeffs);
        }
        this->data = train_compress;
        this->SaveData(this->pca.eigenvalues, this->pca.eigenvectors, this->pca.mean);
    } else {
        cout << "Load data complete" << endl;
    }
    //cout << "Load data complete" << endl;
}

FaceRecogniontPCA::FaceRecogniontPCA(const FaceRecogniontPCA& orig) {

}

FaceRecogniontPCA::~FaceRecogniontPCA() {
}

vector<string> FaceRecogniontPCA::recognition(string path_image) {
    FaceDetect * __face_detect = new FaceDetect();
    //face_detect->initDetect("/home/tabk30/GR/Image_data/image/1052244476/100001048955310_1830116.jpg");
    __face_detect->initDetect(path_image);

    //cout << "Detect complete" << endl;
    this->face_detect = __face_detect->getImage();
    vector<IplImage> face_list = __face_detect->getFaceList();
    vector<string> result;
    vector<int> testVector;

    for (unsigned int i = 0; i < face_list.size(); i++) {
        IplImage temp = face_list.at(i);

        Mat image = Mat(&temp);
        string label_temp = this->recognitionAFace(image);
        if (label_temp.compare("") != 0) {
            testVector.push_back(i);
            result.push_back(label_temp);
        }

    }

    this->face_recognition = __face_detect->tagFaceRecognition(testVector);
    cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
    cvShowImage("image", this->face_recognition);
    cvWaitKey();
    return result;
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

string FaceRecogniontPCA::recognitionAFace(Mat origin) {
    double leastDistSq = 1.0f;
    int __nearlest = 0;
    Mat coeffs, test = origin;
    //coeffs.create(1, train_compress.rows, train_compress.type());
    test = this->synchronizationImage(test);
    vector<Mat> test_data;
    test_data.push_back(test);
    Mat test_compress = this->formatImagesForPCA(test_data);

    this->pca.project(test_compress.row(0), coeffs);
    for (int i = 0; i < this->data.rows; i++) {
        double euclidean = 0.0f;
        euclidean = cv::norm(this->data.row(i), coeffs, cv::NORM_L2);
        if (i == 0) {
            leastDistSq = euclidean;
            __nearlest = i;
        } else if (euclidean < leastDistSq) {
            leastDistSq = euclidean;
            __nearlest = i;
        }
    }
    if (leastDistSq < MAX_DISTENCE) {
        return this->getLabel(this->label_train.at(__nearlest));
    } else
        return "";
}

void FaceRecogniontPCA::SaveData(Mat eigenvalues, Mat eigenvectors, Mat mean) {
    FileStorage fs("import/PCA/data/data.xml", FileStorage::WRITE);
    //FileStorage fs("data/data.xml", FileStorage::WRITE);

    if (!fs.isOpened()) {
        cerr << "Failed to open " << "import/PCA/data/data.xml" << endl;
        //help(av);
        return;
    }
    fs << "eigenvalues" << eigenvalues.clone();
    fs << "eigenvectors" << eigenvectors.clone();
    fs << "mean" << mean.clone();
    fs << "train_data" << this->data.clone();
    fs << "label" << this->label_train;
    fs.release();
}

void FaceRecogniontPCA::LoadData() {
    //Mat error(0, 0, DataType<float>::type), data;

    FileStorage fs("import/PCA/data/data.xml", FileStorage::READ);
    //FileStorage fs("data/data.xml", FileStorage::READ);
    if (!fs.isOpened()) {
        cerr << "Failed to open " << "import/PCA/data/data.xml" << endl;
        return;
    }
    //Mat eigenvalues, eigenvectors, mean;
    fs["eigenvalues"] >> this->pca.eigenvalues;
    fs["eigenvectors"] >> this->pca.eigenvectors;
    fs["mean"] >> this->pca.mean;
    fs["train_data"] >> this->data;
    fs["label"] >> this->label_train;
    fs.release();

    return;
}

string FaceRecogniontPCA::findNearest(Mat input) {
    double leastDistSq = 1.0f;
    int __nearlest = 0;
    for (int i = 0; i < this->data.rows; i++) {
        double euclidean = 0.0f;
        euclidean = cv::norm(this->data.row(i), input, cv::NORM_L2);
        if (i == 0) {
            leastDistSq = euclidean;
            __nearlest = i;
        } else if (euclidean < leastDistSq) {
            leastDistSq = euclidean;
            __nearlest = i;
        }
    }

    return this->label_train.at(__nearlest);
}

Mat FaceRecogniontPCA::synchronizationImage(Mat image) {
    Mat origin;
    cvtColor(image, origin, CV_BGR2GRAY);
    Mat smallerImage;
    resize(origin, smallerImage, Size(70, 70), 0, 0, INTER_AREA);

    return smallerImage;
}

string FaceRecogniontPCA::getLabel(string label) {
    if (label.compare("1") == 0)
        return "Chie Hashimoto";
    else if (label.compare("2") == 0)
        return "Junko Sakuma";
    else if (label.compare("3") == 0)
        return "Cuong Nguyen";
    else if (label.compare("4") == 0)
        return "Phuong Nguyen Thanh";
    else if (label.compare("5") == 0)
        return "Yutaka Furui";
    else if (label.compare("6") == 0)
        return "Nguyen Thanh Cong";
    else if (label.compare("7") == 0)
        return "Nguyen Dinh Loc";
    else if (label.compare("8") == 0)
        return "Pham Nga";
    else if (label.compare("9") == 0)
        return "Ta Son Tung";
    else if (label.compare("10") == 0)
        return "Mr.HoangViet";
    else if (label.compare("11") == 0)
        return "Pham Anh Minh";
    else if (label.compare("12") == 0)
        return "Pham Hung";
    else if (label.compare("13") == 0)
        return "Nguyen Hong Phuong";
    else if (label.compare("14") == 0)
        return "Hung Pham";
    else if (label.compare("15") == 0)
        return "Luong Kim";
    else if (label.compare("16") == 0)
        return "Quang Tan";
    else if (label.compare("17") == 0)
        return "Trong Nghia Bui";
    else if (label.compare("18") == 0)
        return "QuynhDo Anh";
    else if (label.compare("19") == 0)
        return "Huong Luu";
    else if (label.compare("20") == 0)
        return "Nguyen Hoang";
    else if (label.compare("21") == 0)
        return "Thinh Thanh Thoi";
    else if (label.compare("22") == 0)
        return "nguyen Khoi";
    else if (label.compare("23") == 0)
        return "Huy Nguyen Quang";
    else if (label.compare("24") == 0)
        return "Viet Anh";
    else if (label.compare("25") == 0)
        return "Quang Nguyen";
    else if (label.compare("26") == 0)
        return "Hoang Nhat";
    else if (label.compare("27") == 0)
        return "Hoa Nguyen";
    else if (label.compare("28") == 0)
        return "Kien Phi Nguyen";
    else if (label.compare("29") == 0)
        return "Hoang Van Duc";
    else if (label.compare("30") == 0)
        return "Van Anh Duong";
    else if (label.compare("31") == 0)
        return "Trung Kien";
    else if (label.compare("32") == 0)
        return "Hung Doan";
    else if (label.compare("33") == 0)
        return "Anh Pham";
    return "";
}