#include <iostream>
#include <math.h>
#include <gmp.h>
#include <sstream>
#include <time.h>

void matrixMultiply(mpz_t matrix1[], mpz_t matrix2[], mpz_t temp[]);
void twobytwopower(int exponent, mpz_t matrix[]);
void fibQuick(int fibNum, mpz_t result);
void fibSlow(int fibNum, mpz_t result);

int cmdArgNum = 4; 

int main(int argc, char** argv)
{
    if(argc != cmdArgNum){
        std::cout << "Wrong number of inputs.\nExpected " << cmdArgNum - 1 << "." <<  std::endl;
        return 1;
    }
    int fibNum;
    bool doPrint;
    int fibType;
    std::istringstream iss(argv[1]);
    std::istringstream bss(argv[2]);
    std::istringstream tss(argv[3]);
    if(iss >> fibNum && fibNum > 0){} //Sets fibNum as first command line argument if valid
    else{
        std::cout << "Invalid first argument. Expecting positive integer." << std::endl;
        return 1;
    }
    if(bss >> doPrint){} //Sets doPrint as second command line argument if valid
    else{
        std::cout << "Invalid second argument. Expecting boolean." << std::endl;
        return 1;
    }
    if(tss >> fibType && fibType > 0 && fibType < 4){} //Sets doPrint as second command line argument if valid
    else{
        std::cout << "Invalid third argument. Expecting boolean." << std::endl;
        return 1;
    }
    mpz_t result;
    mpz_init(result);
    time_t calcTimerInit;
    time_t calcTimerEnd;
    if(fibType == 1){
        time(&calcTimerInit);
        fibQuick(fibNum, result);
        time(&calcTimerEnd);
    } else if(fibType == 2){
        time(&calcTimerInit);
        fibSlow(fibNum, result);
        time(&calcTimerEnd);
    } else if(fibType == 3){
        mpz_t result2;
        mpz_init(result2);
        fibQuick(fibNum, result);
        fibSlow(fibNum, result2);
        if(mpz_cmp(result, result2) == 0){
            std::cout << "Pass" << std::endl;
            return 0;
        }else{
            std::cout << "Fail" << std::endl;
            return 0;
        }
    } else{
        std::cout << "Invalid fib type." << std::endl;
        return 1;
    }
    if(doPrint){ time_t printTimerInit;
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

void matrixMultiply(mpz_t matrix1[], mpz_t matrix2[], mpz_t temp[]){
    mpz_mul(temp[0], matrix1[0], matrix2[0]);
    mpz_addmul(temp[0], matrix1[1], matrix2[2]);
    mpz_mul(temp[1], matrix1[0], matrix2[1]);
    mpz_addmul(temp[1], matrix1[1], matrix2[3]);
    mpz_mul(temp[2], matrix1[2], matrix2[0]);
    mpz_addmul(temp[2], matrix1[3], matrix2[2]);
    mpz_mul(temp[3], matrix1[2], matrix2[1]);
    mpz_addmul(temp[3], matrix1[3], matrix2[3]);
    mpz_set(matrix1[0], temp[0]);
    mpz_set(matrix1[1], temp[1]);
    mpz_set(matrix1[2], temp[2]);
    mpz_set(matrix1[3], temp[3]);
}

void twobytwopower(int exponent, mpz_t matrix[]){
    mpz_t tempmatrix[4];
    mpz_t base[4];
    for(int i = 0;i < 4;i++)
        mpz_init(tempmatrix[i]);
    for(int i = 0;i < 4;i++)
        mpz_init(base[i]);
    int left = exponent;
    int power;
    while(left > 0){
        power = static_cast<int>(log2(left));
        mpz_set_ui(base[0], 0);
        mpz_set_ui(base[1], 1);
        mpz_set_ui(base[2], 1);
        mpz_set_ui(base[3], 1);
        for(int x = 0;x < power;x++)
            matrixMultiply(base, base, tempmatrix);
        matrixMultiply(matrix, base, tempmatrix);
        left -= pow(2, power);
    }
    for(int i = 0;i < 4;i++)
        mpz_clear(tempmatrix[i]);
    for(int i = 0;i < 4;i++)
        mpz_clear(base[i]);
}

void fibQuick(int fibNum, mpz_t result){
    mpz_t matrix[4];
    for(int i = 0;i < 4;i++)
        mpz_init(matrix[i]);
    mpz_set_ui(matrix[0], 1);
    mpz_set_ui(matrix[1], 0);
    mpz_set_ui(matrix[2], 0);
    mpz_set_ui(matrix[3], 1);
    twobytwopower(fibNum, matrix);
    mpz_add(result, matrix[0], matrix[1]);
    for(int i = 0;i < 4;i++)
        mpz_clear(matrix[i]);
}

void fibSlow(int fibNum, mpz_t result){
    mpz_t temp1;
    mpz_init(temp1);
    mpz_set_ui(temp1,0);
    mpz_t temp2;
    mpz_init(temp2);
    mpz_set_ui(temp2,1);
    for(int i = 0;i < fibNum;i++){
        mpz_add(result, temp1, temp2);
        mpz_set(temp1, temp2);
        mpz_set(temp2, result);
    }
    mpz_clear(temp1);
    mpz_clear(temp2);
}
