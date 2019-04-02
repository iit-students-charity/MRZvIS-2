/*******************************************************************************************
 *
 * Лабораторная работа N1 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 *
 * Файл реализации методов класса Controller, в конструкторе которого происходит
 * инициализация главного окна приложения и запуск конвеера через функцию
 * Pipeline::start(args).
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include "controller.h"


Controller::Controller(){
    button = new QPushButton("&START", this);
    mainWindow = new MainWindow(*button);
    connect(button, SIGNAL(clicked()),
            this, SLOT(handlePipe()));
}

void Controller::handlePipe(){
    vector<int> vectorA,
                vectorB,
                vectorRezult;
    Pipeline    pipe;
    QString     inputA,
                inputB;
    int         inputASize,
                inputBSize;
    size_t      timeParam;

    inputA = mainWindow->getOp1Line()->text();
    inputB = mainWindow->getOp2Line()->text();
    inputASize = inputA.split(" ").size();
    inputBSize = inputB.split(" ").size();

    for(int i=0; i<abs(inputASize-inputBSize); i++){
        if(inputASize<inputBSize){
            inputA+=" 0";
        }
        if(inputASize>inputBSize){
            inputB+=" 0";
        }
    }

    for(int i = 0; i<inputASize; i++){
        vectorA.push_back(inputA.split(" ")[i].toInt());
        vectorB.push_back(inputB.split(" ")[i].toInt());
    }

    timeParam = size_t(mainWindow->getTPLine()->text().toInt());

    pipe.start(vectorA, vectorB, timeParam, *mainWindow);
}

Controller:: ~Controller(){

}
