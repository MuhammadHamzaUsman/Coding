#include<iostream>
#include"Class.h"
using namespace std;

int main()
{
    Employee emp1("Ali", "Nadeem", 100000);
    cout << "\nFirst Name: " << emp1.getFirstName() << "\nLast Name: " << emp1.getLastName() << "\nMonthly Salary: " << emp1.getMonthlySalary();
    emp1.setFirstName("Huzaifa");
    emp1.setLastName("Arshad");
    emp1.setMonthlySalary(-150000);
    cout << "\nFirst Name: " << emp1.getFirstName() << "\nLast Name: " << emp1.getLastName() << "\nMonthly Salary: " << emp1.getMonthlySalary();
    emp1.setMonthlySalary(150000);
    cout << "Monthly Salary: " << emp1.getMonthlySalary();
    emp1.raiseSalary(10);
    cout << "\nMonthly Salary: " << emp1.getMonthlySalary();
    return 0;
}