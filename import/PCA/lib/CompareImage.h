/* 
 * File:   CompareImage.h
 * Author: tabk30
 *
 * Created on January 22, 2014, 11:31 AM
 */

#ifndef COMPAREIMAGE_H
#define	COMPAREIMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

class CompareImage {
public:
    CompareImage();
    CompareImage(const CompareImage& orig);
    virtual ~CompareImage();
    string findNearest(Mat data, Mat test);
private:

};

#endif	/* COMPAREIMAGE_H */

