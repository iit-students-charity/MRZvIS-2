/*******************************************************************************************
 *
 * Лабораторная работа N1 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 *
 * Заголовочный файл класса C.ontroller
 *
 * версия 1.0
 *
 *******************************************************************************************/
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
