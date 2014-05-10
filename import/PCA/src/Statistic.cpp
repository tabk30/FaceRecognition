/* 
 * File:   Statistic.cpp
 * Author: tabk30
 * 
 * Created on December 27, 2013, 2:39 AM
 */

#include "../lib/Statistic.hpp"

Statistic::Statistic() {
    this->test_size = 0;
    this->sugess_wrong = 0;
    this->sugess_truth = 0;
}

Statistic::Statistic(const Statistic& orig) {
}

Statistic::~Statistic() {
}

void Statistic::addTest(string truth, int truth_id, NearestList *nearest_list) {
    nearest_list->addTruth(truth, truth_id);
    for (int i = 0; i <= nearest_list->sizeList(); i++) {
        if (truth.compare(nearest_list->at(i)) == 0) {
            //cout  << "truth: " << truth << " compare: " << nearest_list->at(i) << endl;
            this->test_size++;
            this->sugess_truth++;
            this->truth_list.push_back(nearest_list);
            return;
        }else {
            //cout  << "truth: " << truth << " not compare: " << nearest_list->at(i) << endl;
        }
    }
    this->test_size++;
    this->sugess_wrong++;
    this->wrong_list.push_back(nearest_list);
    return;
}

void Statistic::printStatistic() {
    FILE * imgListFile = NULL;
    NearestList *nearest_list;

    imgListFile = fopen("Info/statistic.txt", "w");

    if (imgListFile != NULL) {
        fprintf(imgListFile, "Sum of test: %d\n   Truth: %d\n     Wrong:%d\n", this->test_size, this->sugess_truth, this->sugess_wrong);
        fprintf(imgListFile,"Suggest truth:\n");
        for (unsigned int i = 0; i<this->truth_list.size(); i++) {
            nearest_list = this->truth_list.at(i);
            fprintf(imgListFile,"   truth:%s\n      list suggest:\n         1.%s--%f\n            2.%s--%f\n            3.%s--%f\n", nearest_list->getTruth().c_str(),  nearest_list->at(0).c_str(),  nearest_list->getDistance(0), nearest_list->at(1).c_str(),  nearest_list->getDistance(1), nearest_list->at(2).c_str(), nearest_list->getDistance(2));
            //printf("        truth:%d list suggest:1.%d 2.%d 3.%d 4.%d 5.%d\n", suggest->getTruth(), list_suggest.at(0), list_suggest.at(1), list_suggest.at(2), list_suggest.at(3), list_suggest.at(4));
        }

        fprintf(imgListFile,"Suggest wrong:\n");
        for (unsigned int i = 0; i<this->wrong_list.size(); i++) {
            nearest_list = this->wrong_list.at(i);
            fprintf(imgListFile,"   truth:%s\n      list suggest:\n         1.%s--%f\n            2.%s--%f\n            3.%s--%f\n", nearest_list->getTruth().c_str(),  nearest_list->at(0).c_str(),  nearest_list->getDistance(0), nearest_list->at(1).c_str(),  nearest_list->getDistance(1), nearest_list->at(2).c_str(), nearest_list->getDistance(2));
        }
    } else {
        printf("read file error\n");
        return;
    }
    fclose(imgListFile);

}

