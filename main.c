#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct img
{
    int width, height;
    int channels;
    unsigned char *pixels;
};

struct img img_default()
{
    struct img img = {
        .width = 1920,
        .height = 1080,
        .channels = 3,
    };
    img.pixels = malloc(img.width * img.height * img.channels);
    return img;
}

#define DIST "."
#define NAME "/igen_image.png"

int main(int argc, char **argv)
{
    char *path;
    if (argc == 2)
    {
        if ((path = malloc(strlen(NAME) + strlen(argv[1]) + 1)) != NULL)
        {
            path[0] = '\0';
            strcat(path, argv[1]);
            strcat(path, NAME);
        }
        else
        {
            fprintf(stderr, "malloc failed!\n");
        }
    }
    else
    {
        if ((path = malloc(strlen(NAME) + strlen(DIST) + 1)) != NULL)
        {
            path[0] = '\0';
            strcat(path, DIST);
            strcat(path, NAME);
        }
        else
        {
            fprintf(stderr, "malloc failed!\n");
        }
    }

    srand((unsigned int)time(NULL));
    struct img img = img_default();

    unsigned char color1[3], color2[3];
    for (int i = 0; i < 3; i++)
    {
        color1[i] = rand() % 256;
        color2[i] = rand() % 256;
    }

    float angle = ((float)rand() / RAND_MAX) * 2.0f * M_PI;
    float dx = cos(angle);
    float dy = sin(angle);

    float max_len = sqrtf(img.width * img.width + img.height * img.height) / 2.0;

    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width; x++)
        {
            int index = (y * img.width + x) * img.channels;

            float cx = x - img.width / 2.0;
            float cy = y - img.height / 2.0;

            float t = (cx * dx + cy * dy) / max_len;
            t = (t + 1.0) / 2.0;

            if (t < 0.0)
                t = 0.0;
            if (t > 1.0)
                t = 1.0;

            img.pixels[index + 0] = (unsigned char)((1.0 - t) * color1[0] + t * color2[0]);
            img.pixels[index + 1] = (unsigned char)((1.0 - t) * color1[1] + t * color2[1]);
            img.pixels[index + 2] = (unsigned char)((1.0 - t) * color1[2] + t * color2[2]);
        }
    }

    int res = stbi_write_png(path, img.width, img.height, img.channels, img.pixels, img.width * img.channels);
    printf("Image save result: %d\n", res);

    free(img.pixels);

    printf("Done!\n");

    return 0;
}
