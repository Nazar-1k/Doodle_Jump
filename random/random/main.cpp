#include <iostream>
#include <cassert>
#include <random>

int main() {

std::uniform_int_distribution<int> dist(0, 99);
#pragma region linear_congruential_engine

	std::linear_congruential_engine<unsigned int, 48271, 0, 2147483647> generator;

	generator.seed(std::random_device()());
	

	std::cout << "linear_congruential_engine -> " << dist(generator) << std::endl;
	
#pragma endregion 

#pragma region mersenne_twister_engine
	
	std::mt19937 gen(std::random_device{}());

	

	std::cout << "mersenne_twister_engine -> " << dist(gen) << std::endl;
	

#pragma endregion

#pragma region subtract_with_carry_engine

	std::subtract_with_carry_engine<unsigned, 24, 10, 24> rng;

	std::seed_seq seed{ 1, 2, 3, 4, 5 };
	rng.seed(seed);

	std::cout << "subtract_with_carry_engine -> " << dist(rng) << std::endl;


#pragma endregion
	

	return 0;
}