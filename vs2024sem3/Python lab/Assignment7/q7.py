def fibonacci(n):

    if n == 0:
        return 0
 
    elif n == 1:
        return 1
   
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)

n = int(input("Enter a number to compute its Fibonacci value: "))

result = fibonacci(n)
print(f"The Fibonacci value of f({n}) is: {result}")
