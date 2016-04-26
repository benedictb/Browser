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

private slots:
    void on_goButton_clicked();
    void on_backButton_clicked();
    void on_forwardButton_clicked();
    void on_refreshButton_clicked();
    void addressBarHighlighter();
    void newTab(QString = QString("New Tab"));
    void on_tabWidget_currentChanged(int index);
    void nextTab();
    void deleteTab();
    void autoComplete();
    void load_visited();
    void toggle_icognito();
    void load_bookmarks();
    void add_bookmark();
    void load_bookmark(QString);

    void on_bookmarkButton_clicked();

private:
    Ui::MainWindow *ui;

    std::set<std::string> past;
    int currentTab;
    QString homepage;

    std::vector<QWebView*> webViews;
    std::vector<HistStack> histories;

    std::set<std::string> visited;
    std::set<std::string>::iterator it;
    bool icognito;

    std::list<std::string> bookmarks;
    std::list<std::string>::iterator bkit;

    QMenu * menu;
    //    std::vector<std::string> history;
    //    int historyPlace;

};

#endif // MAINWINDOW_H
