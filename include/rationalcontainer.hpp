#include <math.h>

#pragma once

namespace nvec {
class RationalContainer {
   public:
    RationalContainer() { containment = 0; };
    RationalContainer(double source) { containment = source; };
    ~RationalContainer(){};
    double get_value() const { return containment; };
    RationalContainer get_root() { return std::sqrt(containment); };
    bool operator==(RationalContainer const& second) const {
        return abs(containment - second.get_value()) < 0.00000001;
    };
    bool operator!=(RationalContainer const& second) const {
        return abs(containment - second.get_value()) > 0.00000001;
    };
    RationalContainer& operator+=(RationalContainer const& second) {
        containment += second.get_value();
        return *this;
    };
    RationalContainer& operator-=(RationalContainer const& second) {
        containment -= second.get_value();
        return *this;
    };
    RationalContainer& operator/=(RationalContainer const& second) {
        containment /= second.get_value();
        return *this;
    };
    RationalContainer& operator*=(RationalContainer const& second) {
        containment *= second.get_value();
        return *this;
    };
    RationalContainer operator+(RationalContainer const second) const {
        RationalContainer temp(*this);
        temp += second;
        return temp;
    };
    RationalContainer operator-(RationalContainer const second) const {
        RationalContainer temp(*this);
        temp -= second;
        return temp;
    };
    RationalContainer operator/(RationalContainer const second) const {
        RationalContainer temp(*this);
        temp /= second;
        return temp;
    };
    RationalContainer operator*(RationalContainer const second) const {
        RationalContainer temp(*this);
        temp *= second;
        return temp;
    };
    RationalContainer operator-() const {
        RationalContainer temp(-containment);
        return temp;
    }

   private:
    double containment;
};
}  // namespace nvec
