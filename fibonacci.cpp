#include "fibonacci.h"

int cmdArgNum = 4; 

int main(int argc, char** argv)
{
    if(argc < 2 || argc > cmdArgNum){
        std::cout << "Invalid number of inputs." << std::endl;
        return 1;
    }
    int fibNum;
    int doPrint = 0;
    int fibType = 0;
    std::istringstream iss(argv[1]);
    if(iss >> fibNum && fibNum > 0){} //Sets fibNum as first command line argument if valid
    else{
        std::cout << "Invalid first argument. Expecting positive integer." << std::endl;
        return 1;
    }
    if(argc > 2){
        std::istringstream bss(argv[2]);
        if(bss >> doPrint){} //Sets doPrint as second command line argument if valid
        else{
            std::cout << "Invalid second argument. Expecting integer." << std::endl;
            return 1;
        }
    }
    if(argc > 3){
        std::istringstream bss(argv[3]);
        if(bss >> fibType){} //Sets fibType as third command line argument if valid
        else{
            std::cout << "Invalid third argument. Expecting integer." << std::endl;
            return 1;
        }
    }
    mpz_t result;
    mpz_init(result);
    time_t calcTimerInit;
    time_t calcTimerEnd;
    time(&calcTimerInit);
    if(fibType)
        fibSlow(fibNum, result);
    else
        fibQuick(fibNum, result);
    time(&calcTimerEnd);
    if(doPrint){
        if(doPrint == 2){
            std::cout << result << std::endl;
            return 0;
        }
        time_t printTimerInit;
        time_t printTimerEnd;
        int lastDigit = fibNum % 10;
        switch(lastDigit){
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
