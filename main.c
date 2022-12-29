#include <stdio.h>
#include <stdlib.h>

int loadFile(char *filePath) {
    // int s[1] = {0};
    printf("Load: %s ...\n", filePath);
    FILE *f = fopen(filePath, "rb");
    if (!f) {
        printf("Load Fail: %s error\n", filePath);
        return -1;
    }
    fclose(f);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 0;
    }
    return loadFile(argv[1]);
}