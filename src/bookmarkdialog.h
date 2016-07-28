#ifndef BOOKMARKDIALOG_H
#define BOOKMARKDIALOG_H

#include <QDialog>
#include <list>
#include <string>
#include <QListWidget>


namespace Ui {
class BookmarkDialog;
}


class BookmarkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookmarkDialog(QWidget *parent = 0);
    ~BookmarkDialog();

    void load_bookmarks(void); //load the bookmarks
//    void make_bookmarks(void); //make the bookmark list abstract model

private slots:
    void on_bookmarkButton_clicked(); //on button click function

signals:
    void loadBookmark(QString); //to emit to other ui

private:
    Ui::BookmarkDialog *ui; //pointer to ui
    std::list<std::string> bkmks; //list of bookmarks
    QStringList list; //special string list
    std::list<std::string>::iterator it; //regular list iterator
};

#endif // BOOKMARKDIALOG_H
