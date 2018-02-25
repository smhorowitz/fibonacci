import datetime
import math

def matrixmultiply(matrix1, matrix2):
    a = (matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0])
    b = (matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1])
    c = (matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0])
    d = (matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1])
    return [[a, b], [c, d]]

def twobytwopower(exponent):
    matrix = [[1, 0], [0, 1]]
    left = exponent
    while left > 0:
        power = int(math.log(left, 2))
        tempmatrix = [[0, 1], [1, 1]]
        for x in range(power):
            tempmatrix = matrixmultiply(tempmatrix, tempmatrix)
        matrix = matrixmultiply(matrix, tempmatrix)
        left = left - (math.pow(2, power))
    
    return matrix

def fib(num):
    matrix = twobytwopower(num)
    return matrix[0][0] + matrix[0][1]

num = input("Which fibonacci term would you like to calculate?")

start = datetime.datetime.now()
fibnum = fib(num)
end = datetime.datetime.now()
time = end - start

start = datetime.datetime.now()
print fibnum
end = datetime.datetime.now()
printtime = end - start

print "Calculation took %r seconds" % time.total_seconds()
print "Printing took %r seconds" % printtime.total_seconds()

