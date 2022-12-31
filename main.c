#include <stdio.h>
#include <stdlib.h>
#define DATACOUNT 20
#define DATACOUNT2X 40
// gcc main.c && chmod +x a.out && ./a.out t.jpg

// 將字串中的小寫字母轉換為大寫
void toUpperCase(char *str) {
    for (int i = 0; i < DATACOUNT2X; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

// 將所有單位元組的 hex 字串合併為一個字串
void hex2hexStr(char *hexStr, char (*data)[2]) {
    for (int i = 0; i < DATACOUNT; i++) {
        hexStr[i*2] = data[i][0];
        hexStr[i*2+1] = data[i][1];
    }
}

// 開始校對資料
int chkData(char *hexStr) {
    printf("%s\n", hexStr);
    return 0;
}

// 將要檢測的檔案頭部讀入到記憶體
int loadFile(char *filePath) {
    int i = 0;
    int nowData = EOF;
    char nowHex[3] = { '0', '0', '\0' };
    char data[20][2] = { EOF };
    char hexStr[DATACOUNT2X+1] = { '\0' };
    FILE *f;
    // int s[1] = {0};
    printf("Load: %s ...\n", filePath);
    f = fopen(filePath, "rb");
    if (!f) {
        printf("Load Fail: %s error\n", filePath);
        return -1;
    }
    printf("Data: ");
    for (i = 0; i < DATACOUNT; i++)
    {
        // fread(s, 1, 1, f);
        nowData = fgetc(f);
        if (nowData == EOF) {
            printf(" (END)");
            break;
        }
        sprintf(nowHex, "%02x", nowData);
        data[i][0] = nowHex[0];
        data[i][1] = nowHex[1];
    }
    fclose(f);
    hex2hexStr(hexStr, data);
    toUpperCase(hexStr);
    return chkData(hexStr);
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
