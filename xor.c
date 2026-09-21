#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


void xorEncryptDecrypt(char *data, size_t dataLen, const char *key) {
    int keyLen = (int)strlen(key);
    for (size_t i = 0; i < dataLen; ++i) {
        data[i] ^= key[i % keyLen];
    }
}
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
    else {
        buffer[0] = '\0';
    }
}

int main() {
    char choice[10];
    printf("Enter 'encrypt' or 'decrypt': ");
    readLine(choice, sizeof(choice));

    if (strcmp(choice, "encrypt") == 0) {
        char message[256];
        char filename[256];
        char key[256];

        printf("Enter the string to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        printf("Enter the filename to save encrypted data: ");
        readLine(filename, sizeof(filename));

        printf("Enter the encryption key: ");
        readLine(key, sizeof(key));

        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }
        size_t msgLen = strlen(message);
        xorEncryptDecrypt(message, msgLen, key);
        fwrite(message, sizeof(char), msgLen, file);

        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        char filename[256];
        char key[256];

        printf("Enter the filename to read encrypted data: ");
		readLine(filename, sizeof(filename));

        printf("Enter the decryption key: ");
		readLine(key, sizeof(key));

        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        char buffer[256];
        size_t bytesRead = fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
        buffer[bytesRead] = '\0';

        fclose(file);

        xorEncryptDecrypt(buffer, bytesRead, key);
        printf("Decrypted data: %s\n", buffer); 
    } else {
        printf("Invalid choice. Please enter 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    return 0;
}