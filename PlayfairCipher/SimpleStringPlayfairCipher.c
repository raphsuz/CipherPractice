#include <stdio.h>
#include <string.h>

#define SIZE 5

// Preprocess text (remove spaces and convert to uppercase)
void preprocess(char *text) {
    int i, j = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ') {
            text[j++] = toupper(text[i]);
        }
    }
    text[j] = '\0';
}

// Function to generate the Playfair matrix
void generateMatrix(char *key, char matrix[SIZE][SIZE]) {
    int i, j, k = 0;
    char *alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int len = strlen(key);
    int used[26] = {0};
    // Fill in the key
    for (i = 0; i < len; i++) {
        if (!used[key[i] - 'A']) {
            matrix[k / SIZE][k % SIZE] = key[i];
            used[key[i] - 'A'] = 1;
            k++;
        }
    }
    // Fill in the rest of the alphabet
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            matrix[k / SIZE][k % SIZE] = alphabet[i];
            k++;
        }
    }
}

// Function to find the row and column of a character in the matrix
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of characters using the Playfair cipher
void encryptPair(char matrix[SIZE][SIZE], char a, char b, char *result) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);
    if (row1 == row2) {
        result[0] = matrix[row1][(col1 + 1) % SIZE];
        result[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        result[0] = matrix[(row1 + 1) % SIZE][col1];
        result[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        result[0] = matrix[row1][col2];
        result[1] = matrix[row2][col1];
    }
}

// Function to encrypt a plaintext using the Playfair cipher
void encrypt(char *plaintext, char *key, char *ciphertext) {
    char matrix[SIZE][SIZE];
    preprocess(plaintext);
    generateMatrix(key, matrix);
    int len = strlen(plaintext);
    int i, j = 0;
    for (i = 0; i < len; i += 2) {
        char pair[2];
        encryptPair(matrix, plaintext[i], plaintext[i+1], pair);
        ciphertext[j++] = pair[0];
        ciphertext[j++] = pair[1];
    }
    ciphertext[j] = '\0';
}

int main() {
    char plaintext[] = "HELLO WORLD";
    char key[] = "SECRET";
    char ciphertext[100];
    encrypt(plaintext, key, ciphertext);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

/*
This implementation takes a plaintext and a key as input, and outputs the corresponding ciphertext using the Playfair cipher algorithm. The 
preprocess
 function removes spaces and converts all characters to uppercase. The 
generateMatrix
 function generates the Playfair matrix based on the key. The 
findPosition
 function finds the row and column of a character in the matrix. The 
encryptPair
 function encrypts a pair of characters using the Playfair cipher. Finally, the 
encrypt
 function encrypts the entire plaintext by encrypting each pair of characters using the 
encryptPair
 function.
*/