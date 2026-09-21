#include <stdio.h>
#include <string.h>

void xorEncryptDecrypt(char *data, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] ^= key[i % keyLen];
    }
}

int main() {
    char choice[10];
    printf("Enter 'encrypt' or 'decrypt': ");
    scanf("%s", choice);

    if (strcmp(choice, "encrypt") == 0) {
        char message[256];
        char filename[256];
        char key[256];

        printf("Enter the string to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        printf("Enter the filename to save encrypted data: ");
        scanf("%s", filename);

        printf("Enter the encryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        xorEncryptDecrypt(message, key);
        fwrite(message, sizeof(char), strlen(message), file);

        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        char filename[256];
        char key[256];

        printf("Enter the filename to read encrypted data: ");
        scanf("%s", filename);

        printf("Enter the decryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        char buffer[256];
        size_t bytesRead = fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
        buffer[bytesRead] = '\0';

        fclose(file);

        xorEncryptDecrypt(buffer, key);
        printf("Decrypted data: %s\n", buffer);
    } else {
        printf("Invalid choice. Please enter 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    return 0;
}