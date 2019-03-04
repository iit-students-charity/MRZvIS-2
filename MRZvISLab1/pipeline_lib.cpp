#include "pipeline_lib.h"


vector<bool *> Pipeline::start(const vector<int> vectorMd, const vector<int> vectorMr) {

	vector<bool *>	output;
	bool			*multiplicand,
					*multiplier,
					*vectorRB;

	cout << "$$$$$$$$Pipeline start's here$$$$$$$$\n";

	for (int i = 0; i < sizeof(vectorMd); i++) {
		multiplicand = intToBool(vectorMd[i]);
		multiplier = intToBool(vectorMr[i]);
		vectorRB = binaryMultipl(multiplicand, multiplier);

		for (int j = 0; j < sizeof(vectorRB); j++) {
			cout << vectorRB[j];
		}
		cout << endl;
		system("pause");
	}

	return output;
	cout << "&&&&&&&&Pipeline stop's here&&&&&&&&\n";
}

bool *Pipeline::intToBool(int intVal) {

	bool*	binVal = new bool[NUMBER_OF_DIGITS];

	for (int i = 0; i < NUMBER_OF_DIGITS; i++){
		binVal[i] = (intVal & 1);
		intVal >>= 1;
		cout << binVal[i];
	}
	return binVal;
}

bool *Pipeline::binaryMultipl(const bool *multiplicand, const bool *multiplier) {

	bool 	*product = new bool[NOD_MAX] { 0 },
			*curSmd;

	for (int i = 0 ; i < NUMBER_OF_DIGITS ; i++){
		if(multiplier [i] == 1){
			curSmd = shift(multiplicand, i);
			product = addition(product, curSmd);
		}
	}

	return product;
}

bool *Pipeline::addition(const bool *summand1, const bool *summand2) {

	const int 	NUMDER_OF_DIGITS_HERE = sizeof(summand1);
	bool		*summ = new bool[NUMDER_OF_DIGITS_HERE];
	bool		extraDigit = 0;
	int			tempSumm = 0;

	for (int i = 0 ; i < NUMBER_OF_DIGITS ; i++){
		tempSumm += summand1[i]+summand2[i]+extraDigit;
		if(tempSumm > 1){
			extraDigit = 1;
		} else {
			extraDigit = 0;
		}
		summ[i] = tempSumm % 2;
	}
	if(extraDigit == 1){
		summ[NUMDER_OF_DIGITS_HERE] = extraDigit;
	}

	return summ;
}

bool *Pipeline::shift(const bool *operand, const int shift) {

	bool* rezult = new bool[sizeof(operand) + shift]{ 0 };

	for (int i = shift; i < sizeof(rezult); rezult[i] = operand[i++ - shift]);	//DANGEROUS CODE!!!

	return rezult;
};
