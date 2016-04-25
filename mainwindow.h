#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit/QtWebKit>
#include <QWebView>
#include <vector>
#include <string>
#include <set>

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

private:
    Ui::MainWindow *ui;
    std::vector<std::string> history;
    std::set<std::string> past;
    int historyPlace;
    int currentTab;
    QString homepage;
    std::vector<QWebView*> webViews;
};

#endif // MAINWINDOW_H
