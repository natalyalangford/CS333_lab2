/*
Author: Natalya Langford 
Due: Jan 28 2025
CS333 Lab 1 - Caesar Cipher  
    - Works on all printable ASCII characters (space to ~)
    - Reads input from stdin, shifts the characters by shift amount 
      (a value >= 0 and <= 95) & print encrypted text back to stdout 

Command line options: 
    -e: Encrypt stdin and print to stdout (default)
    -d: Decrypt stdin and print to stdout 
    -s #: Amount by which characters are shifted 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#ifndef FALSE 
# define FALSE 0
#endif // FALSE
#ifndef TRUE
# define TRUE 1
#endif // TRUE 

#define OPTIONS "eds:"
#define MIN_SHIFT 0  // min shift value
#define MAX_SHIFT 95  // nax shift value 
// caesar cipher implementation works on all printable ASCII chars (space to ~)
#define ASCII_MIN 32  // space
#define ASCII_MAX 126  // tilde ~
#define ASCII_RANGE (ASCII_MAX - ASCII_MIN + 1) // range of ASCII printable characters
#define BUF_SIZE 1024 // input buffer 

void decryption(int shift);
void encryption(int shift);
void caesar_cipher(char * line, int shift, int d_flag);

int main(int argc, char * argv[]) 
{
    int opt; // option
    int shift = 3;   // if shift value not given, default is 3
    int d_flag = FALSE;  // decryption flag
    int e_flag = FALSE;  // encryption flag 

    // handle -e -d -s # command-line options (read input happens after getopt)
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) 
    {
        switch (opt) 
        {
            // case -e: encrypt stdin and print to stdout 
            case 'e':
                e_flag = TRUE; 
                break;
            // case -d: decrypt stdin and print to stdout 
            case 'd':
                d_flag = TRUE;
                break;
            // case -s #: shifts characters with given amount 
            case 's':
                shift = atoi(optarg);  // convert to integer
                // shift amount entered must not be less than 0 and not greater than 95
                if (shift < MIN_SHIFT || shift > MAX_SHIFT) 
                {
                    fprintf(stderr, "ERROR: Shift value must be >= %d and <= %d \n", MIN_SHIFT, MAX_SHIFT);
                    exit(EXIT_FAILURE);
                }
                break;
            // default case
            default:
                fprintf(stderr, "USAGE ERROR. QUITTING PROGRAM...\n");
                exit(EXIT_FAILURE);
        }
    }

    // time to perform encryption or decryption 
    if (d_flag)
        decryption(shift);
    else if (e_flag)
        encryption(shift);
    // default to encryption if neither -d or -e are given 
    else 
        encryption(shift);

    return 0;
}

/*  Encryption Function
    Purpose: This function simply gets the user input to process encryption 
    Arguments: 
        - shift: integer -> shift value 
*/
void encryption(int shift) 
{
    char buffer[BUF_SIZE];
    // read input for encryption
    while (fgets(buffer, BUF_SIZE, stdin)) 
    {
        caesar_cipher(buffer, shift, FALSE);
        printf("%s", buffer); // print encrypted text back to user 
    }
}

/*  Decryption Function
    Purpose: This function simply gets the user input to process decryption 
    Arguments: 
        - shift: integer -> shift value 
*/
void decryption(int shift) 
{
    char buffer[BUF_SIZE];
    // read input for decryption
    while (fgets(buffer, BUF_SIZE, stdin)) 
    {
        caesar_cipher(buffer, shift, TRUE);
        printf("%s", buffer); // print decrypted text back to user 
    }
}

/*  Caesar Cipher Function
    Purpose: This function encrypts or decrypts the users input using caesar cipher
        - processes characters within ASCII range (space to ~) 
        - shifts characters by specfied amount (default set to 3 shifts)
        - void return type
    Arguments: 
        - line: pointer to a char -> contains text to be encrypted/decrypted 
        - shift: integer -> shift value
        - d_flag: integer -> 0/FALSE (Encryption) & 1/TRUE(Decryption)
*/
void caesar_cipher(char * line, int shift, int d_flag) 
{
    // loop through user input, all non printing characters ignored 
    for (int i = 0; line[i] != '\0'; i++) 
    {
        // proceed to encrypt/decrypt if character is ASCII printable 
        if (line[i] >= ASCII_MIN && line[i] <= ASCII_MAX) 
        {
            if (d_flag)
                // decrypt -> shift character backwards 
                line[i] = ((line[i] - ASCII_MIN - shift + ASCII_RANGE) % ASCII_RANGE) + ASCII_MIN;
            else
                // encrypt ->shift character forwards 
                line[i] = ((line[i] - ASCII_MIN + shift) % ASCII_RANGE) + ASCII_MIN;
        }
    }
}
