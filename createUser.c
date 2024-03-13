#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include <time.h>

int main() {
    char username[100], password[50], secretKey[17], command[800];
    const char characters[] = "234567ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int size, i, status;

    size = sizeof(characters) - 1;

    // You will define the name and password for the new user
    printf("\n\n -- Create user --\n");
    printf("\n      Username: ");
    scanf("%s",&username);
    fflush(stdin);

    printf("      Password: ");
    scanf("%s",&password);
    fflush(stdin);

    // The 'secretKey' will be generated automatically
    srand(time(NULL));

    for(i=0;i<16;i++){
        secretKey[i] = characters[rand() % size];
    }

    secretKey[16] = '\0';
    printf("\n\n -> Save your secret key in Google Authenticator or on the website indicated at readme.md!!!");
    printf("\n -> Your secret key: %s\n\n", secretKey);

    // The command below will create the user
    sprintf(command,"sudo useradd -m -p $(openssl passwd -6 %s) %s",password, username);

    // Verify if the user was successfully created
    status = system(command);

    if (status == -1) {
        printf("Error creating the user!\n");
        return 1;
    }

    // Saves the 'username' and 'secretKey' to a .txt file for later searches."
    FILE *file = fopen("secretKeyList.txt","a");
    if (file == NULL) {
        printf("\n Error creating the file!");
        return 1;
    }

    fprintf(file, "username: %s secretKey: %s\n", username, secretKey);
    fclose(file);
    return 0;
}


