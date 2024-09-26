
x = input("what's your name? ")
print("hello,", x)

# funstion , bugs , return values , variables , comments
""" comments: str - string , fuction takes arguments """
# print(*objects, sep=' ', end = '\n', file=sys.stdout , flush = false)
# print fxn can take any no. of object 
# parameters - {}  \escaping\\    
name = input("what's your nick name? ").strip().title()
# capitalize user's name
# name = name.title()
# name = name.strip().title()
# remove white space 

# split username into first name and last name
first, last = x.split(" ")
print(f"hello, {first}")
# interactive mode
a = int(input("what's x? "))
y = input("what's y? ")
# type cast
j = (a) + int(y)
# z = (a)*int(y)
print((a)*int(y))
print(j)

# print(int(input("what's x?"))+ int(input("what's y?")))
nam = str("ashutosh")
print(nam[0:4])