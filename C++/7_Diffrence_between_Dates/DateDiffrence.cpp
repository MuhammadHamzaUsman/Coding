#include<iostream>
#include<iomanip>
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

int main()
{
    cout << "Diff: " << date_diffrence(28,6,2000, 1,1,2020);
    return 0;
}
