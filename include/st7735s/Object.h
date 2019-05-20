#pragma once

#include <cstdint>

namespace ST7735s
{
        class Object
        {
        public:
                static constexpr const bool vertical = true;
                static constexpr const bool horizontal = false;
                static constexpr const bool direction_up = true;
                static constexpr const bool direction_down = false;

                Object() = default;
                ~Object() = default;

                struct data 
                {
                        uint8_t x;
                        uint8_t y;
                        uint8_t w;
                        uint8_t h;
                        uint16_t size;
                        uint16_t color;
                        uint16_t *buffer;
                        bool move = false;
                        bool move_dir  = false;
                        bool owerflow = false;
                        bool owerflow_ctl = true;
                        bool intersection = false;
                        bool moved = false;
                };

                inline uint8_t getX() const { return d.x; }
                inline uint8_t getY() const { return d.y; }
                inline uint8_t getW() const { return d.w; }
                inline uint8_t getH() const { return d.h; }
                inline uint16_t getSize() const { return d.size; }
                inline uint16_t getColor() const { return d.color; }
                inline uint16_t* getBuffer() const { return d.buffer; }
                inline bool getMove() const { return d.move; }
                inline bool getMoveDir() const { return d.move_dir; }
                inline bool isMoved() const { return d.moved; }
                inline bool isOwerflow() const { return d.owerflow; }
                inline bool isOwerflowCtl() const { return d.owerflow_ctl; }
                inline uint8_t getOriginX() const { return origin_x; }
                inline uint8_t getOriginY() const { return origin_y; }
                inline uint8_t isIntersection() const { return d.intersection; }

                inline void move(bool move, bool move_dir) { d.move = move; d.move_dir = move_dir; d.moved = true; }
                inline void stop() { d.moved = false; }
                inline void setX(uint8_t x) { d.x = x; }
                inline void setY(uint8_t y) { d.y = y; }
                inline void setW(uint8_t w) { d.w = w; }
                inline void setH(uint8_t h) { d.h = h; }
                inline void setSize(uint16_t size) { d.size = size; }
                inline void setColor(uint16_t color) { d.color = color; }
                inline void setOwerflow(bool owerflow) { d.owerflow = owerflow; }
                inline void setOwerflowCtl(bool ctl) { d.owerflow_ctl = ctl; }
                inline void setOriginX(uint8_t x) { origin_x = x; }
                inline void setOriginY(uint8_t y) { origin_y = y; }
                inline void setIntersection(bool intersection) { d.intersection = intersection; }

                inline void resetOwerflow() { d.x = origin_x; d.y = origin_y; d.owerflow = false; }

                void fill(uint16_t color);

                virtual void update();

        protected:
                inline void allocBuffer() { d.buffer = new uint16_t[d.size]; }


        private:
                uint8_t origin_x;
                uint8_t origin_y;
                data d;
        };

        class Block : public Object
        {
        public:
                Block(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
                ~Block();
        };

        class Car : public Object
        {
        public:
                Car(uint8_t x, uint8_t y, uint16_t color);
                ~Car() = default;

                void update();

        private:
                void draw();
        };
};
