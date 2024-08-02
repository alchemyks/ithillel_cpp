#include <iostream>

#include <thread>
#include <chrono>

#include "lib/safety_vector.h"

#include <cassert>

int main(int argc, char** argv) {
	safety_vector<int> vector;
	vector.push_back(100);
	assert(vector.size() == 1);
	assert(vector.get(0) == 100);
	vector.erase(0);
	assert(vector.size() == 0);
	

}