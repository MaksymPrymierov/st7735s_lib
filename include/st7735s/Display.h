#pragma once

#include <array>
#include <queue>
#include <cstdint>
#include <cstring>

namespace ST7735s
{
        class Display
        {
        public:
                static constexpr const uint16_t widht = 128;
                static constexpr const uint16_t height = 160;
                static constexpr const uint16_t size_buffer = widht * height;

                Display();
                ~Display();

                int exec();
                void fill(uint16_t color);
                void setPixel(uint8_t x, uint8_t y, uint16_t color);
                void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
                void loadImg(const char *path);

        private:
                enum paint_function : uint8_t
                {
                        fill_screen, set_pixel, fill_rect
                };

                struct paint_task
                {
                        paint_function function;
                        uint16_t color;
                        uint8_t x;
                        uint8_t y;
                        uint8_t w;
                        uint8_t h;
                };

                bool error = false;
                int frame_buffer_file;
                std::string_view frame_buffer_path;
                uint16_t frame_buffer[size_buffer];

                std::queue<struct paint_task> paint_queue;

                void drawUpdate();
                void eventUpdate();
                void _fill(uint16_t color);
                void _setPixel(uint8_t x, uint8_t y, uint16_t color);
                void _fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
        };
};