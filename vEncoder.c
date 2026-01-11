#include <stdio.h>
#include <string.h>

#define XOR_KEY 0xAA

int encodeFile(const char *fileWillEncoded, const char *outputFile);
int decodeFile(const char *fileWillDecoded, const char *outputFile);

int main(int argc, char **argv) {
    if (argc < 3){
        fprintf(stderr, "Usage: %s [-d] <file> <output>!", argv[0]);
        return 1;
    }

    int returnCode;

    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);

    if (strcmp(argv[1], "-d") == 0) {
        returnCode = decodeFile(argv[2], argv[3]);
    } else {
        returnCode = encodeFile(argv[1], argv[2]);
    }

    return returnCode;
}

int encodeFile(const char *fileWillEncoded, const char *outputFile) {
    FILE *fileWillEncodedStream;
    FILE *outputFileStream;
    int c;

    fileWillEncodedStream = fopen(fileWillEncoded, "rb");
    if (!fileWillEncodedStream) {
        perror("Input file");
        return 1;
    }

    outputFileStream = fopen(outputFile, "wb");
    if (!outputFileStream) {
        perror("Output file");
        fclose(fileWillEncodedStream);
        return 1;
    }

    while ((c = fgetc(fileWillEncodedStream)) != EOF) {
        unsigned char encodedChar = (unsigned char)c;
        encodedChar ^= XOR_KEY;

        if (fwrite(&encodedChar, 1, 1, outputFileStream) != 1) {
            perror("Write error");
            break;
        }
    }

    fclose(fileWillEncodedStream);
    fclose(outputFileStream);

    return 0;
}

int decodeFile(const char *fileWillDecoded, const char *outputFile) {
    FILE *fileWillDecodedStream;
    FILE *outputFileStream;
    unsigned char c;

    fileWillDecodedStream = fopen(fileWillDecoded, "rb");
    if (!fileWillDecodedStream) {
        perror("Input file");
        return 1;
    }

    outputFileStream = fopen(outputFile, "wb");
    if (!outputFileStream) {
        perror("Output file");
        fclose(fileWillDecodedStream);
        return 1;
    }

    while (fread(&c, sizeof(char), 1, fileWillDecodedStream) == 1) {
        unsigned char decodedChar = (unsigned char)c;
        decodedChar ^= XOR_KEY;

        if (fwrite(&decodedChar, 1, 1, outputFileStream) != 1) {
            perror("Write error");
            break;
        }
    }

    fclose(fileWillDecodedStream);
    fclose(outputFileStream);

    return 0;
}
