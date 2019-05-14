#pragma once

#include <cstdint>
#include <st7735s/Display.h>

namespace ST7735s
{
        class Object
        {
        public:
                Object();
                ~Object();

                struct data 
                {
                        uint8_t x;
                        uint8_t y;
                        uint8_t w;
                        uint8_t h;
                        uint16_t size;
                        uint16_t color;
                        uint16_t *buffer;
                };

                inline uint8_t getX() const { return d.x; }
                inline uint8_t getY() const { return d.y; }
                inline uint8_t getW() const { return d.w; }
                inline uint8_t getH() const { return d.h; }
                inline uint16_t getSize() const { return d.size; }
                inline uint16_t getColor() const { return d.color; }
                inline uint16_t* getBuffer() const { return d.buffer; }

                inline void setX(uint8_t x) { d.x = x; }
                inline void setY(uint8_t y) { d.y = y; }
                inline void setW(uint8_t w) { d.w = w; }
                inline void setH(uint8_t h) { d.h = h; }
                inline void setSize(uint16_t size) { d.size = size; }
                inline void setColor(uint16_t color) { d.color = color; }

        protected:
                inline void allocBuffer() { d.buffer = new uint16_t[d.size]; }


        private:
                data d;
        };

        class Block : public Object
        {
        public:
                Block(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
                ~Block();
        };
};
