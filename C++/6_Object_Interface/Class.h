#include <iostream>

class Test
{
    public :
        explicit Test(std :: string person_name = " ", char person_gender = ' ', int person_age= -1, float person_height = -1);
        void SetInfo(std :: string person_name = " ", char person_gender = ' ', int person_age= -1, float person_height = -1);
        int age_diffrence(int) const;
        int height_diffrence(int) const;
        void display_info();
    private :
        int age;
        float height;
        char gender;
        std :: string name;
};

class Subject
{
    public : 
        explicit Subject(std :: string subject_name, int subject_level);
        std :: string GetName() const;
        void SetName (std :: string new_name);
        int GetLevel() const;
        void SetLevel (int new_level);
        void DisplayInfo() const;
    private :
        std :: string name;
        int level;
};

class GradeBook
{
    public :
        explicit GradeBook(std :: string name);
        void SetCourseName(std :: string name);
        std :: string GetCourseName() const;
        void DisplayMessage() const;
        void ClassAverage() const;
    private :
        std :: string CourseName;
};

class Account
{
    public :
        explicit Account(double value);
        void credit(double value);
        void debit(double value);
        double getBalance() const;
    private :
        void setBalance(double value);
        double balance;
};

class Invoice
{
    public:
        explicit Invoice(std :: string part_number, std :: string part_description, unsigned int quantity, double price);
        void setPartNumber(std :: string part_number);
        void setPartDescription(std :: string part_description);
        void setQuantity(int quantity);
        void setPrice(double price);
        std :: string getPartNumber() const;
        std :: string getPartDescription() const;
        int getQuantity() const;
        double getPrice() const;
        double getInvoiceAmount() const;
    private :
        std :: string PartNumber;
        std :: string PartDescription;
        unsigned int Quantity;
        double Price;
};

class Employee
{
    public:
        explicit Employee(std :: string first_name, std :: string last_name, double monthly_salary);
        void setFirstName(std :: string new_first_name);
        void setLastName(std :: string new_last_name);
        void setMonthlySalary(double new_monthly_salary);
        void raiseSalary(double percent);
        std :: string getFirstName() const;
        std :: string getLastName() const;
        double getMonthlySalary() const;
    private:
        std :: string first_name, last_name;
        double monthly_salary;
};