/* 
 * File:   Suggest.cpp
 * Author: tabk30
 * 
 * Created on December 27, 2013, 3:52 AM
 */

#include "../lib/Suggest.hpp"

Suggest::Suggest(int truth, NearestList *nearest) {
    this->truth = truth;
    this->nearest = nearest;
}

Suggest::Suggest(const Suggest& orig) {
}

Suggest::~Suggest() {
}

int Suggest::getTruth(){
    return this->truth;
}

vector<int> Suggest::getSuggest(){
    return this->nearest->getIdList();
}

