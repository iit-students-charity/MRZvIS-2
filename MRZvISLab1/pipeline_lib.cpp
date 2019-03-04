#include "pipeline_lib.h"


vector<bool*> Pipeline::start(const vector<int> vectorA, const vector<int> vectorB){

	vector<bool*> output;

	cout << "$$$$$$$$Pipeline start's here$$$$$$$$\n";



	return output;
	cout << "&&&&&&&&Pipeline stop's here&&&&&&&&\n";
}

bool* Pipeline::intToBool(const int input) {

	bool*	output = new bool[NUMBER_OF_DIGITS];
	int		temp = input;

	for (int i = 0; i < NUMBER_OF_DIGITS; i++){
		output[i] = (temp & 1);
		temp >>= 1;
		cout << output[i];
	}
	return output;
}

bool* Pipeline::binaryMultipl(const bool* factor1, const bool* factor2){

	bool* 	result = new bool[NOD_MAX],
			currentTerm;

	for (int i = 0 ; i < NUMBER_OF_DIGITS ; i++){
		if(factor2 [i] == 1){
			currentTerm = shift(factor1, i);
		}
	}
}

bool* Pipeline::addition (const bool* term1, const bool* term2){

	const int 	NUMDER_OF_DIGITS_HERE = sizeof(term1);
	bool*		rezult = new bool[NUMDER_OF_DIGITS_HERE];
	bool		extraDigit = 0;
	int			tempSumm = 0;

	for (int i = 0 ; i < NUMBER_OF_DIGITS ; i++){
		tempSumm += term1[i]+term2[i]+extraDigit;
		if(tempSumm > 1){
			extraDigit = 1;
		} else {
			extraDigit = 0;
		}
		rezult[i] = tempSumm % 2;
	}
	if(extraDigit == 1){
		rezult[NUMDER_OF_DIGITS_HERE] = extraDigit;
	}
}

bool* Pipeline::shift (const bool* binNum, const int shift){

	bool* rezult = new bool[sizeof(binNum) + shift]{ 0 };

	for (int i = shift; i < sizeof(rezult); rezult[i] = binNum[i++ - shift]);	//DANGEROUS CODE!!!

	return rezult;
};
