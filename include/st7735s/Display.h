#pragma once

#include <array>
#include <queue>
#include <cstdint>
#include <cstring>
#include <iostream>

#include <st7735s/Object.h>

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
                void fillImage(const char* path);
                void setPixel(uint8_t x, uint8_t y, uint16_t color);
                void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
                void loadImg(const char *path);
                inline void addObject(Object *obj) { objects.push_back(obj); }
                static void exit(Display* disp) 
                {
                        disp->need_exit = true;
                }
                void connect(bool* sygnal, Display* disp, void (*handler)(Display*));
                void backgroundMove(uint32_t len);
                void updateBackground();
                int update();

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

                struct handler_sygnal
                {
                        bool *sygn;
                        Display *disp;
                        void (*handler)(Display*);
                };

                bool error = false;
                bool need_exit = false;

                int frame_buffer_file;
                std::string_view frame_buffer_path;
                uint16_t frame_buffer[size_buffer];
                uint16_t background[size_buffer];

                std::array<int, size_buffer> object_metadata;

                std::queue<struct paint_task> paint_queue;
                std::vector<struct handler_sygnal> sygnals;
                std::vector<ST7735s::Object*> objects;

                void drawUpdate();
                void eventUpdate();
                void drawObjects();
                void updateObjects();
                void setObjMetaData(uint8_t x, uint8_t y, int data);
                int getObjMetaData(uint8_t x, uint8_t y);

                // handlers
                void handlerSygnals();
        };
};