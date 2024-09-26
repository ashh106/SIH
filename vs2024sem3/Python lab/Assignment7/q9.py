global_variable = 10

def change_global_value():
    global global_variable  
    global_variable = 20     

change_global_value()
print(f"The changed global variable is: {global_variable}")
