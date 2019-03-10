#include "pipeline.h"
#include "mainwindow.h"


vector<vector<bool>> Pipeline::start(const vector<int> &vectorMd,
                                     const vector<int> &vectorMr,
                                     MainWindow        &mainWindow) {

    vector<vector<bool>>	vectorRB;
    vector<bool>			multiplicand,
                            multiplier,
                            product;

    mainWindow.printText("$$$$$$$$Pipeline starts here$$$$$$$$\n");

    for (size_t i = 0; i < vectorMd.size(); i++) {
        multiplicand = intToBool(vectorMd[i]);
        mainWindow.printText(stringify(vectorMd[i]) + " = ");
        out(multiplicand, mainWindow);

        multiplier = intToBool(vectorMr[i]);
        mainWindow.printText("\n" + stringify(vectorMr[i]) + " = ");
        out(multiplier, mainWindow);

        product = binaryMultipl(multiplicand, multiplier);
        mainWindow.printText("\n==\n");
        out(product, mainWindow);
        mainWindow.printText("\n");
    }

    mainWindow.printText("&&&&&&&&Pipeline stops here&&&&&&&&\n");

    return vectorRB;
}

vector<bool> Pipeline::intToBool(int intVal) {

    vector<bool>	binVal(NUMBER_OF_DIGITS);

    for (size_t i = 0; i < NUMBER_OF_DIGITS; i++){
        binVal[i] = (intVal & 1);
        intVal >>= 1;
    }

    return binVal;
}

vector<bool> Pipeline::binaryMultipl(const vector<bool> &multiplicand,
                                     const vector<bool> &multiplier) {

    vector<bool>	product(NUMBER_OF_DIGITS*2),
                    curSmd = multiplicand;

    for (size_t i = 0 ; i < NUMBER_OF_DIGITS ; i++){
        if (multiplier[i] == 1) {
            if (i > 0) {
                curSmd = shift(multiplicand, i);
            }
            product = addition(product, curSmd);
        }
    }

    return product;
}

vector<bool> Pipeline::addition(const vector<bool> &summand1,
                                const vector<bool> &summand2) {

    vector<bool>	summ(summand1.size());
    bool			extraDigit = 0;
    int				iterationSumm = 0;
    size_t          i;

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

vector<bool> Pipeline::shift(const vector<bool> &operand,
                             const size_t       &shift) {

    vector<bool> rezult(operand.size() + shift);

    for (size_t i = shift; i < rezult.size(); i++) {
        rezult[i] = operand[i - shift];
    }

    return rezult;
};

void Pipeline::out(const vector<bool> &input,
                   MainWindow         &mainWindow) {

    for (size_t i = input.size() - 1; i < input.size(); i--) {
        mainWindow.printText(stringify(input[i]));
    }
}
