# l = [1,2,3,4,5,3]
# l.extend("adb3")
# print(l)
# l.append("xyz")
# print(l)
# l.pop(6)
# print(l)
# l.remove("xyz")
# print(l)
# l.insert(5, 6)
# print(l)
# a = "Python Hello"
# L = list(a)
# print(L)
# n= l.index(3)
# print(n)
# b = a
# b = b + 'HELLO'
# print(b, len(b))
# print(a, len(a))
# x = list(zip([10,20]))
# print(x)
# for i1, i2 in zip([10,20,30,40,50],[20,30,40]):
#     print(i1,i2,sep = "\t")

# n = int(input("enter a number: "))
# def fun(n):
#     sum =0
#     for i in range (n) :
#         sum = sum + i
#         print(sum , i)
    
#     # fun(n-1)       
# print(fun(n)) 

  
# A = [1,2,3]     
# for i in range(len(A)):
#     print(A[i])
#     A=[]


x = "abcdef"
i = "a"
for i in x :
    x = x[1:]
    print(i, end="")