import string


def substitution_cipher(text, cipher_dict):
    result = ""
    
    for char in text:
      
        if char.isupper():
            result += cipher_dict.get(char.lower(), char).upper()
       
        elif char.islower():
            result += cipher_dict.get(char, char)
        
        else:
            result += char
    
    return result


alphabet = string.ascii_lowercase


permuted_alphabet = "qwertyuiopasdfghjklzxcvbnm"


encrypt_dict = {original: permuted for original, permuted in zip(alphabet, permuted_alphabet)}
decrypt_dict = {permuted: original for original, permuted in zip(alphabet, permuted_alphabet)}


text = "Hello, World!"


encrypted_text = substitution_cipher(text, encrypt_dict)
print(f"Encrypted: {encrypted_text}")


decrypted_text = substitution_cipher(encrypted_text, decrypt_dict)
print(f"Decrypted: {decrypted_text}")
