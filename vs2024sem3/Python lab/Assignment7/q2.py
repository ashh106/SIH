
def caesar_encrypt(text, shift):
    result = ""
    for char in text:
        if char.isalpha():
            shift_base = 65 if char.isupper() else 97
            result += chr((ord(char) - shift_base + shift) % 26 + shift_base)
        else:
            result += char 
    return result

def caesar_decrypt(ciphertext, shift):
    return caesar_encrypt(ciphertext, -shift)  


plaintext = "HELLO"
shift = 3
ciphertext = caesar_encrypt(plaintext, shift)
print("Encrypted:", ciphertext)
print("Decrypted:", caesar_decrypt(ciphertext, shift))
