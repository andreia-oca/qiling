#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage ./crack_me <password>\n");
        return -1;
    }

    char* correct_passwd = "l33tcode";

    if (strncmp(argv[1], correct_passwd, strlen(correct_passwd))) {
        printf("Incorrect flag.\n");
        return 1;
    } else {
        printf("Congratulations!\n");
    }

    return 0;
}