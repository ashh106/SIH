def count_local_variables():
   
    a = 10
    b = 20
    c = 30
    d = 40
    

    local_vars = locals()
    
   
    num_local_vars = len(local_vars)
    
    return num_local_vars


local_variable_count = count_local_variables()
print(f"The number of local variables declared in the function is: {local_variable_count}")
