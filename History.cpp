#include "History.h"
#include <string>
#include <vector>

using namespace std;

vector<string> * History::getHistory(void){
    return &historyVect;
}

void History::operator++(int num){
    historyPlace++;
}

void History::operator--(int num){
    historyPlace--;
}

void History::snapto(int val){
    historyVect.resize(val);
}

void History::add(string urlString){
    historyVect[historyPlace] = urlString;
}

string History::operator[](int index){
    return historyVect[index];
}

int History::getPlace(void){
    return historyPlace;
}

void History::setPlace(int val){
    historyPlace = val;
}
