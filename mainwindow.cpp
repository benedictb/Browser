#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <iostream>
#include "histstack.h"
#include "bookmarkdialog.h"
#include <iostream>
#include <string>

const QString PATH = "/Users/bobsim21/Desktop/Project/"; // path to various text files
//const QString PATH = "../Project/"; // this one should be appropriate on Linux machines

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    icognito = false; // default value for icognito mode
    ui->setupUi(this); // simple setup for ui, shows the window
    homepage = "http://nd.edu"; // default homepage

    this->setWindowTitle("Browser");
    currentTab = 0;
    // Shortcuts set up here
    QShortcut * quitShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    QShortcut * refreshShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_refreshButton_clicked()));
    QShortcut * addressShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this,SLOT(addressBarHighlighter()));
    QShortcut * newTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_T), this, SLOT(newTab()));
    QShortcut * switchTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Tab),this,SLOT(nextTab()));
    QShortcut * switchBackTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Tab),this,SLOT(previousTab()));
    QShortcut * deleteCurrentTabShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W),this,SLOT(deleteTab()));
    QShortcut * autoComplete = new QShortcut(QKeySequence(Qt::Key_Tab),this,SLOT(autoComplete()));
    QShortcut * backShortcut = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_Left),ui->backButton,SLOT(click()));
    QShortcut * forwardShortcut = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_Right),ui->forwardButton,SLOT(click()));
    QShortcut * toggle_icognito = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I),this,SLOT(toggle_icognito()));
    QShortcut * addBookmarkShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D),this,SLOT(add_bookmark()));

    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->goButton,SIGNAL(clicked())); //connect enter key to go button
    ui->lineEdit->setText(homepage);
    ui->webView->load(ui->lineEdit->text()); //load homepage
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), ui->lineEdit->text()); // sets name of tab to website
    load_visited(); //load the two files, history and bookmarks
    load_bookmarks();


    //This is kind of a test run for the first tab, the other tabs all go through a similar process in the new tab function
    webViews.push_back(ui->webView); //put the webview in the tab vector

    HistStack newHist; //create a new tab history for the first tab and put it into the tab history vector
    newHist.add(homepage.toStdString());
    histories.push_back(newHist);

    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(link_set_text(QUrl))); //add to the history every time a link is clicked
    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(link_loaded(QUrl))); //set the text boxes correctly when a link is clicked

}

MainWindow::~MainWindow()
{
    if (!icognito) {
        QFile file(PATH + "visited.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Text); // opens visited.txt
        QTextStream stream(&file);
        std::string temp;
        for (it = visited.begin(); it != visited.end(); ++it) { // iterates through visited set
           if ((*it).find("http://") != 0)
               temp = "http://" + *it; // adds http:// to all history to make it uniform
           else temp = *it;
           stream << QString::fromStdString(temp) << endl; // writes new visited file before it exits
        }
        file.close();
    }
    for (int i = 0; i < ui->tabWidget->count(); i++){
        delete webViews[i]; //deletes all of the dynamically allocated webviews that we've made for the tabs
    }
    delete ui;
}

void MainWindow::on_goButton_clicked()
{
    QString url = ui->lineEdit->text(); //captures the string
    std::string stdUrl = url.toStdString();
    std::size_t found = stdUrl.find("http://");

    if (found != 0) {
        url = "http://" + url; // adds necessary http format for Url
    }
    lastButtonPressed = 1;

    if (QUrl(url).isValid()) { // check if Url is valid http format
        webViews[ui->tabWidget->currentIndex()]->load(url); // current tab loads html, etc.
        visited.insert(url.toStdString()); // adds url to visited set
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), url); // sets name of tab to website
        histories[ui->tabWidget->currentIndex()].add(url.toStdString()); // adds to history
    } else { // if the url is not vaid
        webViews[ui->tabWidget->currentIndex()]->load("file://" + PATH + "index.html"); // displays custom html for page not found
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), QString("Page Not Found")); // sets tab text
        ui->lineEdit->setText(url); // sets address bar text
    }
}

void MainWindow::on_backButton_clicked()
{
    int current = ui->tabWidget->currentIndex(); //int containing current index
    if (histories[current].canGoBack()){ //if you can go back, it goes back
        lastButtonPressed=2;
        QString url = QString::fromStdString(histories[current].backStep());
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), url); //set text displays and load the previous url
        ui->lineEdit->setText(url);
        webViews[current]->load(url);
    }
}

void MainWindow::on_forwardButton_clicked()
{
    int current = ui->tabWidget->currentIndex(); //similar to the back button
    if (histories[current].canGoForward()){ //if you can go forward...
        lastButtonPressed=3;
        QString url = QString::fromStdString(histories[current].forwardStep());
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), url); //set text displays and load the next url
        ui->lineEdit->setText(url);
        webViews[current]->load(url);
    }
}

void MainWindow::on_refreshButton_clicked() {
    lastButtonPressed = 4;
    int current = ui->tabWidget->currentIndex();
    webViews[current]->load(QString::fromStdString(histories[current].getPresent())); //load the current url again
}

void MainWindow::on_bookmarkButton_clicked() {
    BookmarkDialog * dialog = new BookmarkDialog(); //create a bookmark dialog on b button clicked
    dialog->show(); //open the dialog box
    connect(dialog,SIGNAL(loadBookmark(QString)),this,SLOT(load_bookmark(QString))); // connect the button press on the dialog box to the load_bookmark function in mainwindow
}

void MainWindow::addressBarHighlighter() {
    ui->lineEdit->selectAll(); // Highlights the address bar, mapped to CTRL + L
    ui->lineEdit->setFocus();
}

void MainWindow::newTab(QString str) {
    QWebView *newView = new QWebView(); // creates new tab
    HistStack newHist; // creates new history for this tab
    newHist.add(homepage.toStdString()); // adds first page to history

    webViews.push_back(newView);
    histories.push_back(newHist);

    ui->tabWidget->addTab(newView, str); // implements the new tab
    ui->tabWidget->setTabText(ui->tabWidget->count()-1,homepage); // set name for tabs
    newView->load(homepage); // loads url for the tab

    connect(webViews[ui->tabWidget->count()-1],SIGNAL(urlChanged(QUrl)),this,SLOT(link_set_text(QUrl))); //link up loading a new page to adding to the history and updating text fields
    connect(webViews[ui->tabWidget->count()-1],SIGNAL(urlChanged(QUrl)),this,SLOT(link_loaded(QUrl)));

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    currentTab = index;
}

void MainWindow::nextTab() {
    // moves current tab to the right
    if (ui->tabWidget->currentIndex() >= ui->tabWidget->count()-1){
        ui->tabWidget->setCurrentIndex(0);
    } else {
        ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex() + 1));
    }
    ui->lineEdit->setText(QString::fromStdString(histories[ui->tabWidget->currentIndex()].getPresent()));
}

void MainWindow::previousTab() {
    // moves tab selection to the left
    if (ui->tabWidget->currentIndex() <= 0){
        ui->tabWidget->setCurrentIndex( ui->tabWidget->count()-1);
    } else {
        ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex() - 1));
    }
    ui->lineEdit->setText(QString::fromStdString(histories[ui->tabWidget->currentIndex()].getPresent()));
}

void MainWindow::deleteTab() {
    // deletes the current tab
    if (ui->tabWidget->count() <=1){
        exit(0);
    }

    webViews.erase(webViews.begin()+ui->tabWidget->currentIndex());
    histories.erase(histories.begin()+ui->tabWidget->currentIndex());
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    QString url = QString::fromStdString(histories[ui->tabWidget->currentIndex()].getPresent());
    ui->lineEdit->setText(url);

//    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex());
}

void MainWindow::autoComplete() {
    // auto completes the current address bar text
    std::string current = ui->lineEdit->text().toStdString();
    for (it = visited.begin(); it != visited.end(); ++it) // searches in visited sites
        if (it->find(current) != std::string::npos) { // if a similar string is found
            ui->lineEdit->setText(QString::fromStdString(*it)); // exec autocomplete
            break; // leave the loop and stop searching
        }
}

void MainWindow::load_visited() {
    // loads text file with visited sites
    QFile file(PATH + "visited.txt");
    file.open(QIODevice::ReadWrite);
    if (!file.exists())
        ui->lineEdit->setText("No History Found");
    else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!in.atEnd()) // read the file and put into a visited set.
            visited.insert(in.readLine().toStdString());
        file.close();
    }
}

void MainWindow::load_bookmarks() {
    // loads bookmarks from text file
    QFile file(PATH + "bookmarks.txt");
    file.open(QIODevice::ReadWrite);
    if (!file.exists())
        ui->lineEdit->setText("No Bookmarks Found");
    else {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!in.atEnd()) // reads from the file
            bookmarks.push_back(in.readLine().toStdString()); // adds the strings to bookmarks vector
        file.close(); // closes the file
    }
}

void MainWindow::add_bookmark(){
    QString bkmk = QString::fromStdString(histories[ui->tabWidget->currentIndex()].getPresent());
    QFile file(PATH + "bookmarks.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream stream(&file);
    stream<<bkmk << endl;
    file.close();

}

void MainWindow::toggle_icognito() {
    if (icognito) {
        icognito = false; // true then make false
        this->setWindowTitle("Browser"); // changes title of window
    } else {
        icognito = true; // false then make true
        this->setWindowTitle("Browser (Incognito)");
    }
}

void MainWindow::load_bookmark(QString url){
    webViews[ui->tabWidget->currentIndex()]->load(url);

    visited.insert(url.toStdString());
    ui->lineEdit->setText(url);
    histories[ui->tabWidget->currentIndex()].add(url.toStdString());

    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), url); // sets name of tab to website
}

void MainWindow::link_set_text(QUrl url){

    ui->lineEdit->setText(url.toString());
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), url.toString()); // sets name of tab to website

}

void MainWindow::link_loaded(QUrl url){
    if (lastButtonPressed == 0){
        int current = ui->tabWidget->currentIndex();
        histories[current].add(url.toString().toStdString());
    } else {
        lastButtonPressed = 0;
    }
}

