#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    historyPlace=-1;

    QShortcut * quitShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    QShortcut * refreshShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_refreshButton_clicked()));
    QShortcut * addressShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), ui->lineEdit, SLOT(setFocus()));

    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->goButton,SIGNAL(clicked()));


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
    historyPlace++;
    history.resize(historyPlace+1);
    history[historyPlace]=url.toStdString();

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
