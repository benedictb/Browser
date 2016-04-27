#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit/QtWebKit>
#include <QWebView>
#include <vector>
#include <string>
#include <set>
#include <histstack.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots: //slots are functions that can be connected to signals
    void on_goButton_clicked(); //triggers when each button is clicked
    void on_backButton_clicked();
    void on_forwardButton_clicked();
    void on_refreshButton_clicked();
    void addressBarHighlighter(); //highlights the addressbar
    void newTab(QString = QString("New Tab")); //creates a new tab
    void on_tabWidget_currentChanged(int index);
    void nextTab(); //moves to the next tab
    void deleteTab(); //deletes current tab
    void autoComplete(); //autocompletes in the address bar
    void load_visited(); //loads the previously visted websets into a set from the txt file
    void toggle_icognito(); //turns incognito on and off
    void load_bookmarks(); //loads the bookmarks into the bookmarks list from the txt file
    void add_bookmark(); //adds the current tab's url to the list of bookmarks
    void load_bookmark(QString); //loads a specific bookmark into the current tab
    void link_set_text(QUrl); //sets the address bar to the current url
    void link_loaded(QUrl); //adds a clicked link to the history

    void on_bookmarkButton_clicked(); //launches bookmark dialog box

private:
    Ui::MainWindow *ui; //pointer to the ui object, from which all life flows

    std::set<std::string> past;
    int currentTab; //holds the current tab index
    QString homepage; //homepage that is loaded on each new tab initiazation

    std::vector<QWebView*> webViews; //a vector of webviews, one for each tab
    std::vector<HistStack> histories; //vector of histories, one for each tab

    std::set<std::string> visited;
    std::set<std::string>::iterator it; //iterator for moving through the visted set
    bool icognito; //whether igcognito mode is on or not

    std::list<std::string> bookmarks; // list of all the bookmarks
    std::list<std::string>::iterator bkit; //iterator for the bookmarks, depreciated (kinda)

    int lastButtonPressed; //an integer representing which button was pressed before the load


};

#endif // MAINWINDOW_H
