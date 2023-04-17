#include <ctime>
#include <iostream>
#include <random>

int main()
{
	
	std::mt19937 mt(time(nullptr));

	std::cout << mt.mask_bits << '\n';
	return 0;
}