#include<iostream>

class HeartRates
{
    public:
        explicit HeartRates(std :: string first_name , std :: string last_name, int dob_day, int dob_month, int dob_year);
        void setFirstName(std :: string new_first_name);
        void setLastName(std :: string new_last_name);
        void setDateOfBirthDay(int new_dob_day);
        void setDateOfBirthMonth(int new_dob_month);
        void setDateOfBirthYear(int new_dob_year);
        void setAge();
        int getAge();
        int getMaximumHeartRate();
        int getMinTragetHeartRate();
        int getMaxTragetHeartRate();
        std :: string getFirstName() const;
        std :: string getLastName() const;
        int getDateOFBirth() const;
        int getDateOfBirthMonth() const;
        int getDateOfBirthYear() const;
    private:
        std :: string first_name , last_name;
        int dob_day, dob_month, dob_year, person_age;
};