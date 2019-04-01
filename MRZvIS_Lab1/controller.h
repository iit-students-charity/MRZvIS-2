#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "pipeline.h"
#include "mainwindow.h"

using namespace std;


class Controller : public QWidget{
    Q_OBJECT
public:
    Controller();
    virtual ~Controller();
private:
    QPushButton *button;
    MainWindow  *mainWindow;
private slots:
    void handlePipe();
};

#endif // CONTROLLER_H
