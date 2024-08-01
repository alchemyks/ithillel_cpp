#include <iostream>

#include <thread>
#include <chrono>

#include "lib/pcp.h"

int main() {
	pcp test_pcp;
	test_pcp.start();
	for(int i = 0; i < 10; ++i){
		for(int j = i; j < 10; ++j){
			test_pcp.add_task(j);
		}
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}

}