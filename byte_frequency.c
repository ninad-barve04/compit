#include <stdio.h>

#define BUFFER_SIZE (256)

int main(int argc, char const *argv[])
{
    // FILE *fp = fopen("compression.wav", "rb");

    // unsigned char buffer[BUFFER_SIZE];

    // /* Read in 256 8-bit numbers into the buffer */
    // size_t bytes_read = 0;
    // bytes_read = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, fp);
    // // Note: sizeof(unsigned char) is for emphasis

    // for (int i = 0; i < BUFFER_SIZE; i++) {
    //     printf("%hx - ", buffer[i]);
    // }


    // unsigned char c; int r;
    // while((c = getc(fp)) != EOF) {
    //     printf("%hx - ", c);
    // }

    FILE *fp = fopen("smallTest.ninad", "wb");

    unsigned char buffer[] = "aaaaaaaa";

    fwrite(buffer, sizeof(buffer), 1, fp);
    
    fclose(fp);

    return 0;
}

