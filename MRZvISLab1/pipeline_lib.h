#include <iostream>
#include <vector>

using namespace std;


class Pipeline {
public:
	vector<bool*> start(const vector<int>, const vector<int>);
private:
	static const int NUMBER_OF_DIGITS = 6;
	static const int NOD_STARTING_FROM_0 = NUMBER_OF_DIGITS-1;
	static const int NOD_MAX = 13;
	
	bool* intToBool(const int);
	bool* binaryMultipl(const bool*, const bool*);
	bool* addition (const bool*, const bool*);	//Overloaing operator requires to create a new class
	bool* shift (const bool*, const int);
};
