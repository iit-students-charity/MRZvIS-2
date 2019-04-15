/*******************************************************************************************
 *
 * Лабораторная работа N1 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 *
 * Файл реализации методов класса Pipeline.
 * Метод Pipeline::start(args) является главным методом класса, в нём заключается:
 * передача аргументов в конвейер;
 * реализация конвейерной архитектуры;
 * вывод результатов работы конвейера в MainWindow::table и MainWindow::textBox.
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
                 STAGES_NUMBER   = 2 * DIGITS_NUMBER,
                 RUNTIME         = 2 * DIGITS_NUMBER + OPERANDS_NUMBER;
    size_t       operandsInLine  = 0,
                 stage           = 0;
    QString      cellText        = "";
    vector<bool> *boolA          = new vector<bool>[OPERANDS_NUMBER],
                 *boolB          = new vector<bool>[OPERANDS_NUMBER],
                 *currentSummand = new vector<bool>[OPERANDS_NUMBER],
                 *product        = new vector<bool>[OPERANDS_NUMBER];
    vector<int>  productInt;
    vector<size_t> subproc,
                   curDigit;

    mainWindow.getTable()->clear();
    mainWindow.getTable()->setRowCount(int(RUNTIME));
    mainWindow.getTable()->setColumnCount(int(STAGES_NUMBER + 1));

    mainWindow.printText("$$$$$$$$Pipeline starts here$$$$$$$$\n");

    mainWindow.printText("CONVERTING INT TO BOOL...");
    for (size_t i = 0; i < OPERANDS_NUMBER; i++){
        if(vectorA[i] < 0){
            vectorA[i] = abs(vectorA[i]);
            mainWindow.printText("Error! Negative number occured. Converting in positive.\n");
        }
        if(vectorB[i] < 0){
            vectorB[i] = abs(vectorB[i]);
            mainWindow.printText("Error! Negative number occured. Converting in positive.\n");
        }
        boolA[i] = intToBool(vectorA[i]);
        boolB[i] = intToBool(vectorB[i]);

        mainWindow.printText("\nPair " + stringify(i) + ":\n" +
                             stringify(vectorA[i]) + " = ");
        out(boolA[i], mainWindow);
        mainWindow.printText("\n" + stringify(vectorB[i]) + " = ");
        out(boolB[i], mainWindow);

        product[i] = intToBool(0);
        subproc.push_back(0);
        curDigit.push_back(0);
    }

    for (size_t time = 0; time < RUNTIME; time++){
        mainWindow.printText("\n\nSTEP N" + stringify(time) + ":");

        for (size_t operand = 0; operand <= operandsInLine; operand++){
            stage = time - operand;

            if (stage >= STAGES_NUMBER){
                continue;
            }

            cellText = stringify(operand + 1) + ") STAGE " + stringify(stage + 1) + "\n";

            switch(subproc[operand]){
            case 0:
                cellText += "SHIFTING ";
                mainWindow.printText("\n" + stringify(operand + 1) + ")SHIFTING ");

                currentSummand[operand] = boolA[operand];
                if (boolB[operand][curDigit[operand]] == 1){
                    cellText += "\n" + boolToString(boolA[operand]);
                    out(boolA[operand], mainWindow);

                    currentSummand[operand] = shift(boolA[operand],
                                                     curDigit[operand]);
                } else {
                    cellText += "\n000000";
                    mainWindow.printText("\n000000");

                    currentSummand[operand] = intToBool(0);
                }
                cellText += " <[" + stringify(curDigit[operand]) + "]< " +
                          boolToString(currentSummand[operand]);
                mainWindow.printText(" <[" + stringify(curDigit[operand]) + "]< ");
                out(currentSummand[operand], mainWindow);

                subproc[operand]++;
                break;
            case 1:
                cellText += "ADDITION\n" +
                          boolToString(product[operand]) + " + " +
                          boolToString(currentSummand[operand]) + " = ";
                mainWindow.printText("\n" + stringify(operand+1) + ")ADDITION\n");
                out(product[operand], mainWindow);
                mainWindow.printText(" + ");
                out(currentSummand[operand], mainWindow);
                mainWindow.printText(" = ");
                if (boolB[operand][curDigit[operand]] == 1){
                    product[operand] = addition(product[operand],
                                                 currentSummand[operand]);
                }
                cellText += boolToString(product[operand]);
                out(product[operand], mainWindow);
                curDigit[operand]++;
                subproc[operand] = 0;
                break;
            }
            cellText += "\nTime:" + stringify((time + 1) * timeParam);
            mainWindow.getTable()->setItem(int(time),
                                           int(stage),
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

        cellText += "\n" + stringify(i+1) + ") " +
                    stringify(vectorA[i]) + " * " + stringify(vectorB[i]) +
                    " = " + stringify(productInt[i]) +
                    " = " + boolToString(product[i]);
        mainWindow.printText("\n" + stringify(i+1) + ") " + stringify(productInt[i]) + " = ");
        out(product[i], mainWindow);
    }

    mainWindow.getTable()->setItem(int(RUNTIME - 1),
                                   int(STAGES_NUMBER),
                                   new QTableWidgetItem(cellText));
    mainWindow.printText("\n&&&&&&&&Pipeline stops here&&&&&&&&\n");
    mainWindow.getTable()->resizeRowsToContents();
    mainWindow.getTable()->resizeColumnsToContents();

    return productInt;
}

vector<bool> Pipeline::intToBool(int intNum){
    vector<bool> binNum(DIGITS_NUMBER);

    for (size_t i = 0; i < DIGITS_NUMBER; i++){
        binNum[i] = (intNum & 1);
        intNum  >>= 1;
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
    const int    SUMM_SIZE     = 12;
    vector<bool> summ(0);
    bool		 extraDigit    = 0;
    int			 iterationSumm = 0;

    for (size_t i = 0 ; i <= SUMM_SIZE; i++){
        if(summand.size() <= i){
            summand.push_back(0);
        }
        iterationSumm = product[i]+summand[i]+extraDigit;
        extraDigit    = (iterationSumm > 1) ? 1 : 0;
        summ.push_back(iterationSumm % 2);
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

    for (size_t i = input.size() - 1; i < input.size();i--){
        output += stringify(input[i]);
    }
    return output;
}
