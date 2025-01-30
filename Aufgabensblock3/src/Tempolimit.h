/*
 * Tempolimit.h
 *
 *  Created on: 03.12.2024
 *      Author: annaroessel
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include <limits>


enum class Tempolimit {
    Innerorts = 1,
    Landstrasse = 2,
    Autobahn = 3
};

inline double getkmhTempolimit(Tempolimit limit) {
    double val = 0;
    if(limit == Tempolimit::Innerorts) {
        val = 50.0;
    }
    else if(limit == Tempolimit::Landstrasse) {
        val =  100.0;
    }
    else if(limit == Tempolimit::Autobahn) {
        val =  std::numeric_limits<int>::max();
    }
    return val;
}


#endif /* TEMPOLIMIT_H_ */
