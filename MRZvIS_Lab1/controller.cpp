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

    pipe.start(vectorA, vectorB, *mainWindow);
}

Controller:: ~Controller(){

}
