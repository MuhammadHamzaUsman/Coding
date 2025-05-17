#include"Integer.h"
#include<iostream>
#include<string>
#include<cmath>
#include<array>
using namespace std;

const long long int Integer :: const_remainder_base = pow(10, MAX_DIGITS);
const long long int Integer :: const_division_base = pow(10, MAX_DIGITS - 1);

Integer :: Integer() :
    number({0}),
    sign(Signs :: ZERO),
    one({0}),
    zero({0})
{
    one[SIZE - 1] = 1;
}

Integer :: Integer(int input_number) :
    number({0}),
    sign(Signs :: ZERO),
    one({0}),
    zero({0})
{
    one[SIZE - 1] = 1;

    if(input_number < 0)
        sign = Signs :: NEGATIVE;
    else if(input_number > 0)
        sign = Signs :: POSITIVE;
    
    number[SIZE - 1] = abs(input_number);
}

Integer :: Integer(long long int input_number) :
    number({0}),
    sign(Signs :: ZERO),
    one({0}),
    zero({0})
{
    one[SIZE - 1] = 1;

    if(input_number < 0)
        sign = Signs :: NEGATIVE;
    else if(input_number > 0)
        sign = Signs :: POSITIVE;

    input_number = abs(input_number);
    number[SIZE - 1] = input_number % const_remainder_base;
    number[SIZE - 2] = input_number / const_remainder_base;
}

Integer :: Integer(std :: string input_number) :
    number({0}),
    sign(Signs :: ZERO),
    one({0}),
    zero({0})
{
    one[SIZE - 1] = 1;
    setInteger(input_number);
}

Integer :: ~Integer()
{

}

Integer &Integer :: setInteger(const string &input_number)
{
    int string_size = input_number.size();
    const char *digit = &input_number[0];
    if(input_number[0] == '-')
    {
        sign = Signs :: NEGATIVE;
        string_size--;
        digit++;
    }
    else if(!isStringZero(input_number))
        sign = Signs :: POSITIVE;

    for(int i = 0; i < string_size; i++)
    {
        if(*digit < '0' || *digit > '9')
            throw invalid_argument("String must only have digits or sign at first index.");
        digit++;
    }

    int leading_cell = SIZE - ceil(static_cast<double>(string_size) / MAX_DIGITS);

    int sub_string_end = string_size - 1;
    int sub_string_start = sub_string_end - 17;
    if(sub_string_start < 0)
        sub_string_start = 0;

    array<long long int, SIZE> number = {};
    long long int multiplication_base = 1;
    long long int number_part = 0;
    digit--;

    for(int j = SIZE - 1; j >= leading_cell; j--)
    {
        for(int i = sub_string_end; i >= sub_string_start; i--)
        {
            number_part += (*digit-- - '0') * multiplication_base;
            multiplication_base *= 10;
        }

        number[j] = number_part;
        number_part = 0;
        multiplication_base = 1;

        sub_string_end -= 18;
        sub_string_start = sub_string_end - 17;
        if(sub_string_start < 0)
            sub_string_start = 0;
    }

    Integer :: number = number;
    return *this;
}

std :: string Integer :: getInteger()
{
    string output = "";
    string temp = "";
    int temp_size = 0;
    int leading_cell = getLeadingCell();

    for(int i = Integer :: SIZE - 1; i >= leading_cell; i--)
    {
        temp = to_string(Integer :: number[i]);
        temp_size = temp.size();

        if(temp_size != Integer :: MAX_DIGITS& i != leading_cell)
            for(int i = Integer :: MAX_DIGITS - temp_size; i > 0; i--)
                temp = "0" + temp;
        
        output = temp + output;
        temp = "";
    }

    output = (sign == Signs :: NEGATIVE ? "-" : "") + output;
    return output;
}

bool Integer :: isEqualTo(const Integer &number_2)
{
    if(sign == number_2.sign)
        return isEqualToUtility(number, number_2.number);
    
    return false;
}

bool Integer :: isGreaterThan(const Integer &number_2)
{
    if(sign == Signs :: POSITIVE)
    {
        if(sign == Signs :: POSITIVE && (number_2.sign == Signs :: ZERO || number_2.sign == Signs :: NEGATIVE))
            return true;
        else if(sign == Signs :: POSITIVE && number_2.sign == Signs :: POSITIVE)
            return isGreaterThanUtility(number, number_2.number);
    }
    else if(sign == Signs :: NEGATIVE)
    {
        if(sign == Signs :: NEGATIVE && (number_2.sign == Signs :: ZERO || number_2.sign == Signs :: POSITIVE))
            return false;
        else if(sign == Signs :: NEGATIVE && number_2.sign == Signs :: NEGATIVE)
            return isLessThanUtility(number, number_2.number);
    }
    else
    {
        if((sign == Signs :: ZERO ) && number_2.sign == Signs :: ZERO)
            return false;
        else if(sign == Signs :: ZERO && number_2.sign == Signs :: POSITIVE)
            return false;
        else if(sign == Signs :: ZERO && number_2.sign == Signs :: NEGATIVE)
            return true;
    }

    return false;
}

bool Integer :: isLessThan(const Integer &number_2)
{
    if(sign == Signs :: POSITIVE)
    {
        if(sign == Signs :: POSITIVE && (number_2.sign == Signs :: ZERO || number_2.sign == Signs :: NEGATIVE))
            return false;
        else if(sign == Signs :: POSITIVE && number_2.sign == Signs :: POSITIVE)
            return isLessThanUtility(number, number_2.number);
    }
    else if(sign == Signs :: NEGATIVE)
    {
        if(sign == Signs :: NEGATIVE && (number_2.sign == Signs :: ZERO || number_2.sign == Signs :: POSITIVE))
            return true;
        else if(sign == Signs :: NEGATIVE && number_2.sign == Signs :: NEGATIVE)
            return isGreaterThanUtility(number, number_2.number);
    }
    else
    {
        if((sign == Signs :: ZERO ) && number_2.sign == Signs :: ZERO)
            return false;
        else if(sign == Signs :: ZERO && number_2.sign == Signs :: POSITIVE)
            return true;
        else if(sign == Signs :: ZERO && number_2.sign == Signs :: NEGATIVE)
            return false;
    }

    return false;
}

bool Integer :: isNotEqualTo(const Integer &number_2)
{
    return !isEqualTo(number_2);
}

bool Integer :: isGreaterThanOrEqualTo(const Integer &number_2)
{
    return isGreaterThan(number_2) || isEqualTo(number_2);
}

bool Integer :: isLessThanOrEqualTo(const Integer &number_2)
{
    return isLessThan(number_2) || isEqualTo(number_2);
}

Integer &Integer :: addition(const Integer &number_2)
{
    if(sign == number_2.sign)
    {
        number = additionUtility(number, number_2.number);
    }
    else if(sign == Signs :: ZERO)
    {
        number = additionUtility(number, number_2.number);
        sign = number_2.sign;
    }
    else
    {
        if(number == number_2.number)
        {
            number = {0};
            sign = Signs :: ZERO;
        }
        else if(isGreaterThanUtility(number, number_2.number))
            number = subtractionUtility(number, number_2.number);
        else
        {
            number = subtractionUtility(number_2.number, number);
            sign = number_2.sign;
        }
    }

    return *this;
}

Integer &Integer :: subtraction(const Integer &number_2)
{
    Signs number_2_sign = number_2.sign;
    if(number_2_sign == Signs :: POSITIVE)
        number_2_sign = Signs :: NEGATIVE;
    else if(number_2_sign == Signs :: NEGATIVE)
            number_2_sign = Signs :: POSITIVE;

    if(sign == number_2_sign)
        number = additionUtility(number, number_2.number);
    else if(sign == Signs :: ZERO)
    {
        number = additionUtility(number, number_2.number);
        sign = number_2_sign;
    }
    else
    {
        if(number == number_2.number)
        {
            number = {0};
            sign = Signs :: ZERO;
        }
        else if(isGreaterThanOrEqualToUtility(number, number_2.number))
            number = subtractionUtility(number, number_2.number);
        else
        {
            number = subtractionUtility(number_2.number, number);
            sign = number_2_sign;
        }
    }

    return *this;
}

Integer &Integer :: multiplication(const Integer &number_2)
{
    if(sign == Signs :: ZERO || number_2.sign == Signs :: ZERO)
    {
        number = {0};
        sign = Signs :: ZERO;
    }
    else
    {
        number = multiplicationUtility(number, number_2.number);
        if(sign != number_2.sign)
            sign = Signs :: NEGATIVE;
        else 
            sign = Signs :: POSITIVE;
    }

    return *this;
}

Integer &Integer :: division(const Integer &number_2)
{
    if(number_2.sign == Signs :: ZERO)
        throw invalid_argument("Zero Division Error.");
    else if(sign == Signs :: ZERO)
    {
        number = {0};
    }
    else
    {
        number = divisionUtility(number, number_2.number);
        if(sign != number_2.sign)
            sign = Signs :: NEGATIVE;
        else 
            sign = Signs :: POSITIVE;
    }


    if(number == zero)
        sign = Signs :: ZERO;

    return *this;
}

Integer &Integer :: modulus(const Integer &number_2)
{
    if(number_2.sign == Signs :: ZERO)
        throw invalid_argument("Zero Division Error.");
    else
        number = modulusUtility(number, number_2.number);

    if(isEqualToUtility(number, {0}))
        sign = Signs  :: POSITIVE;

    return *this;
}

bool Integer :: isStringZero(const std :: string &input_string) const
{
    for(char digit : input_string)
        if(digit != '0')
            return false;
    
    return true;
}

std :: array<long long int, Integer :: SIZE> Integer :: additionUtility(const array<long long int, SIZE> &number_1, const array<long long int, SIZE> &number_2)
{
    array<long long int, SIZE> sum = {};
    int Carry = 0;
    int leading_cell_1 = getLeadingCell(number_1);
    int leading_cell_2 = getLeadingCell(number_2);
    int leading_cell = leading_cell_1 < leading_cell_2 ? leading_cell_1 : leading_cell_2;
    
    for(int i = SIZE - 1; i >= leading_cell; i--)
    {
        sum[i] = addNumbers(number_1[i], number_2[i], Carry);
        if(i == leading_cell && Carry != 0)
            if(leading_cell - 1 >= 0)
                leading_cell--;
    }

    return sum;
}

std :: array<long long int, Integer :: SIZE> Integer :: subtractionUtility(array<long long int, SIZE> number_1, const array<long long int, SIZE> &number_2)
{
    array<long long int, SIZE> diffrence = {0};

    int leading_cell_occupied = getLeadingCell(number_1);
    int no_digits = countDigits(number_1[SIZE - 1]);
    array<int, 2> current_digit_index = {SIZE - 1, 1};
    int digit = 0;

    int digit_1 = 0;
    int digit_2 = 0;
    long long int number_part_1 = number_1[0];
    long long int number_part_2 = number_2[0];
    long long int diffrence_number_part = 0;

    long long int remainder_base = 10;
    long long int division_base = 1;

    for(int i = SIZE - 1; i >= leading_cell_occupied; i--)
    {
        number_part_1 = number_1[i];
        number_part_2 = number_2[i];

        for(int j = 1; j <= MAX_DIGITS; j++)
        {
            digit_1 = number_part_1 % remainder_base / division_base;
            digit_2 = number_part_2 % remainder_base / division_base;

            if(digit_1 < digit_2)
            {
                digit_1 += 10;
                BorrowDigit(number_1, {i, j});
                number_part_1 = number_1[i];
            }

            digit = digit_1 - digit_2;
            diffrence_number_part += digit * division_base;
            division_base *= 10;
            remainder_base *= 10;
        }

        diffrence[i] = diffrence_number_part % const_remainder_base;
        diffrence_number_part = 0;
        no_digits = MAX_DIGITS;
        division_base = 1;
        remainder_base = 10;
    }

    return diffrence;
}

std :: array<long long int, Integer :: SIZE> Integer :: multiplicationUtility(const array<long long int, SIZE> &number_1, const array<long long int, SIZE> &number_2)
{
    array<long long int, SIZE> product = {};
    array<long long int, SIZE> temp = {};
    array<long long int, SIZE> multiplication_base = {};
    multiplication_base[39] = 1;
    int leading_cell = getLeadingCell(number_2);
    long long int number_part = 0;
    int no_digits = 0;
    int digit = 0;
    int remiander_base = 10;
    int division_base = 1;
    array<int, 2> shift_index = {0, 0};

    for(int i = SIZE - 1; i >= leading_cell; i--)
    {
        number_part = number_2[i];
        no_digits = countDigits(number_part);

        for(int j = 0; j < no_digits; j++)
        {
            digit = number_part % remiander_base / division_base;
            temp = multiply(number_1, digit);
            shiftIndex(temp, shift_index);
            product = additionUtility(product, temp);
            remiander_base *= 10;
            division_base *= 10;
            shift_index[1]++;
        }

        shift_index[0]++;
        shift_index[1] = 0;

        remiander_base = 10;
        division_base = 1;
    }

    return product;
}

std :: array<long long int, Integer :: SIZE> Integer :: divisionUtility(array<long long int, SIZE> number_1, const array<long long int, SIZE> &number_2)
{

    auto res = divideAndModulus(number_1, number_2);
    return res;
}

std :: array<long long int, Integer :: SIZE> Integer :: modulusUtility(array<long long int, SIZE> number_1, const array<long long int, SIZE> &number_2)
{
    divideAndModulus(number_1, number_2);
    return number_1;
}

int Integer :: countDigits() const
{
    int leading_cell_occupied = getLeadingCell();
    int no_digits = (SIZE - 1 - leading_cell_occupied) * MAX_DIGITS;

    long long int number_part = Integer :: number[leading_cell_occupied];
    while(number_part >= 1)
    {
        no_digits++;
        number_part /= 10;
    }

    return no_digits;
}

long long int Integer :: addNumbers(const long long int &number_1, const long long int &number_2, int &Carry)
{
    long long int sum = 0;

    int no_digits_1 = countDigits(number_1);
    int no_digits_2 = countDigits(number_2);
    int number_of_digits = (no_digits_1 < no_digits_2 ? no_digits_2 : no_digits_1);

    int digit_1 = 0;
    int digit_2 = 0;
    int result = 0;
    int result_digit = 0;

    long long int base = 10;
    long long int lesser_base = 1;

    for(int i = 0; i < number_of_digits; i++)
    {
        digit_1 = (number_1 % base) / lesser_base;
        digit_2 = (number_2 % base) / lesser_base;
        result = digit_1 + digit_2 + Carry;
        Carry = result / 10;
        result_digit = result % 10;
        sum += result_digit * lesser_base;
        base *= 10;
        lesser_base *= 10;
    }

    if(log10(lesser_base) < 18)
    {
        sum += Carry * lesser_base;
        Carry = 0;
    }

    Carry = Carry;
    return sum;
}

array<int, 2> Integer :: getBorrowDigitIndex(const array<long long int, SIZE> &number, const array<int, 2> &index)
{
    int leading_cell_occupied = index[0];
    int current_digit_no = index[1] + 1;

    long long int remainder_base = pow(10, current_digit_no);
    long long int division_base = pow(10, current_digit_no - 1);
    long long int number_part = 0;

    int test_digit = 0;

    bool isValidBrrowDigit = false;

    for(int i = leading_cell_occupied; i >= 0; i--)
    {
        number_part = number[i];

        for(int j = current_digit_no; j <= MAX_DIGITS; j++)
        {
            test_digit = (number_part % remainder_base) / division_base;

            if(test_digit != 0)
                return {i, j};

            remainder_base *= 10;
            division_base *= 10;
        }

        current_digit_no = 1;
        remainder_base = 10;
        division_base = 1;
    }

    return index;
}

void Integer :: BorrowDigit(array<long long int, SIZE> &number, const array<int, 2> &current_digit_index)
{
    array<int, 2> borrow_digit_index = getBorrowDigitIndex(number, current_digit_index);

    int current_leading_cell = current_digit_index[0];
    int current_digit_no = current_digit_index[1]; 
    int borrow_leading_cell = borrow_digit_index[0];
    int borrow_digit_no = borrow_digit_index[1]; 

    long long int new_number_part = 0;

    int start_digit_no = borrow_digit_no;
    int ending_digit_no = 0;
    int extracted_digit = 0;

    long long int remainder_base = pow(10, borrow_digit_no);
    long long int division_base = pow(10, borrow_digit_no - 1);
    long long int temp_base = {};

    long long int number_part = 0;

    for(int i = borrow_leading_cell; i <= current_leading_cell; i++)
    {
        number_part = number[i];
                
        if(i == current_leading_cell)
        {
            ending_digit_no = current_digit_no;
            temp_base = pow(10, (current_leading_cell == borrow_leading_cell ? borrow_digit_no : 18));
            new_number_part = number_part / temp_base * temp_base;
        }

        for(int j = start_digit_no; j >= ending_digit_no; j--)
        {
            extracted_digit = number_part % remainder_base / division_base;

            if(extracted_digit == 0)
                extracted_digit = 10;

            extracted_digit--;
            new_number_part += extracted_digit * division_base;
            remainder_base /= 10;
            division_base /= 10;
        }

        number[i] = new_number_part;
        new_number_part = 0;

        remainder_base = const_remainder_base;
        division_base = const_division_base;
        start_digit_no = MAX_DIGITS;
    }

}

int Integer :: getLeadingCell() const
{
    int size = Integer :: number.size();
    for(int i = 0; i < size; i++)
    {
        if(Integer :: number[i] != 0)
            return i;
    }
    return SIZE - 1;
}

int Integer :: getLeadingCell(const std :: array<long long int, SIZE> &number) const
{
    int size = number.size();
    for(int i = 0; i < size; i++)
    {
        if(number[i] != 0)
            return i;
    }
    return SIZE - 1;   
}

int Integer :: countDigits(long long int number) const
{
    if(number == 0)
        return 18;

    int no_digits = 0;

    while(number >= 1)
    {
        no_digits++;
        number /= 10;
    }

    return no_digits;
}

std :: array<long long int, Integer :: SIZE> Integer :: multiply(const std :: array<long long int, SIZE> &number, const long long int &digit)
{
    array<long long int, SIZE> temp = {};

    long long int remainder_base = 10;
    long long int division_base = 1;

    int leading_cell = getLeadingCell();

    int test_digit = 0;
    int result = 0;
    int prod_digit = 0;

    int no_digits = 0;
    long long int number_part = 0;
    long long int new_number_part = 0;
    int Carry = 0;

    for(int i = SIZE - 1; i >= leading_cell; i--)
    {
        number_part = number[i];
        no_digits = countDigits(number_part);

        for(int i = 0; i < no_digits; i++)
        {
            test_digit = number_part % remainder_base / division_base;

            result = test_digit * digit;
            
            new_number_part += result * division_base;

            remainder_base *= 10;
            division_base *= 10;
        }

        if(new_number_part >= const_remainder_base && i == leading_cell)
        {
            temp[i] = (new_number_part) % division_base;
            if(--i >= 0)
                temp[i - 1] = new_number_part / division_base;
        }
        else
        {
            temp[i] = new_number_part;
        }

        new_number_part = 0;
        remainder_base = 10;
        division_base = 1;
    }

    return temp;
}

void Integer :: shiftIndex(std :: array<long long int, SIZE> &number, const array<int, 2> &shift_index)
{
    int end_limit = SIZE - shift_index[0] - 1;
    int shifted_cell = 0;

    if(shift_index[0] != 0)
    {
        for(int i = shift_index[0]; i <= end_limit; i++)
        {
            number[i] = number[i + 1];
        }

        for(int i = end_limit + 1; i < SIZE; i++)
        {
            number[i] = 0;
        }
    }

    long long int base = pow(10, shift_index[1]);
    long long int left_base = pow(10, MAX_DIGITS - shift_index[1]);
    long long int left_side = 0;

    for(int i = 0; i <= end_limit; i++)
    {
        left_side = number[i] % left_base;

        if(i == (SIZE - 1))
            number[i] = left_side * base;
        else
            number[i] = left_side * base + (number[i + 1] / left_base);
    }
}

array<long long int, Integer :: SIZE> Integer :: divideAndModulus(array<long long int, SIZE> &number_1, const array<long long int, SIZE> &number_2)
{
    array<long long int, SIZE> quotient = {};
    array<long long int, SIZE> temp = {};

    int leading_cell = getLeadingCell(number_1);
    int no_digits = countDigits(number_1[leading_cell]);

    int digit = 0;
    long long int number_part = 0;
    long long int remainder_base = pow(10, no_digits);
    long long int division_base = pow(10, no_digits - 1);
    const long long int const_remainder_base = pow(10, MAX_DIGITS);
    const long long int const_division_base = pow(10, MAX_DIGITS - 1);
    array<long long int, SIZE> multiple = {};
    array<long long int, SIZE> one = {};
    one[SIZE - 1] = 1;
    array<long long int, SIZE> multiplier = {};

    for(int i = leading_cell; i < SIZE; i++)
    {
        number_part = number_1[i];
        no_digits = countDigits(number_part);

        for(int j = no_digits; j > 0; j--)
        {
            digit = number_part % remainder_base / division_base;
            temp[SIZE - 1] += digit;

            if(isGreaterThanOrEqualToUtility(temp ,number_2))
            {
                multiple = {};
                multiple[SIZE - 1] = 1;
                multiplier = {};
                multiplier[SIZE - 1] = 1;

                while(isLessThanUtility(multiple, temp))
                {
                    multiple = multiplicationUtility(number_2, multiplier);
                    multiplier = additionUtility(multiplier, one);
                }
                multiplier[SIZE - 1] -= 2;


                multiple = multiplicationUtility(number_2, multiplier);
                temp = subtractionUtility(temp, multiple);
                quotient = additionUtility(quotient, multiplier);
                shiftIndex(multiple, {static_cast<int>(SIZE) - 1 - i, j - 1});
                number_1 = subtractionUtility(number_1, multiple);
            }

            shiftIndex(quotient, {0, 1});
            shiftIndex(temp, {0, 1});

            remainder_base /= 10;
            division_base /= 10;
        }

        remainder_base = const_remainder_base;
        division_base = const_division_base;
    }

    int quotient_leading_cell = getLeadingCell(quotient);
    long long int lower_base = 10;
    long long int higher_base = pow(10, MAX_DIGITS - 2);
    long long int left_side = 0;
    long long int right_side = 0;
    for(int i = SIZE - 1; i >= quotient_leading_cell; i--)
    {
        if(i == 0)
            left_side = 0;
        else
            left_side = quotient[i - 1] % lower_base;

        right_side = quotient[i] / lower_base;
        quotient[i] = left_side * higher_base + right_side;
    }

    return quotient;
}

bool Integer :: isEqualToUtility(const std :: array<long long int, SIZE> &number_1, const std :: array<long long int, SIZE> &number_2)
{
    int leading_cell_1 = getLeadingCell(number_1); 
    int leading_cell_2 = getLeadingCell(number_2);

    if(leading_cell_1 == leading_cell_2)
    {
        int larger_leading_cell = leading_cell_1 > leading_cell_2 ? leading_cell_1 : leading_cell_2;
        for(int i = larger_leading_cell; i < SIZE; i++)
            if(number_1[i] != number_2[i])
                return false;
    }
    else
        return false;

    return true;
}

bool Integer :: isGreaterThanUtility(const std :: array<long long int, SIZE> &number_1, const std :: array<long long int, SIZE> &number_2)
{
    int leading_cell_1 = getLeadingCell(number_1); 
    int leading_cell_2 = getLeadingCell(number_2);

    if(leading_cell_1 == leading_cell_2)
    {
        int larger_leading_cell = leading_cell_1 > leading_cell_2 ? leading_cell_1 : leading_cell_2;
        for(int i = larger_leading_cell; i < SIZE; i++)
            if(number_1[i] < number_2[i])
                return false;
    }
    else if(leading_cell_1 > leading_cell_2)
        return false;

    return true;
}

bool Integer :: isLessThanUtility(const std :: array<long long int, SIZE> &number_1, const std :: array<long long int, SIZE> &number_2)
{
    int leading_cell_1 = getLeadingCell(number_1); 
    int leading_cell_2 = getLeadingCell(number_2);

    if(leading_cell_1 == leading_cell_2)
    {
        int larger_leading_cell = leading_cell_1 > leading_cell_2 ? leading_cell_1 : leading_cell_2;
        for(int i = larger_leading_cell; i < SIZE; i++)
            if(number_1[i] > number_2[i])
                return false;
    }
    else if(leading_cell_1 < leading_cell_2)
        return false;

    return true;
}

bool Integer :: isNotEqualToUtility(const std :: array<long long int, SIZE> &number_1, const std :: array<long long int, SIZE> &number_2)
{
    return !isEqualToUtility(number_1, number_2);
}

bool Integer :: isGreaterThanOrEqualToUtility(const std :: array<long long int, SIZE> &number_1, const std :: array<long long int, SIZE> &number_2)
{
    return isGreaterThanUtility(number_1, number_2) || isEqualToUtility(number_1, number_2);
}

bool Integer :: isLessThanOrEqualToUtility(const std :: array<long long int, SIZE> &number_1, const std :: array<long long int, SIZE> &number_2)
{
    return isLessThanUtility(number_1, number_2) || isEqualToUtility(number_1, number_2);
}