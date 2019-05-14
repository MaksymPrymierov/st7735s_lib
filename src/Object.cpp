#include <st7735s/Object.h>

ST7735s::Block::Block(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) : Object()
{
        setX(x);
        setY(y);
        setW(w);
        setH(h);
        setSize(uint16_t(w) * uint16_t(h));
        setColor(color);
        
        allocBuffer();
}

ST7735s::Block::~Block()
{
        delete [] getBuffer();
}