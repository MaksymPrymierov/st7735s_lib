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

RG::PlayerCar::PlayerCar() : Object()
{
        setX(50);
        setOriginX(50);
        setY(119);
        setOriginY(119);
        setW(30);
        setH(40);
        setSize(30 * 40);
        setColor(0x543a);
        setOwerflowCtl(false);

        allocBuffer();

        fill(0x543a);
}

void RG::PlayerCar::update()
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

        if (isIntersection()) {
                _need_exit = true;
        } 
}

RG::EvilCar::EvilCar() : ST7735s::Object()
{
        setX(10);
        setOriginX(10);
        setY(0);
        setOriginY(0);
        setW(30);
        setH(40);
        setSize(30 * 40);
        setColor(0x3f14);
        
        allocBuffer();

        fill(0x3f14);
}

void RG::EvilCar::resetOwerflow()
{
        int roadId = rand() % 3;

        switch (roadId) {
        case 0:
                setX(10);
                break;
        case 1:
                setX(50);
                break;
        case 2:
                setX(90);
                break;
        default:
                setX(getOriginX());
                break;
        }

        setY(getOriginY());
        setOwerflow(false);
}
