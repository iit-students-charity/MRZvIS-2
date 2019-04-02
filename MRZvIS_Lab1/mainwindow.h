/*******************************************************************************************
 *
 * Лабораторная работа N1 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 *
 * Заголовочный файл класса MainWindow.
 *
 * версия 1.0
 *
 *******************************************************************************************/
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
#include <QTableWidgetItem>


class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QPushButton&);
    void         printText(const QString&);
    QLineEdit    *getOp1Line(),
                 *getOp2Line(),
                 *getTPLine();
    QTableWidget *getTable();
private:
    QWidget      widget;
    QVBoxLayout  *vertice;
    QHBoxLayout  *lines;
    QTextEdit    *textBox;
    QPushButton  *buttonStart;
    QTableWidget *table;
    QLineEdit    *operand1Line,
                 *operand2Line,
                 *timeParamLine;
};

#endif // MAINWINDOW_H
