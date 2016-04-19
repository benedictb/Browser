#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>

class History{
public:
    std::vector<std::string> * getHistory(void);
    std::string operator[](int);
    void operator++(int = 0);
    void operator--(int = 0);
    void snapto(int);
    void add(std::string);
    int getPlace(void);
    void setPlace(int);



private:
    std::vector<std::string> historyVect;
    int historyPlace;

};

#endif // HISTORY_H
