#include<iostream>

class HealthProfile
{
    public:
        explicit HealthProfile(std :: string first_name , std :: string last_name, char gender, double height, double weight, int dob_day, int dob_month, int dob_year);
        void setFirstName(std :: string new_first_name);
        void setLastName(std :: string new_last_name);
        void setDateOfBirthDay(int new_dob_day);
        void setDateOfBirthMonth(int new_dob_month);
        void setDateOfBirthYear(int new_dob_year);
        void setAge();
        void setGender(char new_gender);
        void setHeightMeter(double new_height);
        void setWeightKilogram(double new_weight);
        void getBMIChart() const;
        int getAge() const;
        int getMaximumHeartRate() const;
        int getMinTragetHeartRate() const;
        int getMaxTragetHeartRate() const;
        int getDateOFBirth() const;
        int getDateOfBirthMonth() const;
        int getDateOfBirthYear() const;
        double getHeightMeter() const;
        double getWeightKilogram() const;
        std :: string getFirstName() const;
        std :: string getLastName() const;
        char getGender() const;
        double getBMI() const;
    private:
        std :: string first_name , last_name;
        char gender;
        int dob_day, dob_month, dob_year, person_age;
        double height, weight;
};