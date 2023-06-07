# SDES (Simplified Data Encryption Standard)
SDES (Simplified Data Encryption Standard) is a simplified version of the Data Encryption Standard (DES) algorithm. It is a symmetric-key block cipher that operates on small blocks of data. SDES is designed to provide basic encryption and decryption capabilities while being easy to understand and implement.

## Functionality
SDES provides the following functionality:
 1. Encryption: SDES takes an 8-bit plaintext and a 10-bit key as input and produces an 8-bit ciphertext as output.
 2. Decryption: SDES takes an 8-bit ciphertext and the same 10-bit key used for encryption as input and produces the original 8-bit plaintext as output.
 3. Key Generation: SDES generates two 8-bit keys from a given 10-bit key for use in encryption and decryption.

## Features
SDES offers the following features:
 1. Simplicity: SDES is a simplified version of the more complex DES algorithm, making it easier to understand and implement.
 2. Small Block Size: SDES operates on 8-bit blocks of data, allowing it to encrypt and decrypt small amounts of data efficiently.
 3. Symmetric Key: SDES uses the same key for both encryption and decryption, simplifying the key management process.
 4. Basic Encryption: SDES provides a basic level of encryption suitable for simple applications and educational purposes.
 5. Lightweight: SDES has a small code footprint and low computational requirements, making it suitable for resource-constrained environments.

## C++ Implementation
Run The `SDES.cpp` file Using Command:
```
g++ SDES.cpp -o SDES
````
Once the compilation process is successful, you can execute the compiled program. To run the program, use the following command:
```
./SDES.exe
```
### Output
![SDES_CPP_IMPLEMENTATION](https://github.com/Sahil-4555/Simplified_DataEncryption_Standard_SDES/blob/main/assets/sdes%20-%20c%2B%2B.png)

## Acknowledgment
SDES is based on the original Data Encryption Standard (DES) algorithm developed by IBM in the 1970s. The simplified version and the code implementation provided in this repository is developed by Me.
