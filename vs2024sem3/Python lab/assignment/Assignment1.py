# 1 pyhton version
import sys
print(sys.version)
print("\n")
# 2 list of all keywords in python 
import keyword
print("The List og keywords is:")
for k in keyword.kwlist:
    print( k )
print("\n")
# 3 i/p user name and age. o/p - 
x = input ("enter name: ")
y = int (input ("enter age: "))
z = 100-y
print (x," be turning 100 in ",z,"year")
# 4 radius of circle 
import math
r = int (input ("entre radius of circle: "))
a = math.pi*r**2
print ("area of required circle : ",a)    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            # 
# 5
# Taking input from the user
number = int(input("Enter a number: "))

# Checking if the number is even or odd
if number % 2 == 0:
    print(f"The number {number} is even.")
else:
    print(f"The number {number} is odd.")
    
# 6 
# Taking the string from the user
string = input("Enter a string: ")

# Remove spaces & convert to lowercase for uniformity
processed_string = string.replace(" ", "").lower()

# Checking  if the string is equal to its reverse
if processed_string == processed_string[::-1]:
    print(f"The string '{string}' is a palindrome.")
else:
    print(f"The string '{string}' is not a palindrome.")
    
    
# 7
# Taking the two input strings from the user
string1 = input("Enter the first string: ")
string2 = input("Enter the second string: ")

# Swap the first two characters of each string
if len(string1) >= 2 and len(string2) >= 2:
    swapped_string1 = string2[:2] + string1[2:]
    swapped_string2 = string1[:2] + string2[2:]
else:
    swapped_string2 = string1 + string2[1:]

# Combine the swapped strings into a single string separated by a space
result = swapped_string1 + " " + swapped_string2

print("Resulting string:", result)

# 8
def is_valid_identifier(identifier):
    if not identifier.isidentifier():
        return False
    return True

# Example usage
identifier = input("Enter a string: ")

if is_valid_identifier(identifier):
    print(f"'{identifier}' is a valid identifier.")
else:
    print(f"'{identifier}' is not a valid identifier.")

# 9
def swap_first_last_chars(s):
    if len(s) < 2:
        return s  # If the string has less than 2 characters, return it as it is
    return s[-1] + s[1:-1] + s[0]

# Example usage
string = input("Enter a string: ")
new_string = swap_first_last_chars(string)
print("New string:", new_string)


# 10

# Taking input from the user
user_input = input("Enter a string: ")

# Converting to uppercase and lowercase
upper_case = user_input.upper()
lower_case = user_input.lower()

# Displaying the results
print("Uppercase:", upper_case)
print("Lowercase:", lower_case)





