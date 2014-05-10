/* 
 * File:   ImageData.cpp
 * Author: tabk30
 * 
 * Created on January 22, 2014, 8:49 AM
 */

#include "../lib/ImageData.h"

ImageData::ImageData(int width, int height) {
    this->width = width;
    this->height = height;
}

ImageData::ImageData(const ImageData& orig) {
}

ImageData::~ImageData() {
}

void ImageData::loadImage(const string& filename, vector<Mat>& images, vector<string>& labels) {
    Mat smallerImage, origin;
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file)
        throw std::exception();
    std::string line, path, classlabel;
    // For each line in the given file:
    while (std::getline(file, line)) {
        // Get the current line:
        std::stringstream liness(line);
        // Split it at the semicolon:
        std::getline(liness, path, ';');
        std::getline(liness, classlabel);
        // And push back the data into the result vectors:
        origin = imread(path, IMREAD_GRAYSCALE);
        if (!origin.data) // Check for invalid input
        {
            cout << "Could not open or find the image" << std::endl;
            continue;
        }
        smallerImage = this->resizeImage(origin);
        
        images.push_back(smallerImage);
        labels.push_back(classlabel.c_str());
    }
}

int ImageData::saveImage(const string &filename, vector<Mat>& images, vector<string>& labels) {
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PXM_BINARY);
    compression_params.push_back(1);
    Mat temp;
    string name = filename;
    //strcpy(name.c_str(), filename.c_str());
    ostringstream convert;
    for (unsigned int i = 0; i < images.size(); i++) {
        name = filename;
        temp = images.at(i);

        name.append("/");
        name.append(labels.at(i).c_str());
        
        mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        name.append("/");
        name.append(this->convertInt(i));
        name.append(".pgm");
        cout << "Image path: " << name << endl;

        try {
            imwrite(name, temp, compression_params);
        } catch (runtime_error& ex) {
            fprintf(stderr, "Exception converting image to JPG format: %s\n", ex.what());
            return 1;
        }
        name.clear();
    }
    return 0;
}

string ImageData::convertInt(int number) {
    stringstream ss; //create a stringstream
    ss << number; //add number to the stream
    return ss.str(); //return a string with the contents of the stream
}

Mat ImageData::resizeImage(Mat origin) {
    Mat smallerImage;
    resize(origin, smallerImage, Size(70, 70), 0, 0, INTER_AREA);
    return smallerImage;
}

