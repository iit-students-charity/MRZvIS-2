#include <QApplication>
#include <iostream>
#include <vector>
#include <thread>

#include "pipeline.h"
#include "mainwindow.h"

using namespace std;


int main(int argc, char** argv) {
    vector<int>		vectorA,
                    vectorB,
                    vectorRezult;

    QApplication app(argc, argv);

    MainWindow      mainWindow;

    vectorA.push_back({ 7 });
    vectorB.push_back({ 9 });

    vectorA.push_back({ 10 });
    vectorB.push_back({ 0 });

    vectorA.push_back({ 16 });
    vectorB.push_back({ 16 });

    vectorA.push_back({ 63 });
    vectorB.push_back({ 63 });

    Pipeline::start(vectorA, vectorB, mainWindow);

    return app.exec();
}
