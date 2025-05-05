#include<iostream>
#include<iomanip>
#include<array>
#include<cmath>
using namespace std;

int getUserInstruction(int, const int, const int);
void executeInstruction(const int *, int *, int [], const size_t *, float *, const int, bool *, bool *);
void registerMemoryDump(float *, int *, const int *, int [], const size_t);
void readStringMem(string, int *, int [], const size_t);
void writeStringMem(int *, int [], const size_t);
int charsetConversion (int, bool);
void readFloatMem(float, int *, int [], const size_t, const int);
float getFloatMem(int *, int [], const size_t, const int);
void relativeBranchMem(int *, int *, const size_t, bool *);

int main()
{   
    // Largest and smallest value possible due to 4-digit limit
    const int MAX_LIMIT = 9999;
    const int MIN_LIMIT = -9999;

    // memory for storing instructions
    const size_t MEMORY_SIZE = 100; 
    int memory[MEMORY_SIZE] = {};
    // instruction_counter will store index to ensure that not more that 100 instruction are loaded
    int instruction_counter = 0;
    // current instruction will store instruction added by user
    int instruction_register = 0;

    cout << "*** Welcome to Simpletron! ***\n"
         << "*** Please enter your program one instruction ***\n"
         << "*** (or data word) at a time. I will type the ***\n"
         << "*** location number and a question mark (?). ***\n"
         << "*** You then type the word for that location. ***\n"
         << "*** Type the sentinel -99999 to stop entering ***\n"
         << "*** your program. ***\n"
         << "\n";

    while(instruction_counter < MEMORY_SIZE)
    {
        // get validated instruction
        instruction_register = getUserInstruction((instruction_counter), MIN_LIMIT, MAX_LIMIT);

        // if sentienel end loop
        if(instruction_register == -99999)
            break;
        
        // add to memory and increase instruction_counter
        memory[instruction_counter] = instruction_register;
        instruction_counter++;
    }

    cout << "\n"
         << "*** Program loading completed ***\n"
         << "*** Program execution begins ***\n"
         << "\n";
      
    // instruction_counter will store index to ensure that index does not go out of bounds
    instruction_counter = 0;
    // current instruction will that will be executed
    instruction_register = 0;
    // variable that determines wether current instruction was Halt or not
    bool isHalt = false;
    // accumalator intialized to 0
    // accumalator is float to accomodate floating type calculation
    float accumalator = 0;
    // wether debug mode is acctive
    bool isDebugActive = false;

    while(!isHalt && instruction_counter < MEMORY_SIZE)
    {
        instruction_register = memory[instruction_counter];
        instruction_counter++;
        executeInstruction(&instruction_register, &instruction_counter, memory, &MEMORY_SIZE, &accumalator, MAX_LIMIT, &isHalt, &isDebugActive);
    }

    registerMemoryDump(&accumalator, &instruction_counter, &instruction_register, memory, MEMORY_SIZE);
    
    return 0;
}

int getUserInstruction(int current_memory_index, const int MIN_LIMIT, const int MAX_LIMIT)
{
    // variable to store instruction
    int instruction = 0;

    do
    {
        // clears 20 columns and bring cursor back to start of column and then prints index
        cout << "                    \r" << setw(2) << current_memory_index << " ? ";
        cin >> instruction;
        // brings cursor up one line so if instruction is not valid same line is cleared and reused
        cout << "\x1b[A";

        // restores cin if it fails
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
        }

        // if sentienel value end loop
        if(instruction == -99999)
        {
            cout << "\n";
            break;
        }
    }while((instruction < MIN_LIMIT || instruction > MAX_LIMIT));

    // after loop ends bring cursor from current line to next line
    cout << endl;

    return instruction;
}

void executeInstruction(const int *instruction, int *instruction_address, int memory[], const size_t *MEMORY_SIZE, float *accumalator, const int MAX_LIMIT, bool *isHalt, bool *isDebugActive)
{
    // operation code of instruction and memory address of instruction
    int operation_code = *instruction / 100;
    int memory_address = *instruction % 100;
    // wether instruction is halt
    *isHalt = false;
    // Input/output operations
    const int read = 10; // Read a word(int) from the keyboard into a specific location in memory.
    const int write = 11; // Write a word(int) from a specific location in memory to the screen.
    const int writeNewLine = 12; // Write new line character to the screen.
    const int readString = 13; // Read a string from the keyboard into a specific location in memory according to method in Read string function.
    const int writeString = 14; // Write a string from the memory address to screen according to method in Write string function.
    const int readFloat = 15; // Read a float from the keyboard into a specific location in memory according to method in Read float function.
    const int writeFloat = 16; // Write a float from the memory address to screen according to method in Write float function.
    // Load and store operations
    const int load = 20; // Load a word(int) from a specific location in memory into the accumulator.
    const int store = 21; // Store a word(int) from the accumulator into a specific location in memory.
    const int loadFloat = 22; // Load 2 words(float) from a specific location in memory into the accumulator.
    const int storeFloat = 23; // Store 2 words(float) from the accumulator into a specific location in memory.
    // Arithmetic operations
    const int add = 30; // Add a word(int) from a specific location in memory to the word in the accumulator (leave result in accumulator).
    const int subtract = 31; // Subtract a word(int) from a specific location in memory from the word in the accumulator (leave result in accumulator).
    const int divide = 32; // Divide a word(int) from a specific location in memory into the word in the accumulator (leave result in accumulator).
    const int multiply = 33; // Multiply a word(int) from a specific location in memory by the word in the accumulator (leave result in accumulator).
    const int modulus = 34; // Divide a word(int) from a specific location in memory into the word in the accumulator (leave remainder in accumulator).
    const int exponentiation = 35; // Exponenet  is a word(int) from a specific location in memory that raises the word in the accumulator (leave reult in accumulator).
    const int addFloat = 36; // Add 2 words(float) from a specific location in memory to the word in the accumulator (leave result in accumulator).
    const int subtractFloat = 37; // Subtract 2 words(float) from a specific location in memory from the word in the accumulator (leave result in accumulator).
    const int divideFloat = 38; // Divide 2 words(float) from a specific location in memory into the word in the accumulator (leave result in accumulator).
    const int multiplyFloat = 39; // Multiply 2 words(float) from a specific location in memory by the word in the accumulator (leave result in accumulator).
    // Transfer-of-control operations
    const int branch = 40; // Branch to a specific location in memory.
    const int branchneg = 41; // Branch to a specific location in memory if the accumulator is negative.
    const int branchzero = 42;//  Branch to a specific location in memory if the accumulator is zero.
    const int halt = 43; // Halt—the program has completed its task
    const int branchTenthAligned = 45; // branches to only locations in memory that are multiple of 10 where memory address is interpreted as multiple of 10
    const int branchRelative = 46; // Branch to a specific location that is ahead in memory relative to current address where memory address is number of address ahead of current
    const int branchRelativeNeg = 47; // Branch to a specific location that is ahead in memory relative to current address where memory address is number of address ahead of current if the accumulator is negative.
    const int branchRelativeZero = 48; // Branch to a specific location that is ahead in memory relative to current address where memory address is number of address ahead of current if the accumulator is zero.
    // Debug operations
    const int SML_DEBUG = 4400; // dumps memory and register after execution of each string
    const int NO_SML_DEBUG = 4401; // turns off debug mode

    // check wether memory address in instruction is valid else output error
    if(memory_address >= 0 && memory_address < *MEMORY_SIZE)
    {
        switch(operation_code)
        {
            case read:
            {
                // get only 4 digits of data
                int input_data;
                cin >> input_data;
                while(input_data > MAX_LIMIT || input_data < -MAX_LIMIT)
                {
                    input_data /= 10;
                }
                
                memory[memory_address] = input_data;

                // validated input
                // do
                // {
                //     cin >> input_data;
                //     cout << "\x1b[A";
                // }while(input_data < MIN_LIMIT || input_data > MAX_LIMIT)
                // cout << "\n";
                break;
            }
            case write:
            {
                // output data with sign and padded to 4 digits with 0
                int output_data = memory[memory_address];
                cout << (output_data < 0 ? '-' : '+') << setw(4) << setfill('0') << output_data;
                break;
            }
            case writeNewLine:
            {
                cout << "\n";
                break;
            }
            case readString:
            {
                string input = "";
                cin >> setw(99) >> input;
                readStringMem(input, &memory_address, memory, *MEMORY_SIZE);
                break;
            }
            case writeString:
            {
                writeStringMem(&memory_address, memory, *MEMORY_SIZE);
                break;
            }
            case readFloat:
            {
                // get input from user
                float input = 0;
                cin >> input;
                // seperate whole and decimal part
                int whole_part = input;
                float decimal_part = input - whole_part;

                // keep only last 4 digits
                while(whole_part > MAX_LIMIT || whole_part < -MAX_LIMIT)
                {
                    whole_part /= 10;
                }
                // add whole part(reduced to 4 dgits) with decimal part 
                input = whole_part + decimal_part;

                readFloatMem(input, &memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                break;
            }
            case writeFloat:
            {
                cout << getFloatMem(&memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                break;
            }
            case load:
            {
                *accumalator = memory[memory_address];
                break;
            }
            case store:
            {
                memory[memory_address] = static_cast<int>(*accumalator);
                break;
            }
            case loadFloat:
            { 
                *accumalator = getFloatMem(&memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                break;
            }
            case storeFloat:
            {
                readFloatMem(*accumalator, &memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                break;
            }
            case add:
            {
                *accumalator = static_cast<int>(*accumalator) + memory[memory_address];
                break;
            }
            case subtract:
            {
                *accumalator = static_cast<int>(*accumalator) - memory[memory_address];
                break;
            }
            case divide:
            {
                int divisor = memory[memory_address];
                // if divisor is 0 then halt execution of program and print error message
                if(divisor == 0)
                {
                    cout << "\n"
                         << "\n"
                         << "*** Attempt to divide by zero ***\n"
                         << "*** Simpletron execution abnormally terminated ***\n";
                    *isHalt = true;
                }

                *accumalator = static_cast<int>(*accumalator) / divisor;
                break;
            }
            case multiply:
            {
                *accumalator = static_cast<int>(*accumalator) * memory[memory_address];
                break;
            }
            case modulus:
            {
                int divisor = memory[memory_address];
                // if divisor is 0 then halt execution of program and print error message
                if(divisor == 0)
                {
                    cout << "\n"
                         << "\n"
                         << "*** Modolus of Zero is invalid ***\n"
                         << "*** Simpletron execution abnormally terminated ***\n";
                    *isHalt = true;
                }

                *accumalator = static_cast<int>(*accumalator) % divisor;
                break;
            }
            case exponentiation:
            {
                int exponent = memory[memory_address];
                // if exponenet is less than 0 then halt execution of program and print error message
                if(exponent < 0)
                {
                    cout << "\n"
                         << "\n"
                         << "*** Exponent is Negative ***\n"
                         << "*** Simpletron execution abnormally terminated ***\n";
                    *isHalt = true;
                }
                else
                {
                    int result = 1;
                    int base = static_cast<int>(*accumalator);

                    for(int i = 1; i <= exponent; i++)
                        result *= base;
                    
                    *accumalator = result;
                }
                break;
            }
            case addFloat:
            {
                *accumalator = *accumalator + getFloatMem(&memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                break;
            }
            case subtractFloat:
            {
                *accumalator = *accumalator - getFloatMem(&memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                break;
            }
            case divideFloat:
            {
                float divisor = getFloatMem(&memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                // if divisor is 0 then halt execution of program and print error message
                if(divisor == 0)
                {
                    cout << "\n"
                         << "\n" 
                         << "*** Attempt to divide by zero ***\n"
                         << "*** Simpletron execution abnormally terminated ***\n";
                    *isHalt = true;
                }

                *accumalator = *accumalator / divisor;
                break;
            }
            case multiplyFloat:
            {
                *accumalator = *accumalator * getFloatMem(&memory_address, memory, *MEMORY_SIZE, MAX_LIMIT);
                break;
            }
            case branch:
            {
                *instruction_address = memory_address;
                break;
            }
            case branchneg:
            {
                if(*accumalator < 0)
                    *instruction_address = memory_address;
                break;
            }
            case branchzero:
            {
                if(*accumalator == 0)
                    *instruction_address = memory_address;
                break;
            }
            case halt:
            {
                *isHalt = true;
                cout << "\n"
                     << "\n"
                     << "*** Simpletron Execution Terminated Successfully ***\n";
                break;
            }
            case branchTenthAligned:
            {
                int calculated_memory_address = memory_address * 10;
                if(memory_address < *MEMORY_SIZE)
                {
                    *instruction_address = calculated_memory_address;
                }
                else
                {
                    // out of bounds error
                    cout << "\n"
                         << "\n"
                         << "*** Tenth Aligned Memory Out of Bounds ***\n"
                         << "*** Simpletron execution abnormally terminated ***\n";
                    *isHalt = true;
                }
                break;
            }
            case branchRelative:
            {
                relativeBranchMem(instruction_address, &memory_address, *MEMORY_SIZE, isHalt);
                break;
            }
            case branchRelativeNeg:
            {
                if(*accumalator < 0)
                    relativeBranchMem(instruction_address, &memory_address, *MEMORY_SIZE, isHalt);
                break;
            }
            case branchRelativeZero:
            {
                if(*accumalator == 0)
                    relativeBranchMem(instruction_address, &memory_address, *MEMORY_SIZE, isHalt);
                break;
            }
            case SML_DEBUG / 100:
            {
                if(memory_address == SML_DEBUG % 100)
                {
                    *isDebugActive = true;
                }
                if(memory_address == NO_SML_DEBUG % 100)
                {
                    *isDebugActive = false;
                }
                break;
            }
            default:
            {
                // invalid operation code anf execution halt
                cout << "\n"
                     << "\n"
                     << "*** Invalid operation code ***\n"
                     << "*** Simpletron execution abnormally terminated ***\n";
                *isHalt = true;
                break;
            }
        }
    }
    else
    {
        {
            // out of bounds error
            cout << "\n"
                 << "\n"
                 << "*** Attempt to access out of bounds ***\n"
                 << "*** Simpletron execution abnormally terminated ***\n";
            *isHalt = true;
        }
    }

    // if accumalator overflow 4 digits then set memory_address equal to overflow in -ive or +ive range
    if(*accumalator > MAX_LIMIT || *accumalator < (-1 * MAX_LIMIT))
    {
        // overflow error
        cout << "\n"
             << "\n"
             << "*** Accumulator Overflow ***\n"
             << "*** Simpletron execution abnormally terminated ***\n";
        *isHalt = true;
    }

    if(*isDebugActive == true)
    {
        registerMemoryDump(accumalator, instruction_address, instruction, memory, *MEMORY_SIZE);
    }
}

void registerMemoryDump(float *accumalator, int *instruction_counter, const int *instruction_register, int memory[], const size_t MEMORY_SIZE)
{
    cout << "\n" << fixed << setprecision(4);

    // print values of all registers
    cout << "REGISTERS:\n"
         << "Accumulator:         " << setw(5) << right << *accumalator << "\n"
         << "InstructionCounter:     " << setw(2) << right << *instruction_counter << "\n"
         << "InstructionRegister: " << (*instruction_register >= 0 ? "+" : "") << setw(4) << setfill('0') << right << *instruction_register << "\n"
         << "OperationCode:          " << setw(2) << right << *instruction_register / 100 << "\n"
         << "OperationCode:          " << setw(2) << right << *instruction_register % 100 << "\n"
         << "\n"
         << "Memory:\n"
         << "    "
         << setfill(' ');

    for(int i = 0; i < 10; i++)
    {
        cout << setw(5) << i << " ";
    }

    int instruction;
    cout << "\n" << setfill('0');

    // no col in memory dump
    int no_col = 10;
    // prints values of all emeory cells in no_col * co_col such as 10x10 table with 5 wide columns
    for(int i = 0; i < MEMORY_SIZE / no_col; i++)
    {
        cout << setw(2) << i * no_col << "  " ;
        for(int j = 0; j < no_col; j++)
        {
            instruction = memory[(i * no_col) + j];
            cout << (instruction >= 0 ? "+" : " ") << setw(4) << instruction << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void readStringMem(string input, int *memory_address, int memory[], const size_t MEMORY_SIZE)
{
    // if size is greater than 99 discard overflow
    // then for rest convert from Ascii to custome character set and assign its value
    // for first word, first half constains number of character in strings while latter half contains first charcter value of string
    // for subsequent word, both first and second half have diffrent character value

    int string_size = input.size();
    
    if(string_size > 99)
    {
        cout << "*** Warning: String Longer than 99 character, Overflow discarded ***";
        string_size = 99;
    }

    memory[*memory_address] = string_size * 100;
    memory[*memory_address] += charsetConversion(static_cast<int>(input[0]), false);
    // value word to assign to memory address
    int word_value = 0;
    // address of word accessed
    int write_memory_address = 0;

    for(int i = 1; i <= string_size; i++)
    {
        if(i % 2 == 1)
        {
            word_value = charsetConversion(static_cast<int>(input[i]), false) * 100;
        }
        else
        {
            word_value += charsetConversion(static_cast<int>(input[i]), false);
            write_memory_address = *memory_address + (i / 2);
            
            if(write_memory_address >= MEMORY_SIZE)
                break;

            memory[*memory_address + (i / 2)] = word_value;
        }
    }
}

void writeStringMem(int *memory_address, int memory[], const size_t MEMORY_SIZE)
{
    // from first word, get length of string and first character and print it
    int stringLength = memory[*memory_address] / 100;
    cout << static_cast<char>(charsetConversion(memory[*memory_address] % 100, true));
    // determine address of final character value
    int ending_memory_address = *memory_address + (stringLength / 2);
    // counter for ensureing in case of even number of characters that latter half(empty: ' ') is not considered as character
    // intialized to 1 as 1 charcter has been printed
    int counter = 1;

    // loop from address next to starting and stop before last address
    for(size_t i = *memory_address + 1; i < ending_memory_address; i++)
    {
        cout << static_cast<char>(charsetConversion(memory[i] / 100, true)) 
             << static_cast<char>(charsetConversion(memory[i] % 100, true));
    }

    // all last memory address will have character in first half
    // in case of even latter half will not store any charcter
    // in case of odd number it will have character
    cout << static_cast<char>(charsetConversion(memory[ending_memory_address] / 100, true));
    if(stringLength % 2 == 1)
        cout << static_cast<char>(charsetConversion(memory[ending_memory_address] % 100, true));
}

int charsetConversion (int character, bool toAscii)
{
    char customCharacterSet[100] = {
        ' ','!','"','#','$','%','&','\'','(',')',
        '*','+',',','-','.','/','0','1','2','3',
        '4','5','6','7','8','9',':',';','<','=',
        '>','?','@','A','B','C','D','E','F','G',
        'H','I','J','K','L','M','N','O','P','Q',
        'R','S','T','U','V','W','X','Y','Z','[',
        '\\',']','^','_','`','a','b','c','d','e',
        'f','g','h','i','j','k','l','m','n','o',
        'p','q','r','s','t','u','v','w','x','y',
        'z','{','|','}','~'
    };
    // if toAscii is true then convert from Custom to Ascii
    // if false convert from Ascii to Custom
    // return thier integer value
    // Custom is just Ascii mapping with only printable character which start at 32
    // just reudce Ascii value by 32 you get Custom index of that character
    // that leaves only 95 that can be represented in 2 digits

    int mapping_offset = 32;

    if(toAscii)
    {
        return character + mapping_offset;
    }
    else
    {
        return character - mapping_offset;
    }
}

void readFloatMem(float real_number, int *memory_address, int memory[], const size_t MEMORY_SIZE, const int MAX_LIMIT)
{
    // first word stores integer part
    // seconf word stores decimal part

    // assign float(real_number) to int(first_word) trancuating its decimal part
    int first_word = real_number;
    // get decimal part of float(first_word) and mutiply Max limit + 1 to make required digits  
    int second_word = (real_number - first_word) * MAX_LIMIT;

    // assign whole and decimal part to thier respective word
    // if float memory address is out of bounds do not do anything
    memory[*memory_address] = first_word;
    if(*memory_address + 1 < MEMORY_SIZE)
        memory[*memory_address + 1] = second_word;
}
float getFloatMem(int *memory_address, int memory[], const size_t MEMORY_SIZE, const int MAX_LIMIT)
{
    int whole_part = memory[*memory_address];
    int decimal_part = 0;

    if(*memory_address + 1 < MEMORY_SIZE)
    {
        decimal_part = memory[*memory_address + 1];
    }

    return static_cast<float>(whole_part) + (static_cast<float>(decimal_part) / (MAX_LIMIT + 1));
}

void relativeBranchMem(int *instruction_address, int *memory_address, const size_t MEMORY_SIZE, bool *isHalt)
{
    // in case of relative branch
    // instruction address is starting location
    // memory address is number of position to move ahead
    // as long as address in with in bounds
    // instruction address is incremented before instruction is executed
    // therefore one is subtracted from total 

    int relative_address = *instruction_address + *memory_address - 1;
    if(relative_address > MEMORY_SIZE || relative_address < 0)
    {
        cout << "\n"
             << "\n"
             << "*** Relative Address is Out of Bounds ***\n"
             << "*** Simpletron execution abnormally terminated ***\n";
        
        *isHalt = true;
    }
    else
    {
        *instruction_address = relative_address;
    }
}