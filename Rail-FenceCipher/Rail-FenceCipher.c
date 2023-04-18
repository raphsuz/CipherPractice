#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encrypt(const char* text, int key) {
    int length = strlen(text);
    char* encrypted = (char*)calloc(length + 1, sizeof(char));

    int index = 0;
    for (int k = 0; k < key; k++) {
        int step = 2 * (key - k - 1);
        for (int i = k; i < length; i += step) {
            encrypted[index++] = text[i];
            if (step == 0 || step == 2 * k) {
                step = 2 * (key - 1);
            } else {
                step = 2 * (key - 1) - step;
            }
        }
    }
    return encrypted;
}

char* decrypt(const char* encrypted, int key) {
    int length = strlen(encrypted);
    char* decrypted = (char*)calloc(length + 1, sizeof(char));

    int index = 0;
    for (int k = 0; k < key; k++) {
        int step = 2 * (key - k - 1);
        for (int i = k; i < length; i += step) {
            decrypted[i] = encrypted[index++];
            if (step == 0 || step == 2 * k) {
                step = 2 * (key - 1);
            } else {
                step = 2 * (key - 1) - step;
            }
        }
    }
    return decrypted;
}

int main() {
    int choice;
    printf("這是柵欄加密法 (Rail-Fence Cipher) \n請選擇操作：\n1. 加密\n2. 解密\n");
    scanf("%d", &choice);

    int key;
    printf("輸入密鑰（大於1的整數）：");
    scanf("%d", &key);
    getchar();

    char input[256];
    printf("輸入內容：");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // 移除換行符

    if (choice == 1) {
        char* encrypted = encrypt(input, key);
        printf("加密結果：%s\n", encrypted);
        free(encrypted);
    } else if (choice == 2) {
        char* decrypted = decrypt(input, key);
        printf("解密結果：%s\n", decrypted);
        free(decrypted);
    } else {
        printf("無效選擇\n");
    }

    return 0;
}
