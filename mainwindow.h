#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit/QtWebKit>
#include <vector>
#include <string>

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

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    std::vector<std::string> history;
    int historyPlace;
    int currentTab;
};

#endif // MAINWINDOW_H
