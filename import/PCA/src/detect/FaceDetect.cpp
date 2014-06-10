
#include "../../lib/FaceDetect.h"
#include <stdio.h>
#include <stdlib.h>

FaceDetect::FaceDetect() {
    //this->face_list = new vector<IplImage>();
    storage_face = 0;
    cascade_face = 0;
    cascade_name_face = "import/PCA/src/detect/dataTraining/haarcascades/haarcascade_frontalface_alt_tree.xml";
    //cascade_name_face = "src/detect/dataTraining/haarcascades/haarcascade_frontalface_alt_tree.xml";

}

FaceDetect::FaceDetect(const FaceDetect& orig) {
}

FaceDetect::~FaceDetect() {
    cvReleaseImage(&image);
    cvReleaseHaarClassifierCascade(&cascade_face);
    cvReleaseMemStorage(&storage_face);
}

IplImage * FaceDetect::getImage() {
    return this->image_result;
}

vector<IplImage> FaceDetect::getFaceList() {
    return face_list;
}

void FaceDetect::initDetect(std::string load_path) {
    //IplImage *image = 0;
    char tab2[1024];
    strcpy(tab2, load_path.c_str());
    this->image = cvLoadImage(tab2, 1);
    if (!this->image) {
        printf("Error loading image\n");
        return;
    }
    //this->image = image;
    cascade_face = (CvHaarClassifierCascade*) cvLoad(cascade_name_face, 0, 0, 0);

    if (!cascade_face) {
        printf("ERROR: Could not load classifier of face  cascade\n");
        return;
    }

    storage_face = cvCreateMemStorage(0);
    // Call function to detect and Draw rectagle around face
    detect_and_draw(this->image);
    // release resourses

}

void FaceDetect::detect_and_draw(IplImage* img) {

    double scale = 1;
    IplImage* result = NULL, * copy = img;
    IplImage* face_tag = cvCreateImage(cvGetSize(img),
            img->depth,
            img->nChannels);
    cvCopy(img, face_tag, NULL);
    cvResetImageROI(img);
    //face_retag = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
    // create a gray image for the input image
    IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
    // Scale down the ie. make it small. This will increase the detection speed
    IplImage* small_img = cvCreateImage(cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1);

    cvCvtColor(img, gray, CV_BGR2GRAY);

    cvResize(gray, small_img, CV_INTER_LINEAR);

    // Equalise contrast by eqalizing histogram of image
    cvEqualizeHist(small_img, small_img);

    cvClearMemStorage(storage_face);
    //Load cascade_face
    if (cascade_face) {
        // Detect object defined in Haar cascade. IN our case it is face
        this->faces = cvHaarDetectObjects(small_img, cascade_face, storage_face,
                1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                cvSize(30, 30));

        // Draw a rectagle around all detected face 

        for (int i = 0; i < (this->faces ? faces->total : 0); i++) {
            CvRect r = *(CvRect*) cvGetSeqElem(faces, i);
            cvRectangle(face_tag, cvPoint(r.x*scale, r.y * scale), cvPoint((r.x + r.width) * scale, (r.y + r.height) * scale), CV_RGB(255, 0, 0), 3, 8, 0);
            result = crop(img, r);
            this->face_list.push_back(*result);
        }
    }
    this->image_result = face_tag;

    cvReleaseImage(&gray);
    cvReleaseImage(&small_img);
    return;
}

IplImage* FaceDetect::tagFaceRecognition(vector<int> tag_id) {
    //cout << "tag number: " << this->faces->total << endl;
    double scale = 1;
    IplImage* face_recognition = cvCreateImage(cvGetSize(this->image),
            this->image->depth,
            this->image->nChannels);
    cvCopy(this->image, face_recognition, NULL);
    cvResetImageROI(this->image);


    int k = 1;
    for (int i = 0; i < (this->faces ? this->faces->total : 0); i++) {
        CvRect r = *(CvRect*) cvGetSeqElem(this->faces, i);
        for (unsigned int j = 0; j < tag_id.size(); j++) {
            if (i == tag_id.at(j)) {
                Mat temp = Mat(face_recognition);
                putText(temp, this->convertInt(k), cvPoint(r.x * scale - 30, r.y * scale + 30),
                        FONT_HERSHEY_COMPLEX_SMALL, 1.8, cvScalar(0, 0, 255), 1, CV_AA);
                cvRectangle(face_recognition, cvPoint(r.x*scale, r.y * scale), cvPoint((r.x + r.width) * scale, (r.y + r.height) * scale), CV_RGB(255, 0, 0), 3, 8, 0);
                k++;
            }
        }
    }
    
    return face_recognition;
}

IplImage* FaceDetect::crop(IplImage* src, CvRect roi) {
    // Must have dimensions of output image
    IplImage* cropped = cvCreateImage(cvSize(roi.width, roi.height), src->depth, src->nChannels);

    // Say what the source region is

    cvSetImageROI(src, roi);

    // Do the copy
    cvCopy(src, cropped);
    cvResetImageROI(src);

    return cropped;
}

string FaceDetect::convertInt(int number) {
    if (number == 0)
        return "0";
    string temp = "";
    string returnvalue = "";
    while (number > 0) {
        temp += number % 10 + 48;
        number /= 10;
    }
    for (int i = 0; i < temp.length(); i++)
        returnvalue += temp[temp.length() - i - 1];
    return returnvalue;
}
