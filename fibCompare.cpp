#include "fibonacci.h"
#include <iomanip>

/*
 * FibCompare is used to make a comparison between the two fibonacci calculations.
 * Uses mpz bigNum to handle values larger than normal c++ data types
 * Compares between slow form of calculation and quick form
 * Quick - uses multiplication of 2x2 matrices for very fast calculation
 * Slow - traditional method using addition of previous values
 * Usage: fibCompare startVal stepVal stepNum printSteps
 * startVal - the first value to compare between the fib types
 * stepVal - how much to increase the value by each step
 * stepNum - how many steps to take before finishing calculation
 * stepType - whether the steps should be taken multiplicatively or additively, 0 for mult, 1 for add
 */

int cmdArgNum = 5; // Function has 4 total args: function, fibNum, printType, fibType

struct timespec start, finish;

int main(int argc, char** argv)
{
    if(argc > cmdArgNum){ // Function requires at least  a number for calculation and can't take more that 3 external args
        std::cout << "Invalid number of inputs." << std::endl;
        std::cout << "Expected use: fibCompare [startVal] [stepVal] [stepNum] [stepType]" << std::endl;
        return 1;
    }
    // Default is to start at 10 and increase by factor of 10 to 1000000
    int startVal = 10;
    int stepVal= 10;
    int stepNum = 6;
    int stepType = 0;
    if(argc > 1){
        std::istringstream iss1(argv[1]); // Used to convert command line argument to string
        if(iss1 >> startVal && startVal > 0){} //Sets fibNum as first command line argument if valid
        else{
            std::cout << "Invalid first argument. Expecting positive integer." << std::endl;
            return 1; // Returns with error if argument is invalid
        }
    }
    if(argc > 2){ // Only try to set print type if there are enough arguments
        std::istringstream iss2(argv[2]); // Used to convert command line argument to string
        if(iss2 >> stepVal && stepVal >= 0){} //Sets fibNum as first command line argument if valid
        else{
            std::cout << "Invalid second argument. Expecting non-negative integer." << std::endl;
            return 1; // Returns with error if argument is invalid
        }
    }
    if(argc > 3){
        std::istringstream iss3(argv[3]); // Used to convert command line argument to string
        if(iss3 >> stepNum && stepNum > 0){} //Sets fibNum as first command line argument if valid
        else{
            std::cout << "Invalid third argument. Expecting integer." << std::endl;
            return 1; // Returns with error if argument is invalid
        }
    }
    if(argc > 4){
        std::istringstream iss4(argv[4]); // Used to convert command line argument to string
        if(iss4 >> stepType && (stepType == 0 || stepType == 1)){} //Sets fibNum as first command line argument if valid
        else{
            std::cout << "Invalid fourth argument. Expecting 1 or 0." << std::endl;
            return 1; // Returns with error if argument is invalid
        }
    }
    mpz_t quickResult; // Defines big integer for holding fibonacci value
    mpz_init(quickResult); // mpz values must be initialized
    mpz_t slowResult;
    mpz_init(slowResult);
    int fibNum = startVal;                         //
    std::cout << std::left << 
                 std::setw(20) << "Fibonacci Number" << 
                 std::setw(14) << "Quick Time" << 
                 std::setw(13) << "Slow Time" <<
                 std::setw(22) << "Quick Times Faster" << 
                 std::endl;
    for(int i = 0;i < stepNum;i++){
        clock_gettime(CLOCK_MONOTONIC, &start);
        fibQuick(fibNum, quickResult);
        clock_gettime(CLOCK_MONOTONIC, &finish);
        float quickTime = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        clock_gettime(CLOCK_MONOTONIC, &start);
        fibSlow(fibNum, slowResult);
        clock_gettime(CLOCK_MONOTONIC, &finish);
        float slowTime = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        
        if(mpz_cmp(quickResult, slowResult)){
            std::cout << "Calculation error: quick and slow methods did not produce the same result." << std::endl;
            return 1;
        }

        std::cout << std::left << 
                     std::setw(20) << fibNum << 
                     std::setw(14) << quickTime << 
                     std::setw(13) << slowTime <<
                     std::setw(22) << slowTime / quickTime << 
                     std::endl;

        if(stepType)
            fibNum += stepVal;
        else
            fibNum *= stepVal;

    }
    return 0;
}
