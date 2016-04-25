#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <iostream>
#include "histstack.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    icognito = false;
    ui->setupUi(this);
    homepage = "http://nd.edu";


    currentTab = 0;
    QShortcut * quitShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    QShortcut * refreshShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_refreshButton_clicked()));
    QShortcut * addressShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), ui->lineEdit, SLOT(setFocus()));
    QShortcut * newTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_T), this, SLOT(newTab()));
    QShortcut * switchTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Tab),this,SLOT(nextTab()));
    QShortcut * deleteCurrentTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W),this,SLOT(deleteTab()));
    QShortcut * autoComplete = new QShortcut(QKeySequence(Qt::Key_Tab),this,SLOT(autoComplete()));

    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->goButton,SIGNAL(clicked()));
    ui->lineEdit->setText(homepage);
    ui->webView->load(ui->lineEdit->text());
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ui->lineEdit->text()); // sets name of tab to website
    load_visited();
    webViews.push_back(ui->webView);

    HistStack newHist;
    newHist.add(homepage.toStdString());
    histories.push_back(newHist);
}

MainWindow::~MainWindow()
{
    if (!icognito) {
        QFile file("/Users/bobsim21/Desktop/Project/visited.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream stream(&file);
        for (it = visited.begin(); it != visited.end(); ++it)
           stream << QString::fromStdString(*it) << endl; // writes new visited file before it exits
        file.close();
    }
    delete ui;
}

void MainWindow::on_goButton_clicked()
{
    QString url = ui->lineEdit->text();
    std::string stdUrl = url.toStdString();
    std::size_t found = stdUrl.find("http://");

    if (found != 0) {
        url = "http://" + url;
    }

    webViews[ui->tabWidget->currentIndex()]->load(url);
    visited.insert(url.toStdString());

    histories[ui->tabWidget->currentIndex()].add(url.toStdString());

    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), url); // sets name of tab to website



}

void MainWindow::on_backButton_clicked()
{
    int current = ui->tabWidget->currentIndex();
    if (histories[current].canGoBack()){
        QString url = QString::fromStdString(histories[current].backStep());
        ui->lineEdit->setText(url);
        webViews[current]->load(url);

    }


}

void MainWindow::on_forwardButton_clicked()
{
    int current = ui->tabWidget->currentIndex();
    if (histories[current].canGoForward()){
        QString url = QString::fromStdString(histories[current].forwardStep());
        ui->lineEdit->setText(url);
        webViews[current]->load(url);
    }

}

void MainWindow::on_refreshButton_clicked() {
    webViews[ui->tabWidget->currentIndex()]->load(QString::fromStdString(histories[ui->tabWidget->currentIndex()].getPresent()));
}

void MainWindow::addressBarHighlighter() {
    ui->lineEdit->selectAll();
    ui->lineEdit->setFocus();
}

void MainWindow::newTab(QString str) {
    QWebView *newView = new QWebView(); // creates new tab
    HistStack newHist;
    newHist.add(homepage.toStdString());

    webViews.push_back(newView);
    histories.push_back(newHist);


    ui->tabWidget->addTab(newView, str);
    ui->tabWidget->setTabText(ui->tabWidget->count()-1,homepage);
    newView->load(homepage);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    currentTab = index;
}

void MainWindow::nextTab(){
    if (ui->tabWidget->currentIndex() >= ui->tabWidget->count()-1){
        ui->tabWidget->setCurrentIndex(0);
    } else {
        ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex() + 1));
    }
}

void MainWindow::deleteTab(){
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    webViews.erase(webViews.begin()+ui->tabWidget->currentIndex());
    histories.erase(histories.begin()+ui->tabWidget->currentIndex());
}

void MainWindow::autoComplete() {
    std::string current = ui->lineEdit->text().toStdString();
    for (it = visited.begin(); it != visited.end(); ++it)
        if (it->find(current) != std::string::npos)
            ui->lineEdit->setText(QString::fromStdString(*it));
}

void MainWindow::load_visited() {
    QFile file("/Users/bobsim21/Desktop/Project/visited.txt");
    file.open(QIODevice::ReadWrite);
    if (!file.exists())
        ui->lineEdit->setText("No History Found");
    else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!in.atEnd())
            visited.insert(in.readLine().toStdString());
        file.close();
    }
}
