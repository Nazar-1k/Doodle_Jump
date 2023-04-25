#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>

int main() {

	std::uniform_int_distribution<int> dist(0, 99);
#pragma region 	Random_number_engines

#pragma region linear_congruential_engine

		std::linear_congruential_engine<unsigned int, 48271, 0, 2147483647> generator1(std::random_device{}());

		std::cout << "linear_congruential_engine -> " << dist(generator1) << std::endl;

	#pragma endregion 

#pragma region mersenne_twister_engine

		std::mt19937 generator2(std::random_device{}());

		std::cout << "mersenne_twister_engine -> " << dist(generator2) << std::endl;


#pragma endregion

#pragma region subtract_with_carry_engine

		std::subtract_with_carry_engine<unsigned, 24, 10, 24> generator3(std::random_device{}());


		std::cout << "subtract_with_carry_engine -> " << dist(generator3) << std::endl;


	#pragma endregion
	
#pragma endregion

#pragma region Random_number_engine_adaptors
		
	#pragma region discard_engine

			std::discard_block_engine<std::mt19937, 4096, 4096> generator4(std::random_device{}());
			std::cout << "discard_engine -> " << dist(generator4) << std::endl;

	#pragma endregion

	#pragma region independent_bits_engine

			std::independent_bits_engine<std::mt19937, 32, uint32_t> generator5(std::random_device{}());
			std::cout << "independent_bits_engine -> " << dist(generator5) <<  std::endl;

	#pragma endregion	
		
	#pragma region shuffle_order_engine

		std::mt19937 gen(std::random_device{}());

		std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		std::shuffle_order_engine<std::mt19937, 10> engine(gen);

		std::cout << "Random sequence: ";
		for (int i = 0; i < 10; i++) {
			std::cout << dist(engine) << " ";
		}
		std::cout << std::endl;


	#pragma endregion	

#pragma endregion
	

#pragma region Predefined_random_number_generators

	#pragma region minstd_rand0

		std::minstd_rand0 generator6(std::random_device{}());
		std::cout << "minstd_rand0 ->  " << dist(generator6) << std::endl; 

	#pragma endregion
	#pragma region minstd_rand

		std::minstd_rand generator7(std::random_device{}());  
		std::cout << "minstd_rand -> " << dist(generator7) << std::endl;

	#pragma endregion
	#pragma region mt19937

		std::mt19937 generator8(std::random_device{}());
		std::cout << "mt19937 -> " << dist(generator8) << std::endl;

	#pragma endregion
#pragma endregion
	return 0;
}