#include <st7735s/Object.h>

#include <cstring>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

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

void ST7735s::Object::fillImage(const char *path)
{
        int image_file = open(path, O_RDONLY);

        read(image_file, d.buffer, d.size * 2);

        close(image_file);
}

RG::PlayerCar::PlayerCar() : Object()
{
        setX(50);
        setOriginX(50);
        setY(119);
        setOriginY(94);
        setW(20);
        setH(44);
        setSize(20 * 44);
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
                fillImage("resources/boomcar.bin");
        }

        ++i;
        if (!(i % 2000)) {
                setSpeed(getSpeed() + 1);
        }
}

RG::EvilCar::EvilCar() : ST7735s::Object()
{
        setX(10);
        setOriginX(10);
        setY(0);
        setOriginY(0);
        setW(20);
        setH(44);
        setSize(20 * 44);
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

void RG::EvilCar::update()
{
        ++i;
        if (!(i % 2000)) {
                setSpeed(getSpeed() + 1);
        }
}