#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // toolbar *bar = new toolbar();
   // MainWindow::setCentralWidget(bar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString url = ui->lineEdit->text();
    std::string stdUrl = url.toStdString();
    std::size_t found = stdUrl.find("http://");
    if (found == 0)
        ui->webView->load(url);
    else ui->webView->load("http://" + url);
}
