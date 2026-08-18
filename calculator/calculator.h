#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include "pow.h"
#include "rational.h"

using Error = std::string;

template <class Number>
class Calculator {
public:
    Calculator() : current_number_(Number{}), mem_(std::nullopt) {}

    void Set(Number number) {
        current_number_ = number;
    }

    Number GetNumber() const {
        return current_number_;
    }

    void Save() {
        mem_ = current_number_;
    }

    void Load() {
        if (mem_.has_value()) {
            current_number_ = *mem_;
        }
    }

    void ClearMem() {
        mem_ = std::nullopt;
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

    std::optional<Error> Add(Number x) {
        current_number_ = current_number_ + x;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number x) {
        current_number_ = current_number_ - x;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number x) {
        current_number_ = current_number_ * x;
        return std::nullopt;
    }

    std::optional<Error> Div(Number x) {
        if constexpr (std::is_same_v<Number, Rational>) {
            if (x.GetNumerator() == 0) {
                return "Division by zero";
            }
        } else if constexpr (std::is_integral_v<Number>) {
            if (x == 0) {
                return "Division by zero";
            }
        }
        current_number_ = current_number_ / x;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number x) {
        if constexpr (std::is_same_v<Number, Rational>) {
            if (current_number_.GetNumerator() == 0 && x.GetNumerator() == 0) {
                return "Zero power to zero";
            }
            if (x.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
        } else if constexpr (std::is_integral_v<Number>) {
            if (current_number_ == 0 && x == 0) {
                return "Zero power to zero";
            }
            if (static_cast<long long>(x) < 0) {
                return "Integer negative power";
            }
        } else if constexpr (std::is_floating_point_v<Number>) {
            if (current_number_ == 0 && x == 0) {
                return "Zero power to zero";
            }
        }

        current_number_ = ::Pow(current_number_, x);
        return std::nullopt;
    }

private:
    Number current_number_;
    std::optional<Number> mem_;
};
