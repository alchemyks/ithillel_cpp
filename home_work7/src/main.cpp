#include <iostream>
#include <cstdlib>

#include <vector>
#include <chrono>

#include <future>

#include <cassert>

int main(int argc, char** argv) {



	srand((unsigned) time(NULL));
	std::vector<int> test_vector(100000000);
	for(int i = 0; i < test_vector.size(); ++i){
		test_vector[i] = rand() % 100;
	}

	int const half_index = test_vector.size() / 2;

	auto begin_single_thread = std::chrono::steady_clock::now();

	std::future<int> ftr_sum = std::async([&test_vector](){ 
													int sum = 0;
													for(auto item = test_vector.begin(); item < test_vector.end(); ++item){
														sum+=*item;
													}
													return sum;
	 											});
	
	int sum_single_thread = ftr_sum.get();

	auto end_single_thread = std::chrono::steady_clock::now();


	auto begin_two_thread = std::chrono::steady_clock::now();
	std::future<int> ftr_sum_first_half = std::async([&test_vector, half_index](){ 
													int sum = 0;
													for(auto item = test_vector.begin(); item < test_vector.begin() + half_index; ++item ){
														sum+=*item;
													}
													return sum;
	 											});

	
	std::future<int> ftr_sum_second_half = std::async([&test_vector, half_index](){ 
													int sum = 0;
													for(auto item = test_vector.begin() + half_index; item < test_vector.end(); ++item){
														sum+=*item;
													}
													return sum;
	 											});

	
	int result = ftr_sum_first_half.get() + ftr_sum_second_half.get();

    auto end_two_thread = std::chrono::steady_clock::now();
	
	std::cout << "Single thread sum = " << sum_single_thread << " time: " << 
										std::chrono::duration_cast<std::chrono::milliseconds>(end_single_thread - begin_single_thread).count() << std::endl;
	std::cout << "Two thread sum = " << result << " time: " << 
										std::chrono::duration_cast<std::chrono::milliseconds>(end_two_thread - begin_two_thread).count() << std::endl;

	return 0;
}