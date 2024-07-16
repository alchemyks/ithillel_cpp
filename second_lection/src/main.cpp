#include<iostream>
#include<vector>




int main(int argc, char** argv){
    int a[1000000];

std::vector<int> vect = {1,2,3,4,5};
for (int item : vect){
    std::cout << item << '\t';
}
std::cout << std::endl;
}
