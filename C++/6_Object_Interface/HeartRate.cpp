#include<iostream>
#include"HeartRate.h"
using namespace std;

int calculate_days(int day, int month, int year, int reference_year)
{
    //intializing refernce date and month always to 1 Jan
    int refernence_date = 1;
    int refernence_month = 1;
    //array that hold days in months of non-leap year
    int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

    //calculating days from refrence year to start of desired year not taking into account leap year
    int years_into_days = (year - reference_year) * 365;

    //calculating leap years between refrence year and desired year excluding desired year
    int leap_years = 0;
    for (int i = reference_year; i < year; i++)
    {
        if ((i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)))
        {
            leap_years++;
        }
    }
    
    // if desired year is leap year then change feb to 29 
    if ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
    {
        days_in_months[1] = 29;
    }
    int month_into_days = 0;
    // calculating days from start of refrence year to desired month excluding desired month
    // because rest of desired year was excluded in previous calcultion
    for (int i = 0; i < month - 1; i++)
    {
        month_into_days += days_in_months[i];
    }

    // Calculate the total number of days by summing:
    // - Total days from full years (excluding the desired year)
    // - Number of leap years (because they have an extra day)
    // - Days from completed months in the desired year
    // - Days from the current month (adding the days of the current month up to the given day)
    // Subtract 1 to exclude the end date from the calculation (since we're calculating the number of days up to the start of the given day)
    int days = years_into_days + leap_years + month_into_days + day - 1;
    return days;
}

int date_diffrence(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
    // days_from_start and days_from_end both calculate days from start of start_year to mentioned date
    // thier absolute diffrence is taken to find number of days between them
    int days_from_start = calculate_days(start_day, start_month, start_year, start_year);
    int days_from_end = calculate_days(end_day, end_month, end_year, start_year);
    int diffrence = abs(days_from_end - days_from_start);
    return diffrence;
}

bool ValidateDay(int day, int month, int year)
{
    // intializing array containing days in every month of common year
    int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // if Birth is in leap year set Feb to 29
    if (year % 4 == 0)
    {
        days_in_months[1] = 29;
    }
    // Validate it is greater than 0  and less than days in that month
    if ((day > 0) && (day <= days_in_months[month - 1]))
    {
        return true;
    }
    else
    {
        cerr << "\nDate: \"" << day << "\" is not in range of month(" << month << ") " << 0 << "-" << days_in_months[month - 1] << ".\n";
        return false;    
    }
}

HeartRates :: HeartRates(string First_Name , string Last_Name, int DOB_day, int DOB_month, int DOB_year) :
    first_name(First_Name),
    last_name(Last_Name)
    {
        setDateOfBirthYear(DOB_year);
        setDateOfBirthMonth(DOB_month);
        setDateOfBirthDay(DOB_day);
        setAge();
    }

void HeartRates :: setFirstName(string new_first_name)
{
    first_name = new_first_name;
}

void HeartRates :: setLastName(string new_last_name)
{
    last_name = new_last_name;
}

void HeartRates :: setDateOfBirthDay(int new_dob_day)
{
    if (ValidateDay(new_dob_day, getDateOFBirth(), getDateOfBirthYear()))
    {
        dob_day = new_dob_day;
    }
}

void HeartRates :: setDateOfBirthMonth(int new_dob_month)
{
    if(new_dob_month > 0 && new_dob_month < 13)
    {
        dob_month = new_dob_month;
    }
    else
    {
        cerr << "\nMonth: \"" << new_dob_month << "\" is not in range 1-12.\n";
    }
}

void HeartRates :: setDateOfBirthYear(int new_dob_year)
{
    if(new_dob_year >= 0)
    {
        dob_year = new_dob_year;
    }
    else
    {
        cerr << "\nYear: \"" << new_dob_year << "\" is less than 0.\n";
    }
}

void HeartRates :: setAge()
{
    int date, month, year;
    cout << "\nTodays Date";
    // Validate that year entered is or after Date of Birth
    while(true)
    {
        cout << "\nEnter Year: ";
        cin >> year;
        if(year >= getDateOfBirthYear())
        {
            break;
        }
    }
     // Validate that month entered is or after Date of Birth
    while(true)
    {
        cout << "Enter Month: ";
        cin >> month;
        // Validate that month in range 1-12 and if year entered is birthday year then month entered is or after birthday month
        if(year == getDateOfBirthYear() && month >= getDateOfBirthMonth())
        {
            break;
        }
        else if((month > 0  && month < 13))
        {
            break;
        }
    }
     // Validate that day entered is or after Date of Birth 
    while(true)
    {
        cout << "Enter Day: ";
        cin >> date;
        // Validates
        // if year and month are birthday year and month then day entered is or after birthday day
        // if year is birthday year then month entered is or after birthday month then day entered is or after birthday day
        // is a Valid Date
        if(ValidateDay(date, month, year) && year == getDateOfBirthYear() && month == getDateOfBirthMonth() && date >= getDateOFBirth())
        {
            break;
        }
        else if (ValidateDay(date, month, year) && year == getDateOfBirthYear() && month >= getDateOfBirthMonth() && date >= getDateOFBirth())
        {
            break;
        }
        else if(ValidateDay(date, month, year))
        {
            break;
        }
    }
    person_age = date_diffrence(dob_day, dob_month, dob_year, date, month, year) / 365;
}

string HeartRates :: getFirstName() const
{
    return first_name;
}

string HeartRates :: getLastName() const
{
    return last_name;
}

int HeartRates :: getDateOFBirth() const
{
    return dob_day;
}

int HeartRates :: getDateOfBirthMonth() const
{
    return dob_month;
}

int HeartRates :: getDateOfBirthYear() const
{
    return dob_year;   
}

int HeartRates :: getAge()
{
    return person_age;
}

int HeartRates :: getMaximumHeartRate()
{
    // calculates maximum heart rate according to rough formula 220 - person age
    return 220 - getAge();
}

int HeartRates :: getMinTragetHeartRate()
{
    // calculates target heart rate as 50%-85% ot maximum
    return getMaximumHeartRate() * 0.5;
}

int HeartRates :: getMaxTragetHeartRate()
{
    // calculates target heart rate as 50%-85% ot maximum
    return getMaximumHeartRate() * 0.85;
}