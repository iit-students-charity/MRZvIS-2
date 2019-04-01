#include <QApplication>
#include <iostream>
#include <vector>
#include <thread>

#include "controller.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Controller control;

    return app.exec();
}
