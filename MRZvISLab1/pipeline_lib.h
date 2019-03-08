#include <iostream>
#include <vector>

using namespace std;


class Pipeline {
public:
	
	static vector<vector<bool>> start(const vector<int>, const vector<int>);
private:

	static const int NUMBER_OF_DIGITS = 6;
	
	static vector<bool> intToBool(const int);
	static vector<bool> binaryMultipl(const vector<bool>, const vector<bool>);
	static vector<bool> addition (const vector<bool>, const vector<bool>);
	static vector<bool> shift (const vector<bool>, const int);
	static void out(const vector<bool>&);
};
