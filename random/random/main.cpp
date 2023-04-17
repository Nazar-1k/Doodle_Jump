#include <iostream>
#include <random>

int main() {

	
#pragma region linear_congruential_engine

	std::linear_congruential_engine<unsigned int, 48271, 0, 2147483647> generator;

	generator.seed(std::random_device()());
	std::uniform_int_distribution<int> distribution(0, 100);

	std::cout << "linear_congruential_engine -> " << distribution(generator) << std::endl;
	
#pragma endregion 

	return 0;
}