//============================================================================
// Name        : physics.cpp
// Author      : Simon Rothman
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <chrono>
#include <ratio>

using namespace std;

void test(){
	int x=0;
	for(int i=0;i<10000;i++){
		x++;
	}
}

double timeit(void (*f)()){
	using namespace std::chrono;
	high_resolution_clock::time_point start = high_resolution_clock::now();

	f();

	high_resolution_clock::time_point end = high_resolution_clock::now();

	duration<double> time_span=duration_cast<duration<double> >(end-start);

	return time_span.count();
}

int main() {
	cout << timeit(test) << endl;
	return 0;
}
