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
    void load_bookmarks(void);
    void make_bookmarks(void);

private slots:
    void on_bookmarkButton_clicked();

signals:
    void loadBookmark(QString);

private:
    Ui::BookmarkDialog *ui;
    std::list<std::string> bkmks;
    QStringList list;
    std::list<std::string>::iterator it;
};

#endif // BOOKMARKDIALOG_H
