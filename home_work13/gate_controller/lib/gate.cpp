#include <iostream>
#include "gate.h"

Gate::Gate(QObject *parent)
    : QObject{parent}
{}

Gate::Gate(int initial_opening){
    if(isSpanValid(initial_opening)){
        current_opening = initial_opening;
        std::cout << "Initial gate state: " << current_opening << "%" << std::endl;
    }else{
        current_opening = 0;
        std::cout << "Initial gate state must be between 0 and 100: " << current_opening << "%";
    }
}

void Gate::open(int percentage){
    if(isSpanValid(percentage)){
        current_opening = current_opening + percentage > 100 ? 100 : current_opening + percentage;
        std::cout << "Gate opened to " << current_opening << "%." << std::endl;
    }else{
        std::cout << "Invalid opening percentage. Must be between 0 and 100." << std::endl;
    }
}

void Gate::close(int percentage){
    if(isSpanValid(percentage)){
        current_opening = current_opening - percentage < 0 ? 0 : current_opening - percentage;
        std::cout << "Gate closed to " << current_opening << "%." << std::endl;
    }else{
        std::cout << "Invalid closing percentage. Must be between 0 and 100." << std::endl;
    }
}

bool Gate::isClosed() const{
    if(current_opening == 0){
        std::cout << "Gate is closed!" << std::endl;
        return true;
    }
    std::cout << "Gate is`n close!" << std::endl;
    return false;
}

int Gate::getOpening() const{
    std::cout << "Gate state: " << current_opening << "%" << std::endl;
    return current_opening;
}

bool Gate::isSpanValid(int percentage)
{
    return percentage >= 0 && percentage <= 100;
}

