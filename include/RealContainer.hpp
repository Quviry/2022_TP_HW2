#pragma once

namespace nvec {
class RationalContainer {
   public:
    RationalContainer();
    ~RationalContainer();
    double get_value();
    RationalContainer get_root();
    RationalContainer operator+();

   private:
    double containment;
};
}  // namespace nvec
