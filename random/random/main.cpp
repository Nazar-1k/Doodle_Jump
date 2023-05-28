#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include <array>

int main() {


#pragma region Random_number_distributions

	#pragma region UniformDistributions

		#pragma region uniform_int_distribution

		// is a C++ standard library class template that provides a way to generate uniformly distributed random integers within a given range. It is defined in the <random> header and is part of the C++11 standard.
			std::uniform_int_distribution<int> dist(0, 99);

		#pragma endregion
		#pragma region uniform_real_distribution

			std::random_device rd; 
			std::mt19937 gen1(rd()); 
			std::uniform_real_distribution<double> distReal(0, 1); 

			double randomReal = distReal(gen1);

			std::cout << "A random real number: " << randomReal << std::endl << std::endl;


		#pragma endregion

	#pragma endregion

	#pragma region Bernoulli distributions
		#pragma region bernoulli_distribution
			
				std::bernoulli_distribution dist1(0.3);	
				std::mt19937 rng1(std::random_device{}());
				std::cout << "(bernoulli_distribution)Did the event happen? " << std::boolalpha << dist1(rng1)<< std::endl;

		#pragma endregion

		#pragma region	binomial_distribution

				std::binomial_distribution<int> dist2(10, 0.3);
				std::mt19937 rng2(std::random_device{}());
				std::cout << "(binomial_distribution) -> " << dist2(rng2) << std::endl;

		#pragma endregion

		#pragma region negative_binomial_distribution

				std::negative_binomial_distribution<int> dist3(10, 0.3);
				std::mt19937 rng3(std::random_device{}());
				std::cout << "(negative_binomial_distribution) -> " << dist3(rng3) << std::endl;
				

		#pragma endregion	

		#pragma region geometric_distribution

				std::mt19937 rng4(std::random_device{}());
				std::geometric_distribution<int> dist4(0.1);
				std::cout << "(geometric_distribution) -> " << dist4(rng4) << std::endl;

		#pragma endregion
		
	#pragma endregion

	#pragma region Poisson_distributions

		#pragma region poisson_distribution
			std::poisson_distribution<int> dist5(3.0);
			std::mt19937 rng5(std::random_device{}());
			std::cout << "(Poisson_distributions) -> " << dist5(rng5) << std::endl;
		#pragma endregion

		#pragma region exponential_distribution

			std::exponential_distribution<double> dist6(3.0);
			std::mt19937 rng6(std::random_device{}());
			std::cout << "(exponential_distribution) -> " << dist6(rng6) << std::endl;

		#pragma endregion

		#pragma region gamma_distribution

			std::gamma_distribution<double> dist7(100.0);
			std::mt19937 rng7(std::random_device{}());
			std::cout << "(gamma_distribution) -> " << dist7(rng7) << std::endl;

		#pragma endregion

		#pragma region weibull_distribution

			std::weibull_distribution<double> dist8(100.0);
			std::mt19937 rng8(std::random_device{}());
			std::cout << "(weibull_distribution) -> " << dist8(rng8) << std::endl;

		#pragma endregion


		#pragma region extreme_value_distribution

			std::extreme_value_distribution<double> dist9(100.0);
			std::mt19937 rng9(std::random_device{}());
			std::cout << "(extreme_value_distribution) -> " << dist9(rng9) << std::endl;

		#pragma endregion

	#pragma endregion

	#pragma region Normal_distributions

		// We define the parameters of the normal distribution
		double mean = 0.0;  // Average value
		double stddev = 100;  // Standard deviation

		#pragma region normal_distribution

			std::mt19937 gen10(std::random_device{}());
			std::normal_distribution<double> dist10(mean, stddev);
			std::cout << "A random number with a normal distribution: " << dist10(gen10) << std::endl;

		#pragma endregion

		#pragma region lognormal_distribution

			std::mt19937 gen11(std::random_device{}());
			std::lognormal_distribution<float> dist11(mean, stddev);
			std::cout << "A random number with a lognormal distribution: " << dist11(gen11) << std::endl;

		#pragma endregion

		#pragma region chi_squared_distribution

			std::mt19937 gen12(std::random_device{}());
			// We define the parameters of the normal distribution
			std::chi_squared_distribution<float> dist12(stddev);
			std::cout << "A random number with a chi_squared_distribution: " << dist12(gen12) << std::endl;

		#pragma endregion


		#pragma region cauchy_distribution

			std::mt19937 gen13(std::random_device{}());
			// We define the parameters of the normal distribution
			std::cauchy_distribution<float> dist13(stddev);
			std::cout << "A random number with a cauchy_distribution: " << dist13(gen13) << std::endl;

		#pragma endregion
			

		#pragma region fisher_f_distribution

			std::mt19937 gen14(std::random_device{}());
			// We define the parameters of the normal distribution
			std::fisher_f_distribution<float> dist14(stddev);
			std::cout << "A random number with a fisher_f_distribution: " << dist14(gen14) << std::endl;

		#pragma endregion
			

		#pragma region student_t_distribution

			std::mt19937 gen15(std::random_device{}());
			// We define the parameters of the normal distribution
			std::student_t_distribution<double> dist15(stddev);
			std::cout << "A random number with a student_t_distribution: " << dist15(gen15) << std::endl;

		#pragma endregion
			


	#pragma endregion

#pragma region Sampling distributions

		#pragma region discrete_distribution

			std::vector<double> probabilities = { 0.1, 0.3, 0.6 }; // ��������� ��������
			std::mt19937 gen16(std::random_device{}());
			std::discrete_distribution<> d16(probabilities.begin(), probabilities.end());

			std::cout << "Generate a random number discrete_distribution: " << d16(gen16) << std::endl;
			
		#pragma endregion

		#pragma region piecewise_constant_distribution

			std::vector<double> intervals = { 0.0, 1.0, 2.0, 3.0 };
			std::vector<double> weights = { 1.0, 2.0, 3.0 };

			std::mt19937 gen17(std::random_device{}());

			std::piecewise_constant_distribution<double> dist17(intervals.begin(), intervals.end(), weights.begin());

			std::cout << "Generate a random number piecewise_constant_distribution: " << dist17(gen17) << std::endl;

		#pragma endregion


#pragma region piecewise_linear_distribution

			std::vector<double> intervals2 = { 0.0, 1.0, 2.0, 3.0 };
			std::vector<double> weights2 = { 0.1, 0.4, 0.3, 0.2 };

			std::mt19937 gen18(std::random_device{}());
			std::piecewise_linear_distribution<double> dist18(intervals2.begin(), intervals2.end(), weights2.begin());

			std::cout << "Generate a random number piecewise_linear_distribution: " << dist18(gen18) << std::endl;

#pragma endregion

			



#pragma endregion

#pragma endregion

#pragma region Utilities

	#pragma region generate_canonical

			std::mt19937 gen19(std::random_device{}());

			// �������� ��������������� ����� � ��������� ������� � ������� [0, 1)
			double random_number19 = std::generate_canonical<double, 10>(gen19);
			std::cout << "generate_canonical: " << random_number19 << std::endl;

	#pragma endregion

#pragma endregion


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
	#pragma region mt19937_64

		std::mt19937_64 generator9(std::random_device{}());
		std::cout << "mt19937_64 -> " << dist(generator9) << std::endl;
	
	#pragma endregion
	#pragma region ranlux24_base


			std::ranlux24_base generator10(std::random_device{}());
			std::cout << "ranlux24_base -> " << dist(generator10) << std::endl;

	#pragma endregion
	#pragma region ranlux48_base


			std::ranlux48_base generator11(std::random_device{}());
			std::cout << "ranlux48_base -> " << dist(generator11) << std::endl;

	#pragma endregion	
	#pragma region ranlux24


			std::ranlux24 generator12(std::random_device{}());
			std::cout << "ranlux24 -> " << dist(generator12) << std::endl;

	#pragma endregion
	#pragma region ranlux48

		std::ranlux48 generator13(std::random_device{}());
		std::cout << "ranlux48 -> " << dist(generator13) << std::endl;

	#pragma endregion
	#pragma region knuth_b


		std::knuth_b generator14(std::random_device{}());
		std::cout << "knuth_b -> " << dist(generator14) << std::endl;

	#pragma endregion	
	#pragma region default_random_engine

		std::default_random_engine generator15(std::random_device{}());
		std::cout << "default_random_engine -> " << dist(generator15) << std::endl;

	#pragma endregion 

#pragma endregion
#pragma region Non-deterministic_random_numbers

	#pragma region random_device
			std::cout << "Example random_device -> " << dist(generator12) << std::endl;
	#pragma endregion random_device

#pragma endregion


	return 0;
}

