/* 
 * File:   Statistic.hpp
 * Author: tabk30
 *
 * Created on December 27, 2013, 2:39 AM
 */

#ifndef STATISTIC_HPP
#define	STATISTIC_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "Suggest.hpp"
#include "NearestList.hpp"
using namespace std;

class Statistic {
public:
    Statistic();
    Statistic(const Statistic& orig);
    virtual ~Statistic();
    void addTest(string truth, int truth_id, NearestList *nearest_list);
    void printStatistic();
private:
    int test_size;
    int sugess_truth;
    int sugess_wrong;
    vector<NearestList*> truth_list;
    vector<NearestList*> wrong_list;
};
  
#endif	/* STATISTIC_HPP */

