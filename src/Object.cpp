#include <st7735s/Object.h>

#include <cstring>
#include <cstdio>
#include <iostream>

void ST7735s::Object::update()
{
        // noop
}

ST7735s::Block::Block(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) : Object()
{
        setX(x);
        setOriginX(x);
        setY(y);
        setOriginY(y);
        setW(w);
        setH(h);
        setSize(uint16_t(w) * uint16_t(h));
        setColor(color);
        
        allocBuffer();

        fill(color);
}

ST7735s::Block::~Block()
{
        delete [] getBuffer();
}

void ST7735s::Object::fill(uint16_t color)
{
        d.color = color;
        memset(d.buffer, color, d.size * 2);
}

ST7735s::Car::Car(uint8_t x, uint8_t y, uint16_t color) : Object()
{
        setX(x);
        setOriginX(x);
        setY(y);
        setOriginY(y);
        setW(30);
        setH(40);
        setSize(30 * 40);
        setColor(color);

        allocBuffer();

        fill(color);
}

void ST7735s::Car::update()
{
        int8_t dir;
        FILE* file = fopen("/sys/class/mpu6050/direction_y", "r");

        fscanf(file, "%hhd", &dir);

        if (dir == -1) {
                stop();
        } else if (dir) {
                move(horizontal, direction_down);
        } else {
                move(horizontal, direction_up);
        }

        fclose(file);
}