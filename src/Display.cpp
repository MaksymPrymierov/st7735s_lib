#include <st7735s/Display.h>

#include <iostream>
#include <chrono>
#include <thread>

#include <unistd.h>
#include <fcntl.h>

ST7735s::Display::Display()
{
        frame_buffer_path = "/dev/st7735s";
        if (frame_buffer_file == -1) {
                std::cerr << "File cannot be opened\n" << std::endl;
                error = true;
        }

        _fill(0x0000);
        object_metadata.fill(-1);
}

ST7735s::Display::~Display()
{
}

void ST7735s::Display::drawUpdate()
{
        struct paint_task buffer;
        while (!paint_queue.empty()) {
                buffer = paint_queue.front();
                paint_queue.pop();

                switch (buffer.function) {
                case paint_function::fill_screen:
                        _fill(buffer.color);
                        break;
                case paint_function::set_pixel:
                        _setPixel(buffer.x, buffer.y, buffer.color);
                        break;
                case paint_function::fill_rect:
                        _fillRect(buffer.x, buffer.y, buffer.w, buffer.h, buffer.color);
                        break;
                }
        }
}

int ST7735s::Display::exec()
{
        uint32_t speed = 1;
        for (uint32_t i = 1; true; ++i) {
                backgroundMove(speed);
                updateBackground();
                object_metadata.fill(-1);

                handlerSygnals();
                updateObjects();
                drawUpdate();
                drawObjects();

                frame_buffer_file = open(frame_buffer_path.data(), O_WRONLY);
                if (error) {
                        std::cerr << "Executable error\n" << std::endl;
                        return -1;
                }
                
                write(frame_buffer_file, frame_buffer, sizeof(frame_buffer));
                close(frame_buffer_file);

                if (need_exit) {
                        
                        screenEnroll(1);
                        
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        
                        return 0;
                }

                if (!(i % 2000)) {
                        ++speed;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
}

void ST7735s::Display::_fill(uint16_t color)
{
        memset(background, color, sizeof(background)); 
}

void ST7735s::Display::_setPixel(uint8_t x, uint8_t y, uint16_t color)
{
        if ((x >= widht) || (y >= height)) {
                return;
        }

        frame_buffer[x + widht * y] = color;
}

void ST7735s::Display::setObjMetaData(uint8_t x, uint8_t y, int data)
{
        if ((x >= widht) || (y >= height)) {
                return;
        }

        object_metadata[x + widht * y] = data;
}

int ST7735s::Display::getObjMetaData(uint8_t x, uint8_t y)
{
        if ((x >= widht) || (y >= height)) {
                return -1;
        }

        return object_metadata[x + widht * y];
}

 void ST7735s::Display::_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color)
 {
        if ((x >= widht) || (y >= height)) {
                return;
        }

        if ((x + w - 1) > widht) {
                w = widht - x;
        }

        if ((y + h - 1) > height) {
                h = height - y;
        }

        for (int i = 0; i < w; ++i) {
                for (int j = 0; j < h; ++j) {
                        frame_buffer[(x + widht * y) + (i + widht * j)] = color;
                }
        }
 }

 void ST7735s::Display::drawObjects()
 {
        for (std::vector<ST7735s::Object*>::size_type iter = 0; iter < objects.size(); ++iter) {
                for (int i = 0; i < objects[iter]->getW(); ++i) {
                        for (int j = 0; j < objects[iter]->getH(); ++j) {
                                _setPixel(objects[iter]->getX() + i, objects[iter]->getY() + j,
                                          objects[iter]->getBuffer()[i + objects[iter]->getW() * j]);
                                if (getObjMetaData(objects[iter]->getX() + i, objects[iter]->getY() + j) != -1) {
                                        objects[iter]->setIntersection(true);
                                }
                                setObjMetaData(objects[iter]->getX() + i, objects[iter]->getY() + j, int(iter));
                        }
                }
        }
 }

void ST7735s::Display::handlerSygnals()
{
        for (std::vector<ST7735s::Object*>::size_type iter = 0; iter < sygnals.size(); ++iter) {
                if (*sygnals[iter].sygn) {
                        sygnals[iter].handler(sygnals[iter].disp);
                        *sygnals[iter].sygn = false;
                }
        }
}

void ST7735s::Display::updateObjects()
{
        for (std::vector<ST7735s::Object*>::size_type iter = 0; iter < objects.size(); ++iter) {
                objects[iter]->update();

                if (objects[iter]->getMove() && objects[iter]->isMoved()) {
                        if (!objects[iter]->getMoveDir() &&
                            objects[iter]->getY() + objects[iter]->getSpeed() < height) {
                                objects[iter]->setY(objects[iter]->getY() + objects[iter]->getSpeed());
                        } else if (objects[iter]->getMoveDir() &&
                                   objects[iter]->getY() - objects[iter]->getSpeed() > 0) {
                                objects[iter]->setY(objects[iter]->getY() - objects[iter]->getSpeed());
                        } else {
                                objects[iter]->setOwerflow(true);
                                if (objects[iter]->isOwerflowCtl()) {
                                        objects[iter]->resetOwerflow();
                                }
                        }
                } else if (!objects[iter]->getMove() && objects[iter]->isMoved()) {
                        if (!objects[iter]->getMoveDir() &&
                             objects[iter]->getX() + objects[iter]->getSpeed() < widht) {
                                objects[iter]->setX(objects[iter]->getX() + objects[iter]->getSpeed());
                        } else if (objects[iter]->getMoveDir() &&
                                   objects[iter]->getX() - objects[iter]->getSpeed() > 0) {
                                objects[iter]->setX(objects[iter]->getX() - objects[iter]->getSpeed());
                        } else {
                                objects[iter]->setOwerflow(true);
                                if (objects[iter]->isOwerflowCtl()) {
                                        objects[iter]->resetOwerflow();
                                }
                        }
                }
        }
}

void ST7735s::Display::fill(uint16_t color) 
{
        struct paint_task task;

        task.function = paint_function::fill_screen;
        task.color = color;

        paint_queue.push(task);
}

void ST7735s::Display::setPixel(uint8_t x, uint8_t y, uint16_t color) 
{
        struct paint_task task;

        task.function = paint_function::set_pixel;
        task.x = x;
        task.y = y;
        task.color = color;

        paint_queue.push(task);
}

void ST7735s::Display::fillImage(const char* path)
{
        int image_file = open(path, O_RDONLY);

        read(image_file, background, sizeof(background));

        close(image_file);
}

void ST7735s::Display::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color)
{
        struct paint_task task;

        task.function = paint_function::fill_rect;
        task.x = x;
        task.y = y;
        task.w = w;
        task.h = h;
        task.color = color;

        paint_queue.push(task);
}
            
void ST7735s::Display::connect(bool* sygn, Display *disp, void (*handler)(Display*))
{
        struct handler_sygnal sygnal;

        sygnal.sygn = sygn;
        sygnal.handler = handler;
        sygnal.disp = disp;

        sygnals.push_back(sygnal);
}

void ST7735s::Display::updateBackground()
{
        memcpy(frame_buffer, background, sizeof(frame_buffer));
}

void ST7735s::Display::backgroundMove(uint32_t len)
{
        uint16_t line[widht * len];

        memcpy(line, (background + widht * height) - widht * len, sizeof(line));
        memmove(background + widht * len, background, sizeof(background) - sizeof(line));
        memcpy(background, line, sizeof(line));
        
}

void ST7735s::Display::screenEnroll(uint32_t len)
{
        uint16_t line[widht * len];
        uint16_t tmp_background[size_buffer];
        
        
        int image_file = open("resources/deathscreen.bin", O_RDONLY);

        read(image_file, tmp_background, sizeof(tmp_background));

        close(image_file);

        for(uint32_t i = 0; i < height/len; i++) {
            
            memcpy(line, tmp_background + widht * len * i, sizeof(line));
            memmove(background, background + widht * len, sizeof(background) - sizeof(line));
            memcpy((background + widht * height) - widht * len, line, sizeof(line));
            
            updateBackground();
            
            frame_buffer_file = open(frame_buffer_path.data(), O_WRONLY);
                
            write(frame_buffer_file, frame_buffer, sizeof(frame_buffer));
            close(frame_buffer_file);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
                        
        }
}
