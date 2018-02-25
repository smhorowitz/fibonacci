#include <iostream>
#include <math.h>
#include <gmp.h>
#include <sstream>
#include <time.h>

void matrixMultiply(mpz_t matrix1[], mpz_t matrix2[], mpz_t temp[]);
void twobytwopower(int exponent, mpz_t matrix[]);
void fib(int num);

int main(int argc, char** argv)
{
    std::istringstream iss(argv[1]);
    int val;
    iss >> val;
    fib(val);
    return 0;
}

void matrixMultiply(mpz_t matrix1[], mpz_t matrix2[], mpz_t temp[])
{
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

void twobytwopower(int exponent, mpz_t matrix[])
{
    mpz_t tempmatrix[4];
    mpz_t base[4];
    mpz_init(tempmatrix[0]);
    mpz_init(tempmatrix[1]);
    mpz_init(tempmatrix[2]);
    mpz_init(tempmatrix[3]);
    mpz_init(base[0]);
    mpz_init(base[1]);
    mpz_init(base[2]);
    mpz_init(base[3]);
    int left = exponent;
    int power;
    while(left > 0)
    {
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
}

void fib(int num)
{
    time_t calcTimerInit;
    time_t printTimerInit;
    time_t calcTimerEnd;
    time_t printTimerEnd;
    time(&calcTimerInit);
    mpz_t matrix[4];
    mpz_init(matrix[0]);
    mpz_init(matrix[1]);
    mpz_init(matrix[2]);
    mpz_init(matrix[3]);
    mpz_set_ui(matrix[0], 1);
    mpz_set_ui(matrix[1], 0);
    mpz_set_ui(matrix[2], 0);
    mpz_set_ui(matrix[3], 1);
    twobytwopower(num, matrix);
    mpz_t result;
    mpz_init(result);
    mpz_add(result, matrix[0], matrix[1]);
    time(&calcTimerEnd);
    //time(&printTimerInit);
    //std::cout << result << std::endl;
    //time(&printTimerEnd);
    st::cout << "Calculation took" << difftime(calcTimerEnd, calcTimerInit) << "seconds." << std::endl;
    //std::cout << "Printing took" << difftime(printTimerEnd, printTimerInit) << "seconds." << std::endl;
}
