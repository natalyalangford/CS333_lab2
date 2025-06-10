/*
Author: Natalya Langford 
Due: Jan 28 2025
CS333 Lab 1 - Decimation Cipher  
    - Also symmetric encryption algorithm -> encryption key same as decryption key
    - Key for decimation cipher is a single integer
    - About reading text from stdin & writing text to stdout

Command line options: 
    -e: Encrypt stdin and print to stdout (default)
    -d: Decrypt stdin and print to stdout 
    -k #: Number used to encrypt/decrypt input (must be greater than 0 and less than 10000)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define CHAR_SET 95       // num of printable ASCII characters
#define ASCII_MIN 32      // space     
#define ASCII_MAX 126     // tilde ~
#define DEFAULT_KEY 128   // default key

int mmi(int key, int modulus); // to find the modular inverse 
void decimation_cipher(int key, int decrypt_flag);

int main(int argc, char * argv[]) 
{
    int opt;  // option
    int key = DEFAULT_KEY;    // set to default decimation cipher key
    int flag = 0;     // 0 for encryption (default), 1 for decryption, 

    // handle -e -d -k # command-line options (read input happens after getopt)
    while ((opt = getopt(argc, argv, "edk:")) != -1) 
    {
        switch (opt) {         
            // case -e: encrypt stdin and print to stdout 
            case 'e':
                flag = 0;  // set flag for encryption
                break;
            // case -d: decrypt stdin and print to stdout 
            case 'd':
                flag = 1;  // set flag for decryption
                break;
            // case -k #: number used to encrypt/decrypt input 
            case 'k':
                key = atoi(optarg);  // convert to integer
                // validation - key must be between 1 & 9999
                if (key <= 0 || key >= 10000) 
                {
                    fprintf(stderr, "ERROR: Key must be less greater than 0 & less than 10000\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                fprintf(stderr, "USAGE ERROR. QUITTING PROGRAM...\n");
                exit(EXIT_FAILURE);
        }
    }

    // first check if key has a modular inverse, exit program if key is invalid
    if (mmi(key, CHAR_SET) == -1) 
    {
        fprintf(stderr, "ERROR: Key %d is invalid as no modular inverse exists\n", key);
        exit(EXIT_FAILURE);
    }

    // once key is validated, move on to decimation cipher
    decimation_cipher(key, flag);

    return 0;
}

/*  Decimation Cipher Function
    Purpose: This function performs the decimation cipher for encryption & decryption
    Arguments: 
        - key: integer -> key that must be greater than 0 & less than 10000
        - flag: integer -> 0 for encryption, 1 for decryption 
*/
void decimation_cipher(int key, int flag) 
{
    int inverse_key = mmi(key, CHAR_SET);  // get modular inverse
    int c; // store input characters

    while ((c = getchar()) != EOF) // process each character from standard input
    {
        if (c >= ASCII_MIN && c <= ASCII_MAX) // ensure character is printable 
        {
            // decryption
            if (flag)  
                // decrypt using modular inverse of the key
                c = ((c - ASCII_MIN) * inverse_key % CHAR_SET + CHAR_SET) % CHAR_SET + ASCII_MIN;
            // encryption 
            else 
                // encrypt with multiplying by the key and wrap within char_set [0, 94]
                c = ((c - ASCII_MIN) * key % CHAR_SET + CHAR_SET) % CHAR_SET + ASCII_MIN;
        }

        putchar(c);  // write to standard output
    }
}

/*  Modular Inverse Function - mmi
    Purpose: 
             - This function calculates the modular inverse of a given key with respect to size of the 
             character set (95). This function is required to decrypting the decimation cipher and to
             to check the key with for encryption.
             - If a key doesn't have a modular inverse, it cant be used for decryption
    Arguments: 
        - key: integer -> encryption key, must be greater than 0 & less than 10000
        - num_char: integer -> character set size (95) 

    NOTE: This function was given to us by Jesse
*/
int mmi(int key, int num_char) 
{
    key %= num_char;
    for (int i = 1; i < num_char; i++) 
    {
        if ((key * i) % num_char == 1) 
            return i;  // modular inverse found 
    }
    return -1;  // error state - an invalid key
}
