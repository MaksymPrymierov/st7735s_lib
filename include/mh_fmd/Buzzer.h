#pragma once

#include <iostream>

namespace MH_FMD
{
    class Buzzer
    {
        
    public:
        
        Buzzer();
        ~Buzzer();
        
        inline void noise_time(int t) { time = t; }
        inline void run() { beep(time); }
        inline void stop() { silence(); }
        
    private:
        
        int buzzer_file;
        int time;
        
        bool activate;
        bool isActive;
        bool err = false;
        
        std::string_view buzzer_path;
        
        void beep(int t);
        void silence();
        int write_to_proc(char val);
        
    };
    
};
