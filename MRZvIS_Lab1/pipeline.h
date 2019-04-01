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
    vector<int> start(const vector<int>&,
                      const vector<int>&,
                      MainWindow&);
private:
    static const int    DIGITS_NUMBER = 6;

    vector<bool> intToBool(int);
    int          boolToInt(vector<bool>);
    vector<bool> addition(const vector<bool>&,
                          vector<bool>&);
    vector<bool> shift(const vector<bool>&,
                       const size_t&);
    void         out(const vector<bool>&,
                     MainWindow&);
    QString      boolToString(const vector<bool>&);
};

#endif // PIPELINE_H
