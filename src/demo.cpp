#include <st7735s/Display.h>
#include <st7735s/Object.h>
#include <mh_fmd/Buzzer.h>

#include <thread>

int main()
{
        MH_FMD::Buzzer buzzer;
    
	ST7735s::Display display;

	display.fillImage("resources/road.bin");
    
        buzzer.noise_time(1);
    
        buzzer.run();

	RG::EvilCar first_evil_car;
	RG::EvilCar second_evil_car;
	RG::PlayerCar player_car;

	second_evil_car.setX(90);
	second_evil_car.setY(100);

	first_evil_car.move(ST7735s::Object::vertical, ST7735s::Object::direction_down);
	second_evil_car.move(ST7735s::Object::vertical, ST7735s::Object::direction_down);

	display.addObject(&first_evil_car);
	display.addObject(&second_evil_car);
	display.addObject(&player_car);

	player_car.fillImage("resources/player.bin");
	first_evil_car.fillImage("resources/evil.bin");
	second_evil_car.fillImage("resources/evil2.bin");

	display.connect(player_car.need_exit(), &display, ST7735s::Display::exit);

	display.fillImage("resources/start.bin");
	display.updateBackground();
	display.update();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	display.fillImage("resources/road.bin");

	if(!display.exec()) {
                buzzer.run();
        }
    
        return 0;
}
