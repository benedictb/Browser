#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <iostream>

//history and bookmarks

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    homepage = "http://nd.edu";
    historyPlace=-1;
    currentTab = 0;

    QShortcut * quitShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    QShortcut * refreshShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_refreshButton_clicked()));
    QShortcut * addressShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), ui->lineEdit, SLOT(setFocus()));
    QShortcut * newTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_T), this, SLOT(newTab()));
    QShortcut * switchTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Tab),this,SLOT(nextTab()));
    QShortcut * deleteCurrentTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W),this,SLOT(deleteTab()));
<<<<<<< HEAD
    QShortcut * autoComplete = new QShortcut(QKeySequence(Qt::Key_Tab),this,SLOT(autoComplete));
=======
>>>>>>> 9621ec4a69d21dbcf9c912d3486c9f8fa5eabc95

    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->goButton,SIGNAL(clicked()));

    ui->lineEdit->setText(homepage);
    ui->webView->load(ui->lineEdit->text());

    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ui->lineEdit->text()); // sets name of tab to website
}

MainWindow::~MainWindow()
{
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

    ui->webView->load(url);

    historyPlace++;
    history.resize(historyPlace+1);
    history[historyPlace]=url.toStdString();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), url); // sets name of tab to website

//    history[historyPlace]=url.toStdString();
//    history.resize(historyPlace+1);

}

void MainWindow::on_backButton_clicked()
{
    if (historyPlace <= 0){
        return;
    }

    historyPlace--;
    ui->lineEdit->setText(QString::fromStdString(history[historyPlace]));
    ui->webView->load(QString::fromStdString(history[historyPlace]));

}

void MainWindow::on_forwardButton_clicked()
{
    if (historyPlace >= history.size()-1){
        return;
    }

    historyPlace++;
    ui->lineEdit->setText(QString::fromStdString(history[historyPlace]));
    ui->webView->load(QString::fromStdString(history[historyPlace]));
}

void MainWindow::on_refreshButton_clicked(){
    on_goButton_clicked();
}

void MainWindow::addressBarHighlighter(){
    ui->lineEdit->selectAll();
    ui->lineEdit->setFocus();
}

void MainWindow::newTab(QString str) {
    ui->tabWidget->addTab(new QWebView(), str);
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
}

void MainWindow::autoComplete() {
    QString current = ui->lineEdit->text();

}
