#ifndef BOOKMARKITEM_H
#define BOOKMARKITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include <string>

class BookmarkItem : public QListWidgetItem
{
public:
    std::string url;
    BookmarkItem(std::string);

private:
    Q_DISABLE_COPY(BookmarkItem);

};

#endif // BOOKMARKITEM_H
