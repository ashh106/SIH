
import sys
print(sys.version)
print ("hello world")

"""comment in more than one line"""
# comment in single line

x = 2.3 
print (x)
# casting
# unpacking list
pagal = [int (5.6) , float (4.6) , str(54) , "ashh" , "hi"]
t , z , y , q , j= pagal
# t , z , y = int (5.6) , float (4.6) , str(54)
# t= int (5.6)
# z= float(4.7)
# y = str(54)
# both are float value
print(x , y , z , t , q , j)
print( x + z ) 
print(j + " " + q)
a = 4
A = "hi"
print (a , A)
# A will not over write

i = " "
def myfan():
    global i
    i = "uwu"
myfan()
print(" python is " + i)