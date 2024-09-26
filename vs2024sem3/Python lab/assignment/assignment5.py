
def find_symmetric_difference(store1_sales, store2_sales):
    # Convert lists to sets
    set1 = set(store1_sales)
    set2 = set(store2_sales)
    
    # Compute symmetric difference
    symmetric_diff = set1 ^ set2  # Alternatively, you could use set1.symmetric_difference(set2)
    
    # Convert result to list if needed and return
    return list(symmetric_diff)

# Example usage
store1_sales = [101, 102, 103, 104, 105]
store2_sales = [103, 104, 106, 107, 108]

result = find_symmetric_difference(store1_sales, store2_sales)
print(result)  # Output: [106, 107, 108, 101, 102, 105]
