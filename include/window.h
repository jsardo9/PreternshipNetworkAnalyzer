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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#define VECT std::vector

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

int simg_create(simg_img *img, int height, int width, char bg) {
    // printf("creating\n");
    img->height = height;
    img->width = width;
    int i, j;
    img->data = (simg_pixel ***)malloc(height * sizeof(simg_pixel *));
    for(i = height - 1; i >= 0; i--) {
        img->data[i] = (simg_pixel **)malloc(width * sizeof(simg_pixel *));
        for(j = 0; j < width; j++) {
            img->data[i][j] = (simg_pixel *)malloc(sizeof(simg_pixel));
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
int simg_read(simg_img *img) {
    FILE *fp;
    fp = fopen("window.simg", "rb");
    if(!fp) {
        printf("could not locate window.simg");
        return 0;
    }

    int i;
    int j;

    fread(&img->height, sizeof(int), 1, fp);
    fread(&img->width, sizeof(int), 1, fp);

    // printf("height: %d\t width: %d\n", img->height, img->width);
    // fflush(NULL);

    img->data = (simg_pixel ***)malloc(img->height * sizeof(simg_pixel *));
    for(i = 0; i < img->height; i++) {
        img->data[i] = (simg_pixel **)malloc(img->width * sizeof(simg_pixel *));
        for(j = 0; j < img->width; j++) {
            img->data[i][j] = (simg_pixel *)malloc(sizeof(simg_pixel));
            // fread(img->data[i][j], sizeof(char) + sizeof(int), 2, fp);
            fread(&img->data[i][j]->c, sizeof(char), 1, fp);
            fread(&img->data[i][j]->r, sizeof(int), 1, fp);
            // printf("char: %x  color: %d\n", img->data[i][j]->c, img->data[i][j]->r);
            // fflush(NULL);
        }
    }
    return 0;
}


int simg_print(simg_img *img) {
    int i, j;
    char c;
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

    return 0;
}

struct editorConfig {
    int width, height;
    struct termios orig_termios;
};

struct editorConfig E;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios);
}

void enableRawMode(){
    tcgetattr(STDIN_FILENO, &E.orig_termios);
    atexit(disableRawMode);

    struct termios raw = E.orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}

char editorReadKey() {
    int nread;
    char c;
    while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        printf("int");
        fflush(NULL);
        if(nread == -1) die("read");
    }
    return c;
}

void editorRefreshScreen(simg_img *img) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    simg_print(img);
}

void editorProcessKeypress(simg_img *img) {
    char c = editorReadKey();
    switch (c) {
        case 'p': //start/pause
            printf("paused");
            fflush(NULL);
            editorReadKey();
            editorRefreshScreen(img);
            break;

        case 'z': //start/pause
            printf("paused");
            fflush(NULL);
            editorReadKey();
            editorRefreshScreen(img);
            break;

        case 'q':
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);

            exit(0);
            break;
    }
}

simg_img img;
void initWindow() {
    simg_read(&img);
    E.height = img.height - 1;
    E.width = img.width - 1;
    editorRefreshScreen(&img);
}

typedef struct {
    int r;
    int bars;
}   Bar;

struct Flag{
    int start; // starting index of the spike
    VECT<int> latencies; // list of spiked latencies (use to calculate mean latency during the spike)
    int numLats = 0; // number of spiking latencies
    double avgLat; // the overage latency over the course of the spike

//-----------------Constructors-------------------------
//------------------------------------------------------
    Flag() : start(), latencies(), numLats(), avgLat() {}

    Flag(int startIn, std::vector<int> latsIn, int nLats) : start(startIn), latencies(latsIn), numLats(nLats), avgLat(0) {
      avgLatCalculation();
    }

//-----------------Methods-------------------------
//-------------------------------------------------
  void avgLatCalculation() {
    for (unsigned int i = 0; i < latencies.size(); ++i) {
      avgLat = avgLat + latencies[i] * 1/(double)numLats;
    }
  }

//-----------------Ostream Overload Function------------
    friend std::ostream& operator<<(std::ostream& output, const Flag& theFlag){
    	 output << "Start Index: " << theFlag.start << " | Mean Latency: " << theFlag.avgLat << " | #Latencies: " << theFlag.numLats << std::endl;
       return output;
    }

};

struct Period{
  int tPeriod; //Time period in which the period covers (in hrs)
  VECT<Flag> flags; //list of all flags which occurred during tPeriod

//-----------------Constructors-------------------------
//------------------------------------------------------
  Period() : tPeriod(), flags() {}

  Period(int tIn, std::vector<Flag> flagsIn) : tPeriod(tIn), flags(flagsIn) {}


//-----------------Ostream Overload Function------------
  friend std::ostream& operator<<(std::ostream& output, const Period& thePeriod){
    output << "Time Period: " << thePeriod.tPeriod << " hours" << " | Flags: " << std::endl;
    for (unsigned int i = 0; i < thePeriod.flags.size(); ++i) {
      output << thePeriod.flags[i];
    }
     return output;
  }
};

typedef struct {
    int time;
    int freq;
    int netf;
}   Info;

void updatePeriod(Period per, Info info) {
    char temp[20];

    sprintf(temp, "%02d", (int)per.flags.size());
    //flags
    simg_setpixel(&img, 12, 18, 3, temp[0]);
    simg_setpixel(&img, 13, 18, 3, temp[1]);

    //time

    sprintf(temp, "%02d", (info.time / 3600) % 12);
    //hours
    simg_setpixel(&img, 12, 17, 3, temp[0]);
    simg_setpixel(&img, 13, 17, 3, temp[1]);

    sprintf(temp, "%02d", (info.time / 60) % 60);
    //minutes
    simg_setpixel(&img, 15, 17, 3, temp[0]);
    simg_setpixel(&img, 16, 17, 3, temp[1]);

    //length
    sprintf(temp, "%02d", per.tPeriod);
    simg_setpixel(&img, 12, 16, 3, temp[0]);
    simg_setpixel(&img, 13, 16, 3, temp[1]);


    editorRefreshScreen(&img);
}

void updateBars(Bar bar) {
    //15 rows
    for (int y = 0; y < 14; y++) {
        for(int x = 0; x < 53; x++) {
            simg_setpixel(&img, 78 - x, 21 - y, img.data[20-y][78-x]->r, img.data[20-y][78-x]->c);
        }
    }
    for(int i = 0; i < 53; i++) {
        simg_setpixel(&img, 78 - i, 7, 0, (char)32);
    }
    for(int i = 0; i < bar.bars; i++) {
        simg_setpixel(&img, 26 + i, 7, bar.r, (char)35);
    }

    editorRefreshScreen(&img);
}

void updateFlag(Flag flag, Info info) {
    //average latency
    char temp[10];
    sprintf(temp, "%03.2f", flag.avgLat);

    simg_setpixel(&img, 13, 10, 3, temp[0]);
    simg_setpixel(&img, 14, 10, 3, temp[1]);
    simg_setpixel(&img, 15, 10, 3, temp[2]);
    //.
    simg_setpixel(&img, 17, 10, 3, temp[4]);
    simg_setpixel(&img, 18, 10, 3, temp[5]);

    //probability
    simg_setpixel(&img, 13, 9, 3, 'A');
    simg_setpixel(&img, 14, 9, 3, 'B');

    //length

    sprintf(temp, "%02d", (flag.numLats * info.freq / 60) % 60);
    //minutes
    simg_setpixel(&img, 13, 8, 3, temp[0]);
    simg_setpixel(&img, 14, 8, 3, temp[1]);

    sprintf(temp, "%02d", (flag.numLats * info.freq) % 60);
    //seconds
    simg_setpixel(&img, 16, 8, 3, temp[0]);
    simg_setpixel(&img, 17, 8, 3, temp[1]);


    editorRefreshScreen(&img);
}

void updateInfo(Info info) {
    //frequency
    char temp[10];
    sprintf(temp, "%d", info.freq);
    simg_setpixel(&img, 15, 2, 3, temp[1]);
    simg_setpixel(&img, 14, 2, 3, temp[0]);

    //total time
    sprintf(temp, "%02d", info.time / 86400);
    //days
    simg_setpixel(&img, 38, 2, 3, temp[0]);
    simg_setpixel(&img, 39, 2, 3, temp[1]);

    sprintf(temp, "%02d", (info.time / 3600)%24);
    //hours
    simg_setpixel(&img, 41, 2, 3, temp[0]);
    simg_setpixel(&img, 42, 2, 3, temp[1]);

    sprintf(temp, "%02d", (info.time / 60) % 60);
    //minutes
    simg_setpixel(&img, 44, 2, 3, temp[0]);
    simg_setpixel(&img, 45, 2, 3, temp[1]);

    //network faults
    sprintf(temp, "%d", info.netf);

    simg_setpixel(&img, 70, 2, 3, '0');
    simg_setpixel(&img, 71, 2, 3, temp[0]);

    editorRefreshScreen(&img);
}

void updateWin(Bar bar, Period per, Flag flag, Info info) {
    updatePeriod(per, info);
    updateFlag(flag, info);
    updateBars(bar);
    updateInfo(info);
}

#endif
