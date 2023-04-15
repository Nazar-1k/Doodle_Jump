// C++ program for demonstrating 
#include <ctime>
#include <iostream>
#include <random>
using namespace std;

int main()
{
	// Initializing the sequence 
	// with a seed value
	// similar to srand()
	mt19937 mt(time(nullptr));

	// Printing a random number
	// similar to rand()
	cout << mt.default_seed << '\n';
	return 0;
}