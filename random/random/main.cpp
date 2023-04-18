#include <iostream>
#include <cassert>
#include <random>

int main() {

	
#pragma region linear_congruential_engine

	std::linear_congruential_engine<unsigned int, 48271, 0, 2147483647> generator;

	generator.seed(std::random_device()());
	std::uniform_int_distribution<int> distribution(0, 100);

	std::cout << "linear_congruential_engine -> " << distribution(generator) << std::endl;
	
#pragma endregion 


#pragma region mersenne_twister_engine
	
	std::mt19937 gen(std::random_device{}());

	std::uniform_int_distribution<int> dist(0, 99);

	std::cout << "mersenne_twister_engine -> " << dist(gen) << std::endl;
	

#pragma endregion
	return 0;
}