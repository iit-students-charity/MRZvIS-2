#include "pipeline.h"
#include "mainwindow.h"


vector<int> Pipeline::start(const vector<int> &vectorMd,
                            const vector<int> &vectorMr,
                            MainWindow        &mainWindow){
    const size_t OPERANDS_NUMBER = vectorMd.size(),
                 STAGES_NUMBER   = DIGITS_NUMBER*2,
                 STEPS_NUMBER    = DIGITS_NUMBER*2+OPERANDS_NUMBER;
    vector<bool> *multiplicand   = new vector<bool>[OPERANDS_NUMBER],
                 *multiplier     = new vector<bool>[OPERANDS_NUMBER],
                 *currentSummand = new vector<bool>[OPERANDS_NUMBER],
                 *product        = new vector<bool>[OPERANDS_NUMBER];
    vector<int>  productInt;
    vector<size_t> stage,
                   curDigit;
    size_t       operandsInLine  = 0,
                 step;
    QString      cellText = "";

    mainWindow.getTable()->clear();
    mainWindow.getTable()->setRowCount(int(STEPS_NUMBER+1));
    mainWindow.getTable()->setColumnCount(int(STAGES_NUMBER+1));

    mainWindow.printText("$$$$$$$$Pipeline starts here$$$$$$$$\n");

    mainWindow.printText("CONVERTING INT TO BOOL...");
    for (size_t i = 0; i < OPERANDS_NUMBER; i++){
        multiplicand[i] = intToBool(vectorMd[i]);
        multiplier[i] = intToBool(vectorMr[i]);

        mainWindow.printText("\nPair " + stringify(i) + ":\n" +
                             stringify(vectorMd[i]) + " = ");
        out(multiplicand[i], mainWindow);
        mainWindow.printText("\n" + stringify(vectorMr[i]) + " = ");
        out(multiplier[i], mainWindow);

        product[i] = intToBool(0);
        stage.push_back(0);
        curDigit.push_back(0);
    }

    for (step = 0; step < STEPS_NUMBER; step++){
        mainWindow.printText("\n\nSTEP N" + stringify(step) + ":");

        for (size_t curOpera = 0; curOpera <= operandsInLine; curOpera++){
            if (int(curDigit[curOpera]) - DIGITS_NUMBER > 0){
                continue;
            }

            cellText = "";

            switch(stage[curOpera]){
            case 0:
                currentSummand[curOpera] = multiplicand[curOpera];
                cellText+="SHIFTING";
                if (multiplier[curOpera][curDigit[curOpera]] == 1){
                    if (curDigit[curOpera] > 0){
                        cellText+="\n " + boolToString(multiplicand[curOpera]) +
                                  " <[" + stringify(curDigit[curOpera]) + "]<";
                        mainWindow.printText("\n" + stringify(curOpera+1) + ") shifting ");
                        out(multiplicand[curOpera], mainWindow);
                        mainWindow.printText(" <[" + stringify(curDigit[curOpera]) + "]< ");

                        currentSummand[curOpera] = shift(multiplicand[curOpera],
                                                         curDigit[curOpera]);

                        cellText+=boolToString(currentSummand[curOpera]);
                        out(currentSummand[curOpera], mainWindow);
                    }
                } else {
                    curDigit[curOpera]++;
                    cellText+="\n Nothing to shift.";
                }

                stage[curOpera] ++;
                break;
            case 1:
                cellText+="ADDITION"
                          "\n " + boolToString(product[curOpera]) + " + " +
                          boolToString(currentSummand[curOpera]) + " = \n";
                mainWindow.printText("\n" + stringify(curOpera+1) + ") ");
                out(product[curOpera], mainWindow);
                mainWindow.printText(" + ");
                out(currentSummand[curOpera], mainWindow);
                mainWindow.printText(" = ");
                if (multiplier[curOpera][curDigit[curOpera]] == 1){
                    product[curOpera] = addition(product[curOpera],
                                                 currentSummand[curOpera]);
                }
                cellText+=boolToString(product[curOpera]);
                out(product[curOpera], mainWindow);
                curDigit[curOpera]++;
                stage[curOpera] = 0;
                break;
            }
            cellText+="\nTime:"+stringify(step+curOpera+1);
            mainWindow.getTable()->setItem(int(step+curOpera),
                                           int(step),
                                           new QTableWidgetItem(cellText));
        }

        if(operandsInLine < OPERANDS_NUMBER - 1){
            operandsInLine++;
        }
    }

     mainWindow.printText("\nRESULTS:\n");
     cellText.clear();
     step++;

    for (size_t i = 0; i < OPERANDS_NUMBER; i++){
        productInt.push_back(boolToInt(product[i]));

        cellText+="RESULT:\n " + stringify(boolToInt(product[i]));
        mainWindow.getTable()->setItem(int(step+i+1),
                                       int(step+1),
                                       new QTableWidgetItem(cellText));
        mainWindow.printText("\n" + stringify(i) + ") " + stringify(productInt[i]) + " = ");
        out(product[i], mainWindow);
    }

    mainWindow.printText("\n&&&&&&&&Pipeline stops here&&&&&&&&\n");

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
