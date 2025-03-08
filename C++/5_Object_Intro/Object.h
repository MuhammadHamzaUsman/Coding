#include<iostream>

class Name 
{
    public :
        explicit Name(std :: string firstname, std :: string lastname) : FirstName(firstname), LastName(lastname) 
        {

        }
        std :: string full_name(std :: string middle_name = " ")
        {
            if(middle_name == " ") 
            {
                return FirstName + middle_name + LastName;
            }
            else
            {
                return FirstName + " " + middle_name + " " + LastName;
            }
        }
    private :
        std :: string FirstName, LastName;
};