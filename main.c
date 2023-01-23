#include <stdio.h>
#include <stdlib.h>
#define COUNTSTART 20 // 從檔案前端讀取多少位元組
#define COUNTEND 20   // 從檔案末端讀取多少位元組
// gcc main.c && chmod +x a.out && ./a.out t.jpg && rm ./a.out

// 將字串中的小寫字母轉換為大寫
void toUpperCase(char *str, int count) {
    for (int i = 0; i < count; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

// 將所有單位元組的 hex 字串合併為一個字串
void hex2hexStr(char *hexStr, char (*data)[2]) {
    for (int i = 0; i < COUNTSTART; i++) {
        hexStr[i*2] = data[i][0];
        hexStr[i*2+1] = data[i][1];
    }
}

// 開始校對資料
int chkData(char *hexStart, char *hexEnd) {
    // printf("%s\n", hexStr);
    return 0;
}

// 將要檢測的檔案頭部讀入到記憶體
int loadFile(char *filePath) {
    int i = 0;
    int nowData = EOF;
    char nowHex[3] = { '0', '0', '\0' };
    char data[20][2] = { EOF };
    char hexStrS[COUNTSTART+COUNTSTART+1] = { '\0' };
    char hexStrE[COUNTEND+COUNTEND+1] = { '\0' };
    FILE *f;
    // int s[1] = {0};
    printf("FILE : %s\n", filePath);
    f = fopen(filePath, "rb");
    if (!f) {
        printf("Load Fail: %s\n", filePath);
        return -1;
    }
    printf("START: ");
    for (i = 0; i < COUNTSTART; i++)
    {
        // fread(s, 1, 1, f);
        nowData = fgetc(f);
        if (feof(f)) {
            printf("(END)");
            break;
        }
        sprintf(nowHex, "%02x", nowData);
        toUpperCase(nowHex, 2);
        data[i][0] = nowHex[0];
        data[i][1] = nowHex[1];
        printf("%s ", nowHex);
    }
    hex2hexStr(hexStrS, data);
    // toUpperCase(hexStrS, COUNTSTART+COUNTSTART);
    // printf("%s\n", hexStrS);
    if (i >= COUNTSTART) {
        printf("\nEND  : ");
        for (i = 0; i < COUNTEND; i++) {
            data[i][0] = EOF;
            data[i][1] = EOF;
        }
        fseek(f, 0-COUNTEND, SEEK_END);
        for (i = 0; i < COUNTEND; i++) {
            nowData = fgetc(f);
            if (feof(f)) {
                printf("(END)");
                break;
            }
            sprintf(nowHex, "%02x", nowData);
            toUpperCase(nowHex, 2);
            data[i][0] = nowHex[0];
            data[i][1] = nowHex[1];
            printf("%s ", nowHex);
        }
        hex2hexStr(hexStrE, data);
        // toUpperCase(hexStrE, COUNTEND+COUNTEND);
    }
    fclose(f);
    printf("\n");
    return chkData(hexStrS, hexStrE);
}

// 程式入口
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 0;
    }
    return loadFile(argv[1]);
}
