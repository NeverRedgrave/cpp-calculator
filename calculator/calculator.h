#ifndef CALCULATOR_H_
#define CALCULATOR_H_

using Number = double;

class Calculator {
public:
    Calculator() = default;

    void Set(Number val);
    Number GetNumber() const;

    void Add(Number val);
    void Sub(Number val);
    void Mul(Number val);
    void Div(Number val);
    void Pow(Number val);

private:
    Number current_value_ = 0.0;
};

#endif