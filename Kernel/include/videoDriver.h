#ifndef _VIDEODRIVER_H
#define _VIDEODRIVER_H

#include <stdint.h>


void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

void drawWhiteLine();

void drawRectangle(int x, int y,int width, int heigth, uint32_t color);

char getPixel(int x, int y);

char isSpaceEmpty(int x, int y);

void printChar(char c, int x, int y, uint32_t color);

void printStringPlace(char * string, int x, int y, uint32_t color);

void printString(char * string);

void printStringN(char * string, uint64_t length);

void printLn(char * string);

void moveOneLineUp();

void printStringColor(char * string, uint32_t color);

void printStringNColor(char * buffer, uint64_t length, uint32_t color);

void moveCursor();

void printRegisters();

void eraseCursor();

void clearScreen();

void toggleCursor();

void drawImage(const unsigned long int * image, int width, int height);

void drawBoard(int x, int y, uint32_t color);

void changeit();

void increaseEscale();
void decreaseEscale();
#endif