#include <iostream>
#include <math.h>
#include <gmp.h>
#include <sstream>
#include <time.h> // TODO: Find a more accurate way to measure time

 
void fibQuick(int fibNum, mpz_t result);
void matrixMultiply(mpz_t result[], mpz_t matrix1[], mpz_t matrix2[]);
void twobytwopower(int exponent, mpz_t result[]);
void fibSlow(int fibNum, mpz_t result);
/*
 * fibQuick calculates fibonacci value using multiplication of a 2x2 matrix, 
 * represented here as a length 4 array
 * [a b] = {a, b, c, d}
 * [c d]
 * [a1 b1] * [a2 b2] = [((a1 * a2) + (b1 * c2)) ((a1 * b2) + (b1 * d2))]
 * [c2 d2]   [c2 d2]   [((c1 * a2) + (d1 * c2)) ((c1 * b2) + (d1 * d2))]
 * [0 1] ^ n = [a b] and a + b = (n+1)th fibonacci number
 * [1 1]       [c d]
 *
 * Inputs:
 *      fibNum: integer representing fibonacci value to be calculated
 *      result: bigNum integer that resulting value is returned to
 */

void fibQuick(int fibNum, mpz_t result){
    mpz_t matrix[4];
    for(int i = 0;i < 4;i++) // bigNum integers must be initialized
        mpz_init(matrix[i]);
    mpz_set_ui(matrix[0], 1); // initial matrix is set as identity matrix
    mpz_set_ui(matrix[1], 0);
    mpz_set_ui(matrix[2], 0);
    mpz_set_ui(matrix[3], 1);
    twobytwopower((fibNum - 1), matrix); // fibNum -1 is used to properly calculate nth fib number instead of n+1th
    mpz_add(result, matrix[0], matrix[1]); // adding first 2 values of matrix results in fibonacci number
    for(int i = 0;i < 4;i++)
        mpz_clear(matrix[i]); // Clearing bigNum ints to revent memory leak
}

/*
 * matrixMultiply takes two arrays, "matrix1" and "matrix2", each of length 4,
 * multiplies them, and returns the result as the length 4 array "result"
 * result = matrix1 * matrix2
 *
 * Inputs:
 *     mpz_t result: length 4 array of bigNum ints, where the resulting array is returned
 *     mpz_t matrix1: length 4 array of bigNum ints, first array to be multiplied
 *     mpz_t matrix2: length 4 array of bigNum ints, second array to be multiplied
 */

void matrixMultiply(mpz_t result[], mpz_t matrix1[], mpz_t matrix2[]){
    mpz_t temp[4];
    for(int i = 0; i < 4;i++) // Sets up temp matrix used to record intermediary operations
        mpz_init(temp[i]);
    mpz_mul(temp[0], matrix1[0], matrix2[0]);
    mpz_addmul(temp[0], matrix1[1], matrix2[2]); // a = (a1 * a2) + (b1 * c2)
    mpz_mul(temp[1], matrix1[0], matrix2[1]);
    mpz_addmul(temp[1], matrix1[1], matrix2[3]); // b = (a1 * b2) + (b1 * d2)
    mpz_mul(temp[2], matrix1[2], matrix2[0]);
    mpz_addmul(temp[2], matrix1[3], matrix2[2]); // c = (c1 * a2) + (d1 * c2)
    mpz_mul(temp[3], matrix1[2], matrix2[1]);
    mpz_addmul(temp[3], matrix1[3], matrix2[3]); // d = (c1 * b2) + (d1 * d2)
    for(int i = 0; i < 4;i++)
        mpz_set(result[i], temp[i]); // Puts temp values into result array
    for(int i = 0; i < 4;i++)
        mpz_clear(temp[i]); // Bignums need to be cleared to prevent memory leaks
}

/*
 * twobytwopower takes the array [0, 1, 1, 1] (representing a 2x2 matrix) and raises it to a given exponent,
 * then multiplies is by the given matrix (if given identity returns the exponentiated matrix
 * multiplies together matrices exponentiated to powers of two for efficiency
 * exponentiating a matrix to a power of two can be done by repeated squaring, requiring less multiplications
 * matrixA^21 = matrixA^16 * matrixA^4 * matrixA = (((matrixA^2)^2)^2)^2 * (matrixA^2)^2 * matrixA
 * the above example reduces matrixA^21 from 21 multiplications to 8 multiplications
 * in general, this turns exponentiation from an O(n) function to an O(logn) function
 *
 * Inputs:
 *      int exponent: the exponent to raise the mastrix to
 *      mpz_t result: length 4 array that resulting matrix is multiplied by (usually expected to be given identity)
 */
void twobytwopower(int exponent, mpz_t result[]){
    mpz_t base[4]; // base is [0, 1, 1, 1] matrix used for exponentiation
    for(int i = 0;i < 4;i++)
        mpz_init(base[i]);
    int left = exponent;
    int power; // keeps track of how many times to square each loop iteration
    while(left > 0){ // Exponantiation done by repeated squaring and multiplication for increased efficiency
        power = static_cast<int>(log2(left)); 
        mpz_set_ui(base[0], 0);
        mpz_set_ui(base[1], 1);
        mpz_set_ui(base[2], 1);
        mpz_set_ui(base[3], 1);
        for(int x = 0;x < power;x++) // each loop base is squared log2(n) times, which is quicker than multiplying n times
            matrixMultiply(base, base, base);
        matrixMultiply(result, base, result); // each loop multiplies squared base by current value
        left -= pow(2, power);
    }
    for(int i = 0;i < 4;i++)
        mpz_clear(base[i]);
}

/*
 * fibSlow calculates fibonacci value in classical way, calculating each value up to fibNum by adding the previous 2
 *
 * Inputs:
 *      fibNum: which fibonacci number is to be calculated
 *      result: location the resulting value is returned to
 */

void fibSlow(int fibNum, mpz_t result){
    mpz_t temp1;            // Setting up temp values to be used in addition
    mpz_init(temp1);        // setting them initially to 0 and 1 allows correct early fib values
    mpz_set_ui(temp1,0);
    mpz_t temp2;
    mpz_init(temp2);
    mpz_set_ui(temp2,1);
    mpz_set_ui(result, 1);
    for(int i = 1;i < fibNum;i++){ // each iteration of loop calculates ith fib value by adding previous two
        mpz_add(result, temp1, temp2);
        mpz_set(temp1, temp2);
        mpz_set(temp2, result);
    }
    mpz_clear(temp1); // clearing bigNums
    mpz_clear(temp2);
}
