#include <stdio.h>
#include <string.h>

int main(void) {
    char *correct_passwd = "l33tcode";
    char passwd[16];

    printf("Type your password:\n");
    fgets(passwd, 16, stdin);

    if (strncmp(passwd, correct_passwd, strlen(correct_passwd))) {
        printf("Incorrect flag.\n");
        return 1;
    } else {
        printf("Congratulations!\n");
    }

    return 0;
}