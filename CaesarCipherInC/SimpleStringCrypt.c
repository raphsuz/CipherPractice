#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(){
    int result = 1;
    int i;
    int string_count = 0;

    // 存放加密前字串
    char text[128] = {'\0'};
    // 存放加密後字串
    char cryptograph[128] = {'\0'};

    // 進入功能選單    
    while (1){
        // 功能引導文字
        printf("此爲簡易訊息加密程式，旨在實現基本加密演算法 - 凱撒密碼\n");
        printf("請輸入數字以進行本程式的功能：\n");
        printf("輸入數字「1」：將明文訊息加密，呈現加密後訊息。\n");
        printf("輸入數字「2」：對功能1的加密訊息進行解密，呈現明文訊息。\n");
        printf("輸入數字「3」：結束本程式。\n\n");
        scanf("%d", &result);

        // 功能1. 發送明文訊息進行加密
        if (result == 1){
            printf("請輸入要傳送的明文訊息： \n");
            scanf("%s", &text);
            string_count = strlen(text);
            for (i = 0; i < string_count; i++) {
                // 凱撒加密法 - 原始字位置如果爲 i，則偏移 i+5 
                cryptograph[i] = text[i] + i + 5;
            }
            cryptograph[i] = '\0';
            printf("進行加密後得到密文訊息：%s \n\n", cryptograph);
        }
        // 功能2. 將加密訊息解密成明文訊息
        else if (result == 2){
                string_count = strlen(text);
                for (i = 0; i < string_count; i++) {
                    // 凱撒加密法 - 解密時將偏移位置 
                    text[i] = cryptograph[i] - i - 5;                    
                }
                text[i] = '\0';
                printf("進行解密取得明文訊息：%s \n\n", text);
            }
        // 功能3. 結束本程式
        else{
            printf("請按任意鍵後結束本程式。");
            scanf("%s", &text);
            break;
        }

    }
    return 0;
}
