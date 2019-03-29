#ifndef PIPELINE_H
#define PIPELINE_H

#define stringify QString::number

#include <iostream>
#include <vector>
#include <QDebug>

#include "mainwindow.h"

using namespace std;


class Pipeline {
public:
    static vector<int> start(const vector<int>&,
                             const vector<int>&,
                             MainWindow&);
private:
    static const int    DIGITS_NUMBER = 6;

    static vector<bool> intToBool(int);
    static int          boolToInt(vector<bool>);
    static vector<bool> addition(vector<bool>&,
                                 const vector<bool>&);
    static vector<bool> shift(const vector<bool>&,
                              const size_t&);
    static void out(const vector<bool>&,
                    MainWindow&);
};

#endif // PIPELINE_H
