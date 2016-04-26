#include "bookmarkdialog.h"
#include "ui_bookmarkdialog.h"
#include "bookmarkitem.h"
#include <QListView>
#include <QFile>
#include <QTextStream>
#include <QStringListModel>

BookmarkDialog::BookmarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookmarkDialog)
{
    ui->setupUi(this);
    load_bookmarks();
    ui->bookmarkView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringListModel * model = new QStringListModel(this);

    for (it = bkmks.begin(); it != bkmks.end(); it++){
        list<< QString::fromStdString(*(it));
    }
    model->setStringList(list);

    ui->bookmarkView->setModel(model);
}

BookmarkDialog::~BookmarkDialog()
{
    delete ui;
}

void BookmarkDialog::load_bookmarks(){
    QFile file("../Project/bookmarks.txt");
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

void BookmarkDialog::make_bookmarks(){
}

void BookmarkDialog::on_bookmarkButton_clicked(){

   QString temp = (*(list.begin()+ui->bookmarkView->currentIndex().row()));
   emit loadBookmark(temp);
   emit close();
}
