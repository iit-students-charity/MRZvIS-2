#include <iostream>
#include <vector>

using namespace std;


class Pipeline {
public:
	static vector<bool *> start(const vector<int>, const vector<int>);
private:
	static const int NUMBER_OF_DIGITS = 6;
	static const int NOD_STARTING_FROM_0 = NUMBER_OF_DIGITS-1;
	static const int NOD_MAX = 13;
	
	static bool *intToBool(const int);
	static bool *binaryMultipl(const bool*, const bool*);
	static bool *addition (const bool*, const bool*);	//Overloaing operator requires to create a new class
	static bool *shift (const bool*, const int);
};
