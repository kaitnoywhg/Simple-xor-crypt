# "XOR Cipher Tool"

## Description
The XOR Cipher Tool encrypts the user-entered text using a random 16-character password generated from letters and numbers. The encryption and decryption operations are performed using a reversible XOR cipher (the same function is used for both operations). The password is stored in the "password.txt" file, and the encrypted data is stored in the "new.txt" file. When decryption is required, the user must enter the password that matches the stored password, and the data will be decrypted.


Features:The utility can also recover a forgotten password if the user knows the encryption method (XOR).

### Requirements
    * Windows operating system (due to `<Windows.h>` and `MAX_PATH`)
    * GCC (MinGW) or MSVC compiler
    * Standard C library
    
### How to Run
1. download the `crypt.c` file
2. open a terminal in the folder with the file
3. compile the program:
```bash
gcc crypt.c -o crypt.exe
```

```bash
crypt.exe
```
#### Usage Example
**Encryption:**

    Enter file name: data.txt
    1 - encrypt data
    2 - decrypt data
    3 - forgot password
    4 - exit
    1
Enter message: Hello, XOR!
Your password for future data decryption: hG7qLp9XzF2rT5nM

**After execution, the following files will be created:**

    * my_data.txt — original message
    * password.txt — generated password
    * new.txt — encrypted data (binary)

**Decryption:**

    Enter file name: data.txt
    2
    Enter password for data decryption: hG7qLp9XzF2rT5nM
    Decrypted data (text): Hello, XOR!
    
**Password Recovery**
    3
Enter the encryption method used: XOR
Your password: hG7qLp9XzF2rT5nM

## Code Explanation

**Connected libraries:**

    * <stdlib.h> — memory allocation, random number generation
    * <stdio.h> — file input/output
    * <time.h> — seed for the random number generator
    * <string.h> — string operations
    * <locale.h> — locale support (for Cyrillic)
    * <Windows.h> — Windows API (for MAX_PATH)
    
**Main functions:**

    * rad_pas() — generates a random password of a given length from a set of characters
    * crypty() — XOR encryption/decryption of data using a key
    * main() — the main logic of the program: menu, file operations, user interaction

**Input validation:**

    * checking the success of file opening
    * number of elements read/written by fread / fwrite
    * password match before decryption

**Key Limitations**

    * Maximum message length: 4095 characters
    * Password saved in plain text in password.txt (not for production use)
    * Windows-only (due to MAX_PATH)

### Important Notes
    * Security: The password is stored in plain text in password.txt. This is an educational example. Do not use it for real encryption of sensitive data.
    * Encoding: The program works with bytes, so it correctly handles any characters (UTF-8, Cyrillic, etc.) if the terminal supports them.
    * Platform: The code uses <Windows.h> (for MAX_PATH). For cross‑platform use, replace MAX_PATH with 260 or PATH_MAX.

## Author

kaitnoywhg

## License

This project is licensed under the MIT