/*******************************************************************************************
 *
 * Лабораторная работа N1 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 *
 * Заголовочный файл класса Pipeline.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#ifndef PIPELINE_H
#define PIPELINE_H

#define stringify QString::number

#include <iostream>
#include <vector>
#include <QDebug>
#include <math.h>

#include "mainwindow.h"

using namespace std;


class Pipeline {
public:
    vector<int> start(vector<int>,
                      vector<int>,
                      const size_t&,
                      MainWindow&);
private:
    static const int    DIGITS_NUMBER = 6;

    vector<bool> intToBool(int);
    int          boolToInt(vector<bool>);
    static vector<bool> addition(const vector<bool>&,
                                 vector<bool>&);
    vector<bool> shift(const vector<bool>&,
                       const size_t&);
    void         out(const vector<bool>&,
                     MainWindow&);
    QString      boolToString(const vector<bool>&);
};

#endif // PIPELINE_H
