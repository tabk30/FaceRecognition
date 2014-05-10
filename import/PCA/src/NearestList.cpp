/* 
 * File:   NearestList.cpp
 * Author: tabk30
 * 
 * Created on December 27, 2013, 12:31 AM
 */
#include "../lib/NearestList.hpp"

NearestList::NearestList() {
    this->size = -1;
}

NearestList::~NearestList() {
}

void NearestList::addElement(string element, int id, double value){
    if(this->size < 2){
        this->id_list.push_back(element);
        this->value_list.push_back(value);
        this->label_list.push_back(id);
        size++;
        this->sort();
    }else{
        if(value < this->findBigest()){
            this->id_list.at(2) = element;
            this->value_list.at(2) = value;
            this->label_list.at(2) = id;
            this->sort();
        }
    }
}

void NearestList::sort(){
    int j=0;
    string temp_id;
    int temp_label;
    double temp_value = 0;
    for(int i = 0; i<=this->size; i++){
        for(j = i + 1; j<=this->size; j++){
            if(this->value_list.at(i) > this->value_list.at(j)){
                temp_id = this->id_list.at(i);
                temp_value = this->value_list.at(i);
                temp_label = this->label_list.at(i);
                
                this->id_list.at(i) = this->id_list.at(j);
                this->value_list.at(i) = this->value_list.at(j);
                this->label_list.at(i) = this->label_list.at(j);
                
                this->id_list.at(j) = temp_id;
                this->value_list.at(j) = temp_value;
                this->label_list.at(j) = temp_label;
            }
        }
    }
}

double NearestList::findBigest(){
    return this->value_list.back();
}

vector<string> NearestList::getIdList(){
    return this->id_list;
}

void NearestList::printList(){
    for(int i = 0; i <= this->size; i++){
        printf("        %d. %s--%f\n ", i, this->id_list.at(i).c_str(), this->value_list.at(i));
    }
} 

void NearestList::addTruth(string truth, int truth_label){
    this->truth = truth;
    this->truth_label = truth_label;
}
string NearestList::at(int index){
    return this->id_list.at(index);
}
int NearestList::sizeList(){
    return this->size;
}
string NearestList::getTruth(){
    return this->truth;
}
int NearestList::getTruthLabel(){
    return this->truth_label;
}
int NearestList::getLabel(int index){
    return this->label_list.at(index);
}
double NearestList::getDistance(int index){
    return this->value_list.at(index);
}

