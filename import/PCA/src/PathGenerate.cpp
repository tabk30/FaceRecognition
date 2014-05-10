/* 
 * File:   PathGenerate.cpp
 * Author: tabk30
 * 
 * Created on January 21, 2014, 3:06 PM
 */

#include "../lib/PathGenerate.h"

PathGenerate::PathGenerate(string path, string save) {
    this->face_training = path;
    this->file_save = save;
}

PathGenerate::PathGenerate(const PathGenerate& orig) {
}

PathGenerate::~PathGenerate() {
}

void PathGenerate::generate(){
    this->findFaceId();
}

int PathGenerate::checkPath(string path) {
    char temp[1024];
    strcpy(temp, path.c_str());
    struct stat s;
    if (stat(temp, &s) == 0) {
        if (s.st_mode & S_IFDIR) {

            return 1;
        } else if (s.st_mode & S_IFREG) {
            //it's a file
            return 2;
        } else {
            //something else
            return 0;
        }
    } else {
        //error
        return 0;
    }
    return 0;
}

void PathGenerate::findFaceId() {
    DIR *dp;
    struct dirent *dirp;
    string temp;
    string id_temp;
    if ((dp = opendir(face_training.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << face_training << endl;
        return;
    }
    while ((dirp = readdir(dp)) != NULL) {
        temp = string(dirp->d_name);
        id_temp = dirp->d_name;
        if ((temp.compare(".") != 0) && (temp.compare("..") != 0)) {
            temp = face_training + "/" + temp;
            if (checkPath(temp) == 1) {
                findFaceImage(id_temp, temp);

            }
        }
    }
    savePath();
    closedir(dp);
    return;
}

void PathGenerate::savePath() {
    FILE * imgListFile = NULL;
    imgListFile = fopen(file_save.c_str(), "w");

    if (imgListFile != NULL) {
        for (unsigned int i = 0; i < files.size(); i++) {
            if(i != (files.size() - 1))fprintf(imgListFile, "%s;%s\n", files.at(i).c_str(), id.at(i).c_str());
            else fprintf(imgListFile, "%s;%s", files.at(i).c_str(), id.at(i).c_str());
            
        }
    } else {
        printf("read file error\n");
        return;
    }
    fclose(imgListFile);
}

void PathGenerate::findFaceImage(string id_temp, string path) {
    DIR *dp;
    struct dirent *dirp;
    string temp;
    if ((dp = opendir(path.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << face_training << endl;
        return;
    }
    while ((dirp = readdir(dp)) != NULL) {
        temp = string(dirp->d_name);
        if ((temp.compare(".") != 0) && (temp.compare("..") != 0)) {
            temp = path + "/" + temp;
            if (checkPath(temp) == 2) {
                files.push_back(temp);
                id.push_back(id_temp);
            }
        }
    }
    savePath();
    closedir(dp);
    return;
}