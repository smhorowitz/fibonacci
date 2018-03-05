#include "fibonacci.h"

/*
 * Fibonacci is used to return the nth fibonacci number.
 * Has two methods, "quick" and "slow"
 * Uses mpz bigNum to handle calues larger than normal c++ data types
 * Quick - uses multiplication of 2x2 matrices for very fast calculation
 * Slow - traditional method using addition of previous values
 * Usage: fibonacci fibNum printType fibType
 * fibNum - the fibonacci number to be calculated
 * printType - how to print (default is 0): 
 *             0 only prints calculation time
 *             1 prints fibonacci number with calculation and print time
 *             2 only prints fibonacci number
 * fibType - which calculation method to use (default is 0):
 *                           0 for quick
 *                           1 for slow
 */

int cmdArgNum = 4; // Function has 4 total args: function, fibNum, printType, fibType

int main(int argc, char** argv)
{
    if(argc < 2 || argc > cmdArgNum){ // Function requires at least  a number for calculation and can't take more that 3 external args
        std::cout << "Invalid number of inputs." << std::endl;
        return 1;
    }
    int fibNum;
    int printType = 0; // Default is to only do calculation and print time taken
    int fibType = 0; // Default is quick method
    std::istringstream iss(argv[1]); // Used to convert command line argument to string
    if(iss >> fibNum && fibNum > 0){} //Sets fibNum as first command line argument if valid
    else{
        std::cout << "Invalid first argument. Expecting positive integer." << std::endl;
        return 1; // Returns with error if argument is invalid
    }
    if(argc > 2){ // Only try to set print type if there are enough arguments
        std::istringstream bss(argv[2]); // Used to convert command line argument to string
        if(bss >> printType){} //Sets printType as second command line argument if valid
        else{
            std::cout << "Invalid second argument. Expecting integer." << std::endl;
            return 1; // Returns with error if argument is invalid
        }
    }
    if(argc > 3){
        std::istringstream bss(argv[3]); // Used to convert command line argument to string
        if(bss >> fibType){} //Sets fibType as third command line argument if valid
        else{
            std::cout << "Invalid third argument. Expecting integer." << std::endl;
            return 1; // Returns with error if argument is invalid
        }
    }
    mpz_t result; // Defines big integer for holding fibonacci value
    mpz_init(result); // mpz values must be initialized
    time_t calcTimerInit; //    
    time_t calcTimerEnd;  // Times used to figure out calculation time of function
    time(&calcTimerInit);
    if(fibType) // Performs slow calculation if fibType is 1, quick calculation otherwise
        fibSlow(fibNum, result);
    else
        fibQuick(fibNum, result);
    time(&calcTimerEnd);
    if(printType){ // If printType is 0, only prints calculation time
        if(printType == 2){
            std::cout << result << std::endl;
            return 0; // Done after printing result of calculation
        }
        time_t printTimerInit;
        time_t printTimerEnd;
        int lastDigit = fibNum % 10;
        switch(lastDigit){ // Properly numerates which fibonacci number is being calculated
            case 1: std::cout << fibNum << "st "; break;
            case 2: std::cout << fibNum << "nd "; break;
            case 3: std::cout << fibNum << "rd "; break;
            default: std::cout << fibNum << "th ";
        }
        time(&printTimerInit);
        std::cout << "fibonacci number is: " << result << std::endl;
        time(&printTimerEnd);
        std::cout << "Printing took " << difftime(printTimerEnd, printTimerInit) << " seconds." << std::endl;
    }
    std::cout << "Calculation took " << difftime(calcTimerEnd, calcTimerInit) << " seconds." << std::endl;
    return 0;
}
