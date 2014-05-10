/* 
 * File:   Suggest.hpp
 * Author: tabk30
 *
 * Created on December 27, 2013, 3:52 AM
 */

#ifndef __SUGGEST_HPP__
#define	__SUGGEST_HPP__

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "../lib/NearestList.hpp"

using namespace std;
class Suggest {
public:
    Suggest(int truth, NearestList *suggest);
    Suggest(const Suggest& orig);
    virtual ~Suggest();
    int getTruth();
    vector<int> getSuggest();
private:
    int truth;
    vector<int> suggest;
    NearestList * nearest;

};

#endif	/* SUGGEST_HPP */

