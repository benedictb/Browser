#include <string>
#include <stack>
#include "histstack.h"


HistStack::HistStack(){
}

HistStack::~HistStack(){
}

std::string HistStack::getPresent(void){
    return back.top();
}

std::string HistStack::backStep(void){
    front.push(back.top()); //shift one from the back to the front and return the present
    back.pop();
    return getPresent();
}

std::string HistStack::forwardStep(void){
    back.push(front.top()); //shift one from the front to the back and return the present
    front.pop();
    return getPresent();
}

void HistStack::add(std::string url){
    while (!front.empty()){ //clear the front, and "start a new branch"
        front.pop();
    }
    back.push(url); //add to the present
}

int HistStack::canGoForward(void){ //is there anything there?
    return !(front.empty());
}

int HistStack::canGoBack(void){
    return (back.size() > 1);
}
