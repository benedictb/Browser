#ifndef HISTSTACK_H
#define HISTSTACK_H

#include <stack>
#include <string>


/*This is a class that uses two stacks of string (in hindsight should have been qstrings) to keep
 * track of a tab's history.
*/

class HistStack
{
public:
    HistStack();
    ~HistStack();
    std::string backStep(void); //takes a step back
    std::string forwardStep(void); //takes a step forward in the history
    void add(std::string); // adds a item to the history list
//    void snapToPresent(void); ///incorporated into the add function
    std::string getPresent(void); //returns the current string that the list is using
    int canGoForward(void); //returns if you can go forward
    int canGoBack(void); //likewise but back


private:
        std::stack<std::string> back; //back stack, the top of which is the present url
        std::stack<std::string> front; //forward stack, the future
};


#endif // HISTSTACK_H
