/* 
 * File:   PathGenerate.h
 * Author: tabk30
 *
 * Created on January 21, 2014, 3:06 PM
 */

#ifndef __PATHGENERATE_H__
#define	__PATHGENERATE_H__

#include <cstdlib>
#include <string>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <vector>

using namespace std;

class PathGenerate {
public:
    PathGenerate(string path, string save);
    PathGenerate(const PathGenerate& orig);
    virtual ~PathGenerate();
    void generate();
private:
    int checkPath(string path);
    void findFaceId();
    void savePath();
    void findFaceImage(string id_temp, string path);
    
    string face_training;
    string file_save;
    vector<string> files;
    vector<string> id;
};

#endif	/* PATHGENERATE_H */

