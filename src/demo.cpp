#include <st7735s/Display.h>
#include <st7735s/Object.h>

int main()
{
	ST7735s::Display display;

	display.fillImage("resources/road.bin");

	RG::EvilCar first_evil_car;
	RG::EvilCar second_evil_car;
	RG::PlayerCar player_car;

	second_evil_car.setX(90);
	second_evil_car.setY(60);

	first_evil_car.move(ST7735s::Object::vertical, ST7735s::Object::direction_down);
	second_evil_car.move(ST7735s::Object::vertical, ST7735s::Object::direction_down);

	player_car.setSpeed(2);

	display.addObject(&first_evil_car);
	display.addObject(&second_evil_car);
	display.addObject(&player_car);

	player_car.fillImage("resources/player.bin");
	first_evil_car.fillImage("resources/evil.bin");
	second_evil_car.fillImage("resources/evil2.bin");

	display.connect(player_car.need_exit(), &display, ST7735s::Display::exit);

	return display.exec();
}