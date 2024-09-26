def append_item(item, item_list=None):
    if item_list is None:  
        item_list = []
    item_list.append(item)  
    return item_list        
print(append_item(1))  
print(append_item(2))  
print(append_item(3))  
