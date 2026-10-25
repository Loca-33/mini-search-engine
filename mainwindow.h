#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "searchengine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectDirectoryButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    SearchEngine *searchEngine;
    QDir currentDir;
    bool isIndexBuilt = false;
};
#endif // MAINWINDOW_H
