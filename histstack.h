#ifndef HISTSTACK_H
#define HISTSTACK_H

#include <stack>
#include <string>




class HistStack
{
public:
    HistStack();
    ~HistStack();
        std::string backStep(void);
        std::string forwardStep(void);
        void add(std::string);
    void snapToPresent(void);
        std::string getPresent(void);
    int canGoForward(void);
    int canGoBack(void);


private:
        std::stack<std::string> back;
        std::stack<std::string> front;
};


#endif // HISTSTACK_H
