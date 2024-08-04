#include <iostream>

#include <vector>

#include <string>
#include <string.h>

#include <algorithm>

#include <cassert>






struct Person {
    std::string first_name;
    std::string last_name;  
    int age;
	
  };


  std::ostream& operator<<(std::ostream& os, const Person& p){
	return os << p.first_name << ", " << p.last_name << ", " << p.age; 
}
  
int main(int argc, char** argv) {

	std::vector<Person> people = {
    							{"Yoda", "", 900},
    							{"Obi-Wan", "Kenobi", 38},
    							{"Leia", "Organa", 25},
    							{"Anakin", "Skywalker", 22}
  							};


	std::cout << "Sotr for first name: " << std::endl;
	std::sort(people.begin(), people.end(), [](const Person& a, const Person& b){
											return  strcasecmp(a.first_name.c_str(), b.first_name.c_str()) <= 0;
										});
	for(auto item: people){
		std::cout << item << std::endl;
	}

	std::cout << "Sotr for last name: " << std::endl;
	std::sort(people.begin(), people.end(), [](const Person& a, const Person& b){
											return  strcasecmp(a.last_name.c_str(), b.last_name.c_str()) <= 0;
										});
	for(auto item: people){
		std::cout << item << std::endl;
	}

	std::cout << "Sotr for age: " << std::endl;
	std::sort(people.begin(), people.end(), [](const Person& a, const Person& b){
											return  a.age < b.age;
										});
	for(auto item: people){
		std::cout << item << std::endl;
	}

return 0;
}