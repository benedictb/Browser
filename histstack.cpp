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
    front.push(back.top());
    back.pop();
    return getPresent();
}

std::string HistStack::forwardStep(void){
    back.push(front.top());
    front.pop();
    return getPresent();
}

void HistStack::add(std::string url){
    while (!front.empty()){
        front.pop();
    }
    back.push(url);
}

int HistStack::canGoForward(void){
    return !(front.empty());
}

int HistStack::canGoBack(void){
    return (back.size() > 1);
}
