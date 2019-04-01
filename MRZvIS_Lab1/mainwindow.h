#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>


class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QPushButton&);
    void         printText(const QString&);
    QLineEdit    *getOp1Line(),
                 *getOp2Line();
    QTableWidget *getTable();
private:
    QWidget      widget;
    QVBoxLayout  *vertice;
    QHBoxLayout  *lines;
    QTextEdit    *textBox;
    QPushButton  *buttonStart;
    QTableWidget *table;
    QLineEdit    *operand1Line,
                 *operand2Line;
};

#endif // MAINWINDOW_H
