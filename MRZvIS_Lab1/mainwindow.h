#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>


class MainWindow {

public:
    MainWindow();
    void printText(const QString&);

private:
    QWidget         widget;
    QVBoxLayout*    vertice;
    QTextEdit*      textBox;
    QPushButton*    buttonStart;
};

#endif // MAINWINDOW_H
