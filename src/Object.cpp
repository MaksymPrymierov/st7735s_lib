#include <st7735s/Object.h>

#include <cstring>

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