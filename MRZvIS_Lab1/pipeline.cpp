/*******************************************************************************************
 *
 * Лабораторная работа N1 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 *
 * Файл реализации методов класса Pipeline.
 * Метод Pipeline::start(args) является главным методом класса, в нём заключается
 * передачи аргументов в конвеер,
 * реализация конвеерной архитектуры
 * и вывод результатов работы конвеера в MainWindow::table и MainWindow::textBox.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include "pipeline.h"
#include "mainwindow.h"


vector<int> Pipeline::start(vector<int> vectorA,
                            vector<int> vectorB,
                            const size_t      &timeParam,
                            MainWindow        &mainWindow){
    const size_t OPERANDS_NUMBER = vectorA.size(),
                 STAGES_NUMBER   = DIGITS_NUMBER*2+OPERANDS_NUMBER,
                 STEPS_NUMBER    = DIGITS_NUMBER*2+(OPERANDS_NUMBER)*2;
    size_t       operandsInLine  = 0;
    QString      cellText = "";
    vector<bool> *boolA          = new vector<bool>[OPERANDS_NUMBER],
                 *boolB          = new vector<bool>[OPERANDS_NUMBER],
                 *currentSummand = new vector<bool>[OPERANDS_NUMBER],
                 *product        = new vector<bool>[OPERANDS_NUMBER];
    vector<int>  productInt;
    vector<size_t> stage,
                   curDigit;

    mainWindow.getTable()->clear();
    mainWindow.getTable()->setRowCount(int(STEPS_NUMBER+1));
    mainWindow.getTable()->setColumnCount(int(STAGES_NUMBER+1));

    mainWindow.printText("$$$$$$$$Pipeline starts here$$$$$$$$\n");

    mainWindow.printText("CONVERTING INT TO BOOL...");
    for (size_t i = 0; i < OPERANDS_NUMBER; i++){
        if(vectorA[i]<0){
            vectorA[i]=abs(vectorA[i]);
            mainWindow.printText("Error! Negative number ocured. Converting in positive.\n");
        }
        if(vectorB[i]<0){
            vectorB[i]=abs(vectorB[i]);
            mainWindow.printText("Error! Negative number ocured. Converting in positive.\n");
        }
        boolA[i] = intToBool(vectorA[i]);
        boolB[i] = intToBool(vectorB[i]);

        mainWindow.printText("\nPair " + stringify(i) + ":\n" +
                             stringify(vectorA[i]) + " = ");
        out(boolA[i], mainWindow);
        mainWindow.printText("\n" + stringify(vectorB[i]) + " = ");
        out(boolB[i], mainWindow);

        product[i] = intToBool(0);
        stage.push_back(0);
        curDigit.push_back(0);
    }

    //TODO: Fix pojehavshaya tablica(разобраться с кол-вом тактов и прочего. Там видимо всё изза deadcell)
    //TODO: показывать этапы
    for (size_t step = 0; step < STEPS_NUMBER; step++){
        mainWindow.printText("\n\nSTEP N" + stringify(step) + ":");

        for (size_t curOpera = 0; curOpera <= operandsInLine; curOpera++){
            if (int(curDigit[curOpera]) - DIGITS_NUMBER > 0){
                continue;
            }

            cellText = "";

            switch(stage[curOpera]){
            case 0:
                cellText+=stringify(curOpera+1) + ")SHIFTING ";
                mainWindow.printText("\n" + stringify(curOpera+1) + ")SHIFTING ");

                currentSummand[curOpera] = boolA[curOpera];
                if (boolB[curOpera][curDigit[curOpera]] == 1){
                    cellText+="\n  " + boolToString(boolA[curOpera]);
                    out(boolA[curOpera], mainWindow);

                    currentSummand[curOpera] = shift(boolA[curOpera],
                                                     curDigit[curOpera]);
                } else {
                    cellText+="\n  000000";
                    mainWindow.printText("\n 000000");

                    currentSummand[curOpera] = intToBool(0);
                }
                cellText+=" <[" + stringify(curDigit[curOpera]) + "]< " +
                          boolToString(currentSummand[curOpera]);
                mainWindow.printText(" <[" + stringify(curDigit[curOpera]) + "]< ");
                out(currentSummand[curOpera], mainWindow);

                stage[curOpera] ++;
                break;
            case 1:
                cellText+=stringify(curOpera+1) + ")ADDITION\n  " +
                          boolToString(product[curOpera]) + " + " +
                          boolToString(currentSummand[curOpera]) + " = ";
                mainWindow.printText("\n" + stringify(curOpera+1) + ")ADDITION\n ");
                out(product[curOpera], mainWindow);
                mainWindow.printText(" + ");
                out(currentSummand[curOpera], mainWindow);
                mainWindow.printText(" = ");
                if (boolB[curOpera][curDigit[curOpera]] == 1){
                    product[curOpera] = addition(product[curOpera],
                                                 currentSummand[curOpera]);
                }
                cellText+=boolToString(product[curOpera]);
                out(product[curOpera], mainWindow);
                curDigit[curOpera]++;
                stage[curOpera] = 0;
                break;
            }
            cellText+="\nTime:"+stringify((step+1)*timeParam);
            mainWindow.getTable()->setItem(int(step+curOpera),
                                           int(step),
                                           new QTableWidgetItem(cellText));
        }

        if(operandsInLine < OPERANDS_NUMBER - 1){
            operandsInLine++;
        }
    }

     mainWindow.printText("\nRESULTS:\n");
     cellText="RESULTS:";

    for (size_t i = 0; i < OPERANDS_NUMBER; i++){
        productInt.push_back(boolToInt(product[i]));

        cellText+="\n" + stringify(i+1) + ") " +
                  stringify(vectorA[i]) + " * " + stringify(vectorB[i]) +
                  " = " + stringify(productInt[i]) +
                  " = " + boolToString(product[i]);
        mainWindow.printText("\n" + stringify(i+1) + ") " + stringify(productInt[i]) + " = ");
        out(product[i], mainWindow);
    }

    mainWindow.getTable()->setItem(int(STEPS_NUMBER),
                                   int(STAGES_NUMBER),
                                   new QTableWidgetItem(cellText));
    mainWindow.printText("\n&&&&&&&&Pipeline stops here&&&&&&&&\n");
    mainWindow.getTable()->resizeRowsToContents();
    mainWindow.getTable()->resizeColumnsToContents();

    return productInt;
}

vector<bool> Pipeline::intToBool(int intNum){
    vector<bool>	binNum(DIGITS_NUMBER);

    for (size_t i = 0; i < DIGITS_NUMBER; i++){
        binNum[i] = (intNum & 1);
        intNum >>= 1;
    }

    return binNum;
}

int Pipeline::boolToInt(vector<bool> binNum){
    int intNum = 0;

    for(size_t i = 0; i < binNum.size(); i++){
        intNum += binNum[i] * pow(2,i);
    }
    return intNum;
}

vector<bool> Pipeline::shift(const vector<bool> &operand,
                             const size_t       &shift){
    vector<bool> rezult(operand.size() + shift);

    for (size_t i = shift; i < rezult.size(); i++){
        rezult[i] = operand[i - shift];
    }

    return rezult;
};

vector<bool> Pipeline::addition(const vector<bool> &product,
                                vector<bool> &summand){
    vector<bool> summ(summand.size());
    bool		 extraDigit = 0;
    int			 iterationSumm = 0;

    for (size_t i = 0 ; i < product.size(); i++){
        if(summand.size() <= i){
            summand.push_back(0);
        }
        iterationSumm = product[i]+summand[i]+extraDigit;
        extraDigit = (iterationSumm > 1) ? 1 : 0;
        summ[i] = iterationSumm % 2;
    }
    if(extraDigit == 1){
        summ.push_back(extraDigit);
    }

    return summ;
}

void Pipeline::out(const vector<bool> &input,
                   MainWindow         &mainWindow){
    for (size_t i = input.size() - 1; i < input.size(); i--){
        mainWindow.printText(stringify(input[i]));
    }
}

QString Pipeline::boolToString(const vector<bool> &input){
    QString output = "";

    for (size_t i = input.size()-1; i<input.size();i--){
        output+=stringify(input[i]);
    }
    return output;
}
