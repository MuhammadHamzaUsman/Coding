#include<iostream>
#include"HealthProfile.h"
using namespace std;

int main()
{
    HealthProfile profile("FName", "LName", 'M', 1.5, 60, 4, 2, 2004);
    cout << "Name: " << profile.getFirstName() << " " << profile.getLastName()
        << "\nDate of Birth: " << profile.getDateOFBirth() << ", " << profile.getDateOfBirthMonth() << ", " << profile.getDateOfBirthYear()
        << "\nAge: " << profile.getAge() 
        << "\nGender: " << profile.getGender() 
        << "\nHeight: " << profile.getHeightMeter()
        << "\nWeight: " << profile.getWeightKilogram()
        << "\nMax: " << profile.getMaximumHeartRate()
        << "\nTarget: " << profile.getMinTragetHeartRate() << "-" << profile.getMaxTragetHeartRate()
        << "\nBMI: " << profile.getBMI()
        << "\nBMI Chart"; 
        profile.getBMIChart();
    return 0;
}