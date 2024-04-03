import json
import os

LETTERS_IN_THE_ALPHABET = 26
lowercaseAlphabet = "abcdefghijklmnopqrstuvwxyz"
uppercaseAlphabet = lowercaseAlphabet.upper()

def loadEncryptionSystem(dir_path, plaintext_suffix) :
    config_path = os.path.join(dir_path, 'config.json') # path to file
    
    with open('config.json', 'r') as f : # open and reads file ( DO WE NEED TO CHECK IF OPEN? )
        loaded_text = json.load(f)
    
    configured_type = loaded_text.get('type') 
    configured_encrypt = loaded_text.get('encrypt') # DO WE NEED TO CHECK IF TEXTS ARE VALID?
    configured_key = loaded_text.get('key')
    
    if (configured_type == 'Caesar') :
        if (configured_encrypt == "True") :
            function_output = CaesarCipher.encrypt(configured_key)
        else : # must be decrypt
            function_output = CaesarCipher.decrypt(configured_key)
    else : # must be vigenere
        if (configured_encrypt == "True") :
            function_output = VigenereCipher.encrypt(configured_key)
        else : # must be decrypt
            function_output = VigenereCipher.decrypt(configured_key)
    
    for file in os.listdir(dir_path):
        if file.endswith('plaintext_suffix'):
            file_path = os.path.join(dir_path, file)
            with open(file_path, 'r') as f:
                text = f.read()
            encrypted_text = function_output #(text, configured_key, configured_encrypt) << why did i write this?
            if configured_encrypt :
                new_file = file.replace(f'.{plaintext_suffix}', '.enc')
            else :
                file.replace('.enc', f'.{plaintext_suffix}')
            
            new_file_path = os.path.join(dir_path, new_file)
            with open(new_file_path, 'w') as f:
                f.write(encrypted_text)
    
class CaesarCipher :
    
    def __init__(self, key):
        self.key = key % 26
    
    def encrypt(self, messageToEncrypt) :
        encryptedMessage = ""
        for letter in messageToEncrypt :
            if letter.islower() == True :
                for i in range (0, len(lowercaseAlphabet)) :
                    if lowercaseAlphabet[i] == letter :
                        encryptedMessage += lowercaseAlphabet[i+self.key]
            elif letter.isupper() == True :
                for i in range (0, len(uppercaseAlphabet)) :
                    if uppercaseAlphabet[i] == letter :
                        encryptedMessage += uppercaseAlphabet[i+self.key]
            else :
                encryptedMessage += letter
        return encryptedMessage
    
    def decrypt(self, messageToDecrypt) :
        self.key *= (-1)
        decryptedMessage = self.encrypt(messageToDecrypt)
        self.key *= (-1)
        return decryptedMessage
    
    def key_shift(self, delta) :
        self.key += delta
        
class VigenereCipher :
    
    def __init__(self, keys_list):
        for i in range(len(keys_list)) :
            self.keys_list[i] = keys_list[i] % 26
    
    def encrypt(self, messageToEncrypt) :
        encryptedMessage = ""
        for letter in messageToEncrypt :
            if letter.islower() == True :
                for i, k in zip(range, self.keys_list) :
                    if lowercaseAlphabet[i] == letter :
                        encryptedMessage += lowercaseAlphabet[i+self.keys_list[k]]
            elif letter.isupper() == True :
                for i, k in zip(range, self.keys_list) :
                    if lowercaseAlphabet[i] == letter :
                        encryptedMessage += lowercaseAlphabet[i+self.keys_list[k]]
            else :
                encryptedMessage += letter
        return encryptedMessage
    
    def decrypt(self, messageToDecrypt) :
        for i in range(len(self.keys_list)) :
            self.keys_list[i] *= (-1)
        decryptedMessage = self.encrypt(messageToDecrypt)
        for i in range(len(self.keys_list)) :
            self.keys_list[i] *= (-1)
        return decryptedMessage