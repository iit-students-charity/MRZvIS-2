#include "pipeline.h"
#include "mainwindow.h"


vector<int> Pipeline::start(const vector<int> &vectorMd,
                            const vector<int> &vectorMr,
                            MainWindow        &mainWindow){
    const size_t OPERANDS_NUMBER = vectorMd.size(),
                 STEPS_NUMBER    = DIGITS_NUMBER*OPERANDS_NUMBER;
    vector<bool> *multiplicand   = new vector<bool>[OPERANDS_NUMBER],
                 *multiplier     = new vector<bool>[OPERANDS_NUMBER],
                 *currentSummand = new vector<bool>[OPERANDS_NUMBER],
                 *product        = new vector<bool>[OPERANDS_NUMBER];
    vector<int>  productInt;
    vector<size_t> stage,
                   curDigit;
    size_t       operandsInLine  = 0;

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

    for (size_t step = 0; step < STEPS_NUMBER; step++){
        mainWindow.printText("\n\nSTEP N" + stringify(step) + ":");

        for (size_t curOpera = 0; curOpera <= operandsInLine; curOpera++){
            if (int(curDigit[curOpera]) - DIGITS_NUMBER > 0){
                continue;
            }

            switch(stage[curOpera]){
            case 0:
                currentSummand[curOpera] = multiplicand[curOpera];
                if (multiplier[curOpera][curDigit[curOpera]] == 1){
                    if (curDigit[curOpera] > 0){
                        mainWindow.printText("\n" + stringify(curOpera+1) + ") shifting ");
                        out(multiplicand[curOpera], mainWindow);
                        mainWindow.printText(" <[" + stringify(curDigit[curOpera]) + "]< ");

                        currentSummand[curOpera] = shift(multiplicand[curOpera], curDigit[curOpera]);

                        out(currentSummand[curOpera], mainWindow);
                    }
                } else {
                    curDigit[curOpera]++;
                }
                stage[curOpera] ++;
                break;
            case 1:
                if (multiplier[curOpera][curDigit[curOpera]] == 1){
                    mainWindow.printText("\n" + stringify(curOpera+1) + ") ");
                    out(product[curOpera], mainWindow);
                    mainWindow.printText(" + ");
                    out(currentSummand[curOpera], mainWindow);
                    mainWindow.printText(" = ");

                    product[curOpera] = addition(product[curOpera], currentSummand[curOpera]);

                    out(product[curOpera], mainWindow);
                }
                curDigit[curOpera]++;
                stage[curOpera] = 0;
                break;
            }
        }

        if(operandsInLine < OPERANDS_NUMBER - 1){
            operandsInLine++;
        }
    }

     mainWindow.printText("\nRESULTS:\n");

    for (size_t i = 0; i < OPERANDS_NUMBER; i++){
        productInt.push_back(boolToInt(product[i]));
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

vector<bool> Pipeline::addition(vector<bool> &summand1,
                                const vector<bool> &summand2){
    vector<bool> summ(summand2.size());
    bool		 extraDigit = 0;
    int			 iterationSumm = 0;
    size_t       i;

    for (i = 0 ; i < summand2.size(); i++){
        if(summand1.size() <= i){
            summand1.push_back(0);
        }
        iterationSumm = summand1[i]+summand2[i]+extraDigit;
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
