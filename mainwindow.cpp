#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    historyPlace=-1;
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

    if (found != 0){
        url = "http://" + url;
    }

    ui->webView->load(url);
    history.push_back(url.toStdString());
    historyPlace++;
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
