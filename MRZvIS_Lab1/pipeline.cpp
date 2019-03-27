#include "pipeline.h"
#include "mainwindow.h"


vector<bool>* Pipeline::start(const vector<int> &vectorMd,
                                     const vector<int> &vectorMr,
                                     MainWindow        &mainWindow) {
    const size_t OPERAND_NUMB    = vectorMd.size();
    vector<bool> *multiplicand   = new vector<bool>[OPERAND_NUMB],
                 *multiplier     = new vector<bool>[OPERAND_NUMB],
                 *currentSummand = new vector<bool>[OPERAND_NUMB],
                 *product        = new vector<bool>[OPERAND_NUMB];
    size_t       operandsInLine  = 0,
                 *stage          = new size_t[OPERAND_NUMB],
                 curDig          = 0;

    mainWindow.printText("$$$$$$$$Pipeline starts here$$$$$$$$\n");
    qDebug("$$$$$$$$Pipeline starts here$$$$$$$$\n");

    mainWindow.printText("CONVERTING INT TO BOOL...");
    for (size_t i = 0; i < OPERAND_NUMB; i++){
        multiplicand[i] = intToBool(vectorMd[i]);

        mainWindow.printText("\nPair " + stringify(i) + ":\n" +
                             stringify(vectorMd[i]) + " = ");
        out(multiplicand[i], mainWindow);

        multiplier[i] = intToBool(vectorMr[i]);

        mainWindow.printText("\n" + stringify(vectorMr[i]) + " = ");
        out(multiplier[i], mainWindow);

        product[i] = intToBool(0);
        stage[i] = 0;
    }

    for (size_t step = 0; step < NUMBER_OF_DIGITS*OPERAND_NUMB; step++){
        mainWindow.printText("\n\nSTEP N" + stringify(step) + ":");
        qDebug() << "step " << step;

        for (size_t curOpera = 0; curOpera <= operandsInLine; curOpera++){
            qDebug() << step << " - " << curOpera << " - " << stage[curOpera];
            curDig = step - curOpera - stage[curOpera];
            qDebug() << ">curDig         = " << curDig;
            if (int(curDig) - NUMBER_OF_DIGITS > 0){
                qDebug() << "dead cell " << int(curDig) - NUMBER_OF_DIGITS;
                continue;
            }

            switch(stage[curOpera]){
            case 0:
                qDebug() << "case 0";
                qDebug() << ">curOpera       = " << curOpera;
                qDebug() << ">operandsInList = " << operandsInLine;
                qDebug() << ">multiplicand   = " << multiplicand[curOpera];
                qDebug() << ">currentSummd   = " << currentSummand[curOpera];
                currentSummand[curOpera] = multiplicand[curOpera];

                if (multiplier[curOpera][curDig] == 1){
                    if (curDig > 0) {
                        qDebug() << "shifting" << curOpera;
                        mainWindow.printText("\n" + stringify(curOpera+1) + ") shifting ");
                        out(multiplicand[curOpera], mainWindow);
                        mainWindow.printText(" <[" + stringify(curDig) + "]< ");

                        currentSummand[curOpera] = shift(multiplicand[curOpera], curDig);
                    }
                }
                out(currentSummand[curOpera], mainWindow);

                stage[curOpera] ++;
                qDebug() << "case 0 end";
                break;
            case 1:
                qDebug() << "case 1";

                if (multiplier[curOpera][curDig] == 1){
                    qDebug() << "additing" << curOpera;
                    mainWindow.printText("\n" + stringify(curOpera+1) + ") ");
                    out(product[curOpera], mainWindow);
                    mainWindow.printText(" + ");
                    out(currentSummand[curOpera], mainWindow);
                    mainWindow.printText(" = ");

                    product[curOpera] = addition(product[curOpera], currentSummand[curOpera]);
                }
                out(product[curOpera], mainWindow);

                stage[curOpera] = 0;
                qDebug() << "case 1 end";
                break;
            }
        }

        if(operandsInLine < OPERAND_NUMB - 1){
            operandsInLine++;
            stage[operandsInLine] = 0;
        }

        qDebug() << "step end";
    }

     mainWindow.printText("\nRESULTS:\n");
    for (size_t i = 0; i < OPERAND_NUMB; i++) {
        mainWindow.printText("\n" + stringify(i) + ") " + stringify(boolToInt(product[i])) + " = ");
        out(product[i], mainWindow);
    }

    mainWindow.printText("\n&&&&&&&&Pipeline stops here&&&&&&&&\n");
    qDebug() << "\n&&&&&&&&Pipeline stops here&&&&&&&&\n";

    return product;
}

vector<bool> Pipeline::intToBool(int intNum) {
    vector<bool>	binNum(NUMBER_OF_DIGITS);

    for (size_t i = 0; i < NUMBER_OF_DIGITS; i++){
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
                             const size_t       &shift) {
    vector<bool> rezult(operand.size() + shift);

    for (size_t i = shift; i < rezult.size(); i++) {
        rezult[i] = operand[i - shift];
    }

    return rezult;
};

vector<bool> Pipeline::addition(const vector<bool> &summand1,
                                const vector<bool> &summand2) {
    vector<bool> summ(summand1.size() + 1);
    bool		 extraDigit = 0;
    int			 iterationSumm = 0;
    size_t       i;

    for (i = 0 ; i < summand2.size(); i++){
        iterationSumm = summand1[i]+summand2[i]+extraDigit;
        extraDigit = (iterationSumm > 1) ? 1 : 0;
        summ[i] = iterationSumm % 2;
    }
    if(extraDigit == 1){
        summ[++i] = extraDigit;
    }

    return summ;
}

void Pipeline::out(const vector<bool> &input,
                   MainWindow         &mainWindow) {
    for (size_t i = input.size() - 1; i < input.size(); i--) {
        mainWindow.printText(stringify(input[i]));
    }
}
