#include "bookmarkdialog.h"
#include "ui_bookmarkdialog.h"
#include "bookmarkitem.h"
#include <QListView>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringListModel>


const QString PATH = "../Project/";
//const QString PATH = "/Users/bobsim21/Desktop/Project";

BookmarkDialog::BookmarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookmarkDialog)
{
    ui->setupUi(this); //load ui
    load_bookmarks(); //load bookmarks
    ui->bookmarkView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //non-editable list

    QStringListModel * model = new QStringListModel(this);

    for (it = bkmks.begin(); it != bkmks.end(); it++){ //load the list of bookmarks into the new Qlist
        list<< QString::fromStdString(*(it)); //using an iterator to move through the list
    }
    model->setStringList(list); //load the Qstringlist into the ui

    ui->bookmarkView->setModel(model);//load the Qstringlist into the ui

    ui->bookmarkView->setCurrentIndex(ui->bookmarkView->model()->index(0, 0)); //highlight one to avoid segfaults

}

BookmarkDialog::~BookmarkDialog()
{
    delete ui->bookmarkView->model(); //clean up ui and the model that we made
    delete ui;
}

void BookmarkDialog::load_bookmarks(){ //load the file into a list, original implementation in mainwindow.cpp
    QFile file(PATH + "bookmarks.txt");
    file.open(QIODevice::ReadWrite);
    if (!file.exists())
        emit close();
    else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!in.atEnd())
            bkmks.push_back(in.readLine().toStdString());
        file.close();
    }
}

//void BookmarkDialog::make_bookmarks(){
//}

void BookmarkDialog::on_bookmarkButton_clicked(){
   QString temp = (*(list.begin()+ui->bookmarkView->currentIndex().row())); //user's selection

   emit loadBookmark(temp); //emit the loadbookmark for the other ui and then close the window
   emit close();
}

