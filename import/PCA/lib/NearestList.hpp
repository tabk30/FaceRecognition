/* 
 * File:   NearestList.hpp
 * Author: tabk30
 *
 * Created on December 27, 2013, 12:31 AM
 */

#ifndef __NEARESTLIST_HPP__
#define	__NEARESTLIST_HPP__

#include <stdio.h>
#include <string>
#include <vector>

using namespace  std;


class NearestList{
private:
    vector<int> label_list;
    vector<string> id_list;
    vector<double> value_list;
    int bigest;
    int size;
    double leastDistSq;
    double findBigest();
    void sort();
    string truth;
    int truth_label;
public:
    NearestList();
    ~NearestList();
    void addElement(string element, int id, double value);
    void addTruth(string truth, int truth_label);
    string at(int index);
    int sizeList();
    string getTruth();
    int getTruthLabel();
    vector<string> getIdList();
    void printList();
    double getDistance(int index);
    int getLabel(int index);
};
 
#endif	/* NEARESTLIST_HPP */

