/*************************************
 * File name: NetworkFunctions.h
 * Authors: Jacob Sardo and Chase Brown
 * Emails: jsardo@nd.edu and cbrown54@nd.edu
 *
 * This file contains the functions to find flags
 * and split them up into their respective periods
 * ***********************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <termios.h>
#include <unistd.h>

typedef struct {
    char c;
    int r;
} simg_pixel;

typedef struct {
    int height;
    int width;
    simg_pixel ***data;
} simg_img;

typedef struct {
    int cx;
    int cy;
    char c;
    int r;
} simg_cursor;

enum simg_color_list {
    SIMG_RESET,
    SIMG_RED,
    SIMG_GREEN,
    SIMG_YELLOW,
    SIMG_BLUE,
    SIMG_MAGENTA,
    SIMG_CYAN
};

#include <stdio.h>
#include <stdlib.h>

int simg_create(simg_img *img, int height, int width, char bg) {
    // printf("creating\n");
    img->height = height;
    img->width = width;
    int i, j;
    img->data = malloc(height * sizeof(simg_pixel *));
    for(i = height - 1; i >= 0; i--) {
        img->data[i] = malloc(width * sizeof(simg_pixel *));
        for(j = 0; j < width; j++) {
            img->data[i][j] = malloc(sizeof(simg_pixel));
            img->data[i][j]->c = bg;
            img->data[i][j]->r = 0;
        }
    }
    return 0;
}


int simg_setpixel(simg_img *img, int x, int y, int color, char c) {
    // printf("setting pixel x: %d\ty: %d\tchar: %c\n", x, y, c);
    img->data[y][x]->c = c;
    img->data[y][x]->r = color;
    return 0;
}

int simg_write(simg_img *img, char *fn) {
    // printf("writing\n");
    FILE *fp;
    fp = fopen(fn, "wb");
    fwrite(&img->height, sizeof(int), 1, fp);
    fwrite(&img->width, sizeof(int), 1, fp);
    int i, j;
    for(i = 0; i < img->height; i++) {
        for(j = 0; j < img->width; j++) {
            fwrite(&img->data[i][j]->c, sizeof(char), 1, fp);
            fwrite(&img->data[i][j]->r, sizeof(int), 1, fp);
        }
    }

    return 0;
}
//good
int simg_read(simg_img *img, char *fn) {
    // printf("reading\n");
    FILE *fp;
    fp = fopen(fn, "rb");

    int i;
    int j;

    fread(&img->height, sizeof(int), 1, fp);
    fread(&img->width, sizeof(int), 1, fp);

    // printf("height: %d\t width: %d\n", img->height, img->width);

    img->data = malloc(img->height * sizeof(simg_pixel *));
    for(i = 0; i < img->height; i++) {
        img->data[i] = malloc(img->width * sizeof(simg_pixel *));
        for(j = 0; j < img->width; j++) {
            img->data[i][j] = malloc(sizeof(simg_pixel));
            // fread(img->data[i][j], sizeof(char) + sizeof(int), 2, fp);
            fread(&img->data[i][j]->c, sizeof(char), 1, fp);
            fread(&img->data[i][j]->r, sizeof(int), 1, fp);
            // printf("char: %x  color: %d\n", img->data[i][j]->c, img->data[i][j]->r);
        }
    }
    return 0;
}


int simg_print(simg_img *img, simg_cursor *cur) {
    int i, j;
    char c;
    int r;
    if (cur) {
        for(i = img->height - 1; i >= 0; i--) {
            for(j = 0; j < img->width; j++) {
                if(cur->cx == j && cur->cy == i) {
                    c = (char)(cur->c);
                    r = cur->r;
                }
                else {
                    c = (char)(img->data[i][j]->c);
                    r = img->data[i][j]->r;
                }
                switch (r) {
                    case 0:
                        printf("\033[0m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 1:
                        printf("\033[0;31m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 2:
                        printf("\033[0;32m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 3:
                        printf("\033[0;33m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 4:
                        printf("\033[0;34m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 5:
                        printf("\033[0;35m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 6:
                        printf("\033[0;36m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;
                }
            }
            printf("\n");
        }
    }
    else {
        for(i = img->height - 1; i >= 0; i--) {
            for(j = 0; j < img->width; j++) {
                c = (char)(img->data[i][j]->c);
                switch (img->data[i][j]->r) {
                    case 0:
                        printf("\033[0m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 1:
                        printf("\033[0;31m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 2:
                        printf("\033[0;32m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 3:
                        printf("\033[0;33m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 4:
                        printf("\033[0;34m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 5:
                        printf("\033[0;35m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;

                    case 6:
                        printf("\033[0;36m");
                        printf("%c", c);
                        printf("\033[0m");
                        break;
                }

            }
            printf("\n");
        }

    }
    return 0;
}

void printWin() {
    simg_img img;

    int read;
    read = simg_read(&img, "window.simg");
    // printf("read is: %d\n", read);

    int print;
    print = simg_print(&img, NULL);
}
