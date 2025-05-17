#ifndef INTEGER_H
#define INTEGER_H

#include<iostream>
#include<string>
#include<cmath>
#include<array>

class Integer
{
    public:
        static const size_t SIZE = 56;
        static const int MAX_DIGITS = 18;

        Integer();
        Integer(int);
        Integer(long long int);
        Integer(std :: string);
        ~Integer();

        Integer &setInteger(const std :: string &);
        std :: string getInteger();
        bool isEqualTo(const Integer &);
        bool isGreaterThan(const Integer &);
        bool isLessThan(const Integer &);
        bool isNotEqualTo(const Integer &);
        bool isGreaterThanOrEqualTo(const Integer &);
        bool isLessThanOrEqualTo(const Integer &);
        Integer &addition(const Integer &);
        Integer &subtraction(const Integer &);
        Integer &multiplication(const Integer &);
        Integer &division(const Integer &);
        Integer &modulus(const Integer &);

    private:
        enum class Signs {
            POSITIVE = 1,
            ZERO = 0,
            NEGATIVE = -1
        };

        std :: array<long long int, SIZE> number = {};
        Signs sign = Signs :: ZERO;

        static const long long int const_remainder_base;
        static const long long int const_division_base;
        std :: array<long long int, SIZE> one;
        std :: array<long long int, SIZE> zero;

        bool isStringZero(const std :: string &) const;
        int countDigits() const;
        long long int addNumbers(const long long int &, const long long int &, int&);
        std :: array<int, 2> getBorrowDigitIndex(const std :: array<long long int, SIZE> &, const std :: array<int, 2> &);
        void BorrowDigit(std :: array<long long int, SIZE> &, const std :: array<int, 2> &);
        int getLeadingCell() const;
        int getLeadingCell(const std :: array<long long int, SIZE> &) const;
        int countDigits(long long int) const;
        std :: array<long long int, SIZE> multiply(const std :: array<long long int, SIZE> &, const long long int &);
        void shiftIndex(std :: array<long long int, SIZE> &, const std :: array<int, 2> &);
        std :: array<long long int, SIZE> divideAndModulus(std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        std :: array<long long int, SIZE> additionUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        std :: array<long long int, SIZE> subtractionUtility(std :: array<long long int, SIZE>, const std :: array<long long int, SIZE> &);
        std :: array<long long int, SIZE> multiplicationUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        std :: array<long long int, SIZE> divisionUtility(std :: array<long long int, SIZE>, const std :: array<long long int, SIZE> &);
        std :: array<long long int, SIZE> modulusUtility(std :: array<long long int, SIZE>, const std :: array<long long int, SIZE> &);
        bool isEqualToUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        bool isGreaterThanUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        bool isLessThanUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        bool isNotEqualToUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        bool isGreaterThanOrEqualToUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
        bool isLessThanOrEqualToUtility(const std :: array<long long int, SIZE> &, const std :: array<long long int, SIZE> &);
};
#endif