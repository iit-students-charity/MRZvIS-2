#include <iostream>
#include <vector>
#include <thread>
#include "pipeline_lib.h"

using namespace std;


int main() {

	vector<int>		vectorA,
					vectorB,
					vectorRezult;

	vectorA.push_back({ 8 });
	vectorB.push_back({ 7 });

	vectorA.push_back({ 10 });
	vectorB.push_back({ -9 });

	vectorA.push_back({ 16 });
	vectorB.push_back({ 16 });

	Pipeline::start(vectorA, vectorB);

	system("pause");
	return 1;
}
