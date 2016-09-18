# import datetime
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

def fibmatrix(num):
    matrix = twobytwopower(num)
    return matrix[0][0] + matrix[0][1]

def fibrecursive(num):
    if num == 1 or num == 0:
        return 1

    return fibrecursive(num - 1) + fibrecursive(num - 2)

def fibloop(num):
    f0 = 1
    f1 = 1
    for x in range(num):
        temp = f1
        f1 += f0
        f0 = temp

    return f0

def fibformula(num):
    return (((((1 + math.sqrt(5)) / 2) ** num) - (((1 - math.sqrt(5)) / 2) ** num)) / math.sqrt(5))

# start = datetime.datetime.now()
# fibmatrix(100000)
# end = datetime.datetime.now()
# matrixtime = end - start

# start = datetime.datetime.now()
# fibrecursive(30)
# end = datetime.datetime.now()
# recursivetime = end - start

# start = datetime.datetime.now()
# fibloop(100000)
# end = datetime.datetime.now()
# looptime = end - start

# start = datetime.datetime.now()
# fibformula(1000)
# end = datetime.datetime.now()
# formulatime = end - start

# print fibmatrix(100000) == fibloop(100000)

# print "Matrix took %r" % matrixtime.total_seconds()
# print "Recursive took %r" % recursivetime.total_seconds()
# print "Loop took %r" % looptime.total_seconds()
# print "Formula took %r" % formulatime.total_seconds()
