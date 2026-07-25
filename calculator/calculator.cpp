#include "calculator.h"
#include <cmath>

void Calculator::Set(Number val) { 
    current_value_ = val; 
}

Number Calculator::GetNumber() const { 
    return current_value_; 
}

void Calculator::Add(Number val) { 
    current_value_ += val; 
}

void Calculator::Sub(Number val) { 
    current_value_ -= val; 
}

void Calculator::Mul(Number val) { 
    current_value_ *= val; 
}

void Calculator::Div(Number val) { 
    if (val != 0.0) {
        current_value_ /= val; 
    }
}

void Calculator::Pow(Number val) { 
    current_value_ = std::pow(current_value_, val); 
}