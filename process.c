#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://cse4k12.org/encoding/decoding_bmp.pdf
struct Metadata {
    int width;
    int height;
    int channels;
    int id;
    long end_byte;
    int channel_size;
    char directory[128];
};

int main () {
    printf("a");
    clock_t elapsed = clock();

    struct Metadata ImageData;

    // read file
    
    FILE * filePointer = fopen("test4.bmp", "rb");
    
    fseek(filePointer, 0, SEEK_END); // seek end of file
    ImageData.end_byte = ftell(filePointer); // get file length
    fseek(filePointer, 0, SEEK_SET); // reset to front

    unsigned char * bytedata = (char *) malloc (ImageData.end_byte * sizeof(char));
    //unsigned char bytedata[] = dataptr;
    fread(bytedata, ImageData.end_byte, 1, filePointer);
    fclose(filePointer);
    // handle formatting errors
    if (bytedata[0] != 0x42 || bytedata[1] != 0x4D) {
        printf("Error: image type is not BMP. Program will now exit.");
        return (1);
    }
    printf("Start of pixel data:\n\n");
    

    
    ImageData.width = bytedata[0x12]+(bytedata[0x13]<<8)+(bytedata[0x14]<<16)+(bytedata[0x15]<<24); // parse 4-byte words into int
    ImageData.height = bytedata[0x16]+(bytedata[0x17]<<8)+(bytedata[0x18]<<16)+(bytedata[0x19]<<24); // parse 4-byte words into int

    ImageData.channels = 3; // r, g, b
    ImageData.channel_size = (bytedata[0x1C]+(bytedata[0x1D]<<8))/ImageData.channels/8; // bits/channel, -> bytes/channel
    int pixel_grid[ImageData.width][ImageData.height][ImageData.channels]; // create array for holding data in matrix
    
    /*// FIX ME ^^^^^ FIX ME ^^^^^ FIX ME ^^^^^ FIX ME ^^^^^ FIX ME ^^^^^ FIX ME ^^^^^ FIX ME ^^^^^ FIX ME ^^^^^ FIX ME ^^^^^ 
    // POINTER TOO LARGE, USE MALLOC


    printf("%dpx by %dpx, %d channel(s), %d byte(s)/channel/pixel\n", ImageData.width, ImageData.height, ImageData.channels, ImageData.channel_size);
    
    long current_byte = bytedata[0xA];
    long pixelCounter = 0;
    printf("Start of pixel data: %d\n", current_byte);

    for (int y = 0; y < ImageData.height; y++) {
        for (int x = 0; x < ImageData.width; x++) {
            for (int z = 0; z < ImageData.channels; z++) pixel_grid[x][y][z] = bytedata[current_byte++]; // for every subpixel of pixel, set to matrix
        }
    }

    printf("Image size: %d x %d\n", ImageData.width, ImageData.height);

    for (int y = 0; y < ImageData.height; y++) {
        for (int x = 0; x < ImageData.width; x++) {
            int avg = 0;
            for (int z = 0; z < ImageData.channels; z++) avg += pixel_grid[x][y][z];
            avg /= ImageData.channels;
            printf("%s", avg>170?"##":avg>85?"::":"  ");
        }
        printf("\n");
    }

    elapsed = clock() - elapsed;
    double timeUsed = (double)elapsed/CLOCKS_PER_SEC;
    printf("%f seconds elapsed.\n", timeUsed);*/
    free(bytedata);
}