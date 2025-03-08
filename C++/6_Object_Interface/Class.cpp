#include<iostream>
#include<iomanip>
#include"Class.h"

// Test class
Test :: Test(std :: string person_name, char person_gender, int person_age, float person_height) :
    name(person_name),
    gender(person_gender), 
    age(person_age), 
    height(person_height)
{

}
void Test :: SetInfo(std :: string person_name, char person_gender, int person_age, float person_height)
{
    if (person_name != " ")
    {
        name = person_name;
    }
    else if (person_gender != ' ')
    {
        gender = person_gender;
    }
    else if (person_age != -1)
    {
        age = person_age;
    }
    else if (person_height != -1)
    {
        height = person_height;
    }
}
int Test :: age_diffrence(int other_age) const
{
    if(age >= other_age)
    {
        return age - other_age;
    }
    return -1;
}
int Test :: height_diffrence(int other_height) const
{
    if(height>= other_height)
    {
        return height - other_height;
    }
    return -1;
}
void Test :: display_info()
{
    std :: cout << "\nName: " << name
                << "\nGender: " << gender
                << "\nAge: " << age
                << "\nHeight: " << height;
}

// Subject Class
Subject :: Subject(std :: string subject_name, int subject_level)
    {
        SetName(subject_name);
        SetLevel(subject_level);
    }

std :: string Subject :: GetName () const
{
    return name;
}

void Subject :: SetName (std :: string new_name)
{
    if(new_name.size() <= 15)
    {
        name = new_name;
    }
    else
    {
        name = new_name.substr(0, 15);
        std :: cerr << "\nName: \"" << new_name << "\" is longer than 15 characters.\nHave been limited to 15 character as \"" << name << "\"\n";
    }
}

int Subject :: GetLevel () const
{
    return level;
}

void Subject :: SetLevel (int new_level)
{
    if(new_level >= 1 && new_level <= 12)
    {
        level = new_level;
    }
    else
    {
        level = 1;
        std :: cerr << "\nLevel: \"" << new_level << "\" is less than 1 or greater than 12.\nHave been set to \"1\"\n"; 
    }
}

void Subject :: DisplayInfo() const
{
    std :: cout << "\nSubject"
                << "\nName: " << GetName()
                << "\nLevel: " << GetLevel(); 
}

// GradeBoook class

GradeBook :: GradeBook(std :: string name)
{
    SetCourseName(name);
}

void GradeBook :: SetCourseName (std :: string name)
{
    if(name.size() <= 25)
    {
        CourseName = name;
    }
    else
    {
        CourseName = name.substr(0, 25);
        std :: cerr << "\nName :\"" << name << "\" is longer than 25 characters.\nHave been limited to 25 characters as \"" << CourseName << "\".\n";  
    }
}

std :: string GradeBook :: GetCourseName() const
{
    return CourseName;
}

void GradeBook :: DisplayMessage() const
{
    std:: cout << "Grade Book Subject: " << GetCourseName() << std :: endl;
}

void GradeBook :: ClassAverage() const
{
    int total = 0;
    unsigned int counter = 0;
    int input;
    std :: cout << "\nEnter Marks/Quit(-1): ";
    std :: cin >> input;
    while(input != -1)
    {
        if(input >= 0 && input <= 100)
        {
            total += input;
            counter++;
        }
        else
        {
            std :: cerr << "\nValue: " << input << "outside limits 0 - 100.";
        }
        std :: cout << "Enter Marks/Quit(-1): ";
        std :: cin >> input;
    }
    if(counter != 0)
    {
        float average = static_cast<float>(total) / counter;
        std :: cout << "\nTotal(" << counter << "): " << std :: setprecision(2) << std :: fixed << total << "\nAverage: " << average; 
    }
    else
        std :: cerr << "\nCounter: " << counter << "\nZero Division Error";
}

//Account Class
Account :: Account(double value)
{
    setBalance(value);
}

void Account :: credit(double value)
{
    if(value >= 0)
    {
        balance += value;
    }
    else
    {
        std :: cerr << "Value: \"" << value << "\" Less than 0.\nUse debit for deductions.";
    }
}

void Account :: debit(double value)
{
    if(balance - value >= 0)
    {
        balance -= value;
    }
    else
    {
        std :: cerr << "Debit amount exceeded account balance.No changes made.";
    }
}

double Account :: getBalance() const
{
    return balance;
}

void Account :: setBalance(double value = 0)
{
    if(value >= 0)
    {
        balance = value;
    }
    else
    {   balance =  value;
        std :: cerr << "Intial Balance: \"" << value << "\"Less than 0.Balance Assigned 0";
    }
}

//Invoice Class
Invoice :: Invoice(std :: string part_number, std :: string part_description, unsigned int quantity, double price) :
    PartNumber(part_number), PartDescription(part_description)
{
    setQuantity(quantity);
    setPrice(price);
}

void Invoice :: setPartNumber(std :: string part_number)
{
    PartNumber = part_number;
}

void Invoice :: setPartDescription(std :: string part_description)
{
    PartDescription = part_description;
}

void Invoice :: setQuantity(int quantity)
{
    if(quantity >= 0)
    {
        Quantity = quantity;
    }
    else
    {
        Quantity = 0;
        std :: cerr << "\nQuantity: \"" << quantity << "\" less than 0. Default value 0 Assigned.\n";
    }
}

void Invoice :: setPrice(double price)
{
    if(price >= 0)
    {
        Price = price;
    }
    else
    {
        Price = 0;
        std :: cerr << "\nPrice: \"" << price << "\" less than 0. Default value 0 Assigned.\n";
    }
}

std :: string Invoice :: getPartNumber() const
{
    return PartNumber;
}

std :: string Invoice :: getPartDescription() const
{
    return PartDescription;
}

int Invoice :: getQuantity() const
{
    return Quantity;
}

double Invoice :: getPrice() const
{
    return Price;
}

double Invoice :: getInvoiceAmount() const
{
    return getQuantity() * getPrice();
}

// Employee Class
Employee :: Employee(std :: string firstname, std :: string lastname, double monthlysalary) :
    first_name(firstname),
    last_name(lastname)
{
    setMonthlySalary(monthlysalary);
}

void Employee :: setFirstName(std :: string new_first_name)
{
    first_name = new_first_name;
}

void Employee :: setLastName(std :: string new_last_name)
{
    last_name = new_last_name;
}

void Employee :: setMonthlySalary(double new_monthly_salary)
{
    if(new_monthly_salary >= 0)
    {
        monthly_salary = new_monthly_salary;
    }
    else
    {
        monthly_salary = 0;
        std :: cerr << "\nMonthly Salary: \"" << new_monthly_salary << "\" less thn zero. Assigned 0.\n";
    }
}

std :: string Employee :: getFirstName() const
{
    return first_name;
}

std :: string Employee :: Employee :: getLastName() const
{
    return last_name;
}

double Employee :: getMonthlySalary() const
{
    return monthly_salary;
}

void Employee :: raiseSalary(double percent)
{
    if(percent >= 0)
    {
        monthly_salary = monthly_salary * (1 + percent / 100);
    }
    else
    {
       std :: cerr << "\nPercentage: \"" << percent << "\" is negative no operation performed.\n";
    }
}

// Date Class

Date :: Date(int date_c, int month_c, int year_c)
{
    setDate(date_c);
    setMonth(month_c);
    setYear(year_c);
}

void Date :: setDate(int new_date)
{
    if(new_date > 0 && new_date < 32)
    {
        date = new_date;
    }
    else
    {
        std :: cerr << "\nDate: \"" << new_date << "\" less than 1 or greater than 31.\n";
    }
}

void Date :: setMonth(int new_month)
{
    if(new_month > 0 && new_month < 13)
    {
        month = new_month;
    }
    else
    {
        std :: cerr << "\nMonth: \"" << new_month << "\" less than 1 or greater than 12.\n";
    }
}

void Date :: setYear(int new_year)
{
    if(new_year > 0)
    {
        year = new_year;
    }
    else
    {
        std :: cerr << "\nYear: \"" << new_year << "\" less than 1.\n";
    }
}

int Date :: getDate() const
{
    return date;
}

int Date :: getMonth() const
{
    return month;
}

int Date :: getYear() const
{
    return year;
}

void Date :: display() const
{
    std :: cout << std :: setw(2) << std :: setfill('0') << "\nDate: " << getDate() << " Month: " << getMonth() << " Year: " << getYear() << std :: endl;
}