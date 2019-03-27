#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <string.h>

using namespace std;


class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow();
    void         printText(const QString&);

private:
    QWidget         widget;
    QVBoxLayout*    vertice;
    QTextEdit*      textBox;
    QPushButton*    buttonStart;

//public slots:
//    void slotButtonClicked();
};

#endif // MAINWINDOW_H
