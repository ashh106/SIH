# def count(s, c):
#     char_count = {}
#     for i in range(len(s)):
#         if (s[i]==c):
#             char_count=char_count+1
#     return char_count
# x = (input("ENTER THE STRING: "))
# y = input("Enter the character: ")     
# print(count(x, y))

# x = str(input("enter a string: "))
# char_count = {}
# for char in char_count :
#     if char in char_count :
#        char_count[char]+=1
#     else:
#         char_count[char]=1
# print("counts: ",  char_count)        
           
           
# birthdays = {
#     "Aashutosh": "15th August",
#     "Alice": "12th December",
#     "Bob": "23rd April",
#     "Charlie": "5th October"
# }          
# name_string = "Aashutosh, Alice, Bob, Charlie"
# name_list = name_string.split(", ")
# print("List of names after split:", name_list) 
# new_name_string = " | ".join(name_list)
# print("Names recombined with '|' as separator:", new_name_string)             
# name_to_find = input("name to find: ")
# if name_to_find in birthdays :
#     print(f"{name_to_find}'s birthday is on {birthdays[name_to_find]}")
# else:
#     print(f"sorry we have no information ablout {name_to_find} : ")
    
    
# import math
# def compute_gcd(a, b):
#     return math.gcd(a, b)
# def compute_lcm(a, b):
#     gcd = compute_gcd(a, b)
#     return abs(a * b) // gcd
# num1 = 36
# num2 = 48
# gcd_result = compute_gcd(num1, num2)
# lcm_result = compute_lcm(num1, num2)
# print(f"GCD of {num1} and {num2} is: {gcd_result}")
# print(f"LCM of {num1} and {num2} is: {lcm_result}")

# import math
# def ball_collide(ball1, ball2):
#     x1, y1, r1 = ball1
#     x2, y2, r2 = ball2
#     distance = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
#     sum_of_radii = r1 + r2
#     return distance <= sum_of_radii
# ball1 = (0, 0, 5)  # Ball at (0, 0) with radius 5
# ball2 = (7, 0, 3)  # Ball at (7, 0) with radius 3
# colliding = ball_collide(ball1, ball2)
# print(f"Are the balls colliding? {colliding}")

# import statistics
# def calculate_statistics(numbers):
#     # Calculate mean
#     mean_value = statistics.mean(numbers)
#     # Calculate median
#     median_value = statistics.median(numbers)
#     # Calculate mode
#     try:
#         mode_value = statistics.mode(numbers)
#     except statistics.StatisticsError:
#         mode_value = "No unique mode"
#     return mean_value, median_value, mode_value
# # Example usage
# numbers = [1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 5]
# mean_value, median_value, mode_value = calculate_statistics(numbers)
# print(f"Mean: {mean_value}")
# print(f"Median: {median_value}")
# print(f"Mode: {mode_value}")


def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]
        
        merge_sort(L)
        merge_sort(R)
        
        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

def selection_sort(arr):
    for i in range(len(arr)):
        min_idx = i
        for j in range(i+1, len(arr)):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def sort_switch_case(choice, arr):
    switcher = {
        1: bubble_sort,
        2: merge_sort,
        3: selection_sort,
        4: insertion_sort
    }
    
    sort_function = switcher.get(choice, lambda x: "Invalid choice")
    if callable(sort_function):
        sort_function(arr)
    else:
        print(sort_function)

# Example usage
if __name__ == "__main__":
    # Input list and choice
    arr = [64, 34, 25, 12, 22, 11, 90]
    print("Original array:", arr)
    
    print("Choose sorting algorithm:")
    print("1. Bubble Sort")
    print("2. Merge Sort")
    print("3. Selection Sort")
    print("4. Insertion Sort")
    
    choice = int(input("Enter your choice (1/2/3/4): "))
    
    # Perform sorting based on choice
    sort_switch_case(choice, arr)
    
    print("Sorted array:", arr)
