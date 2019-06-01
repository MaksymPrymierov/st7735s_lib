#include <mh_fmd/Buzzer.h>
#include <fcntl.h>
#include <unistd.h>

MH_FMD::Buzzer::Buzzer()
{
    isActive = false;
    buzzer_path = "/proc/buzzer/mh_fmd";
    if (buzzer_file == -1) {
                std::cerr << "File cannot be opened\n" << std::endl;
                err = true;
        }
}

MH_FMD::Buzzer::~Buzzer()
{
    if (isActive){
        silence();
    }
}

int MH_FMD::Buzzer::write_to_proc(char val)
{
    buzzer_file = open(buzzer_path.data(), O_WRONLY);
    if (err) {
        std::cerr << "Executable error\n" << std::endl;
        return -1;
    }
    
    write(buzzer_file, &val, 1);
    close(buzzer_file);
    
    isActive = ~isActive;
    
    return 0;
}

void MH_FMD::Buzzer::silence()
{
    write_to_proc('0');
}

void MH_FMD::Buzzer::beep(int t)
{
    
    write_to_proc('1');
    
    sleep(t);
    
    silence();

}
