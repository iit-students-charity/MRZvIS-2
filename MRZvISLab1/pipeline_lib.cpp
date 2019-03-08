#include "pipeline_lib.h"


vector<vector<bool>> Pipeline::start(const vector<int> vectorMd, const vector<int> vectorMr) {

	vector<vector<bool>>	vectorRB;
	vector<bool>			multiplicand,
							multiplier,
							product;

	cout << "$$$$$$$$Pipeline starts here$$$$$$$$\n";

	for (int i = 0; i < vectorMd.size(); i++) {
		multiplicand = intToBool(vectorMd[i]);
		cout << vectorMd[i] << " = ";
		out(multiplicand);

		multiplier = intToBool(vectorMr[i]);
		cout << endl << vectorMr[i] << " = ";
		out(multiplier);

		product = binaryMultipl(multiplicand, multiplier);
		cout << "\n==\n";
		out(product);
		cout << endl;

		system("pause");
	}

	cout << "&&&&&&&&Pipeline stops here&&&&&&&&\n";

	return vectorRB;
}

vector<bool> Pipeline::intToBool(int intVal) {

	vector<bool>	binVal(NUMBER_OF_DIGITS);

	for (int i = 0; i < NUMBER_OF_DIGITS; i++){
		binVal[i] = (intVal & 1);
		intVal >>= 1;
	}

	return binVal;
}

vector<bool> Pipeline::binaryMultipl(const vector<bool> multiplicand, const vector<bool> multiplier) {

	vector<bool>	product(NUMBER_OF_DIGITS*2),
					curSmd = multiplicand;

	for (int i = 0 ; i < NUMBER_OF_DIGITS ; i++){
		if (multiplier[i] == 1) {
			if (i > 0) {
				curSmd = shift(multiplicand, i);
			}
			product = addition(product, curSmd);
		}
	}

	return product;
}

vector<bool> Pipeline::addition(const vector<bool> summand1, const vector<bool> summand2) {

	vector<bool>	summ(summand1.size());
	bool			extraDigit = 0;
	int				iterationSumm = 0,
					i;

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

vector<bool> Pipeline::shift(const vector<bool> operand, const int shift) {

	vector<bool> rezult(operand.size() + shift);

	for (int i = shift; i < rezult.size(); i++) {
		rezult[i] = operand[i - shift];
	}

	return rezult;
};

void Pipeline::out(const vector<bool> &input) {

	for (int i = 0; i < input.size(); i++) {
		cout << input[i];
	}
}
