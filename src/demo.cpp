#include <st7735s/Display.h>
#include <st7735s/Object.h>

int main()
{
	ST7735s::Display display;

	RG::EvilCar first_evil_car;
	RG::EvilCar second_evil_car;
	RG::PlayerCar player_car;

	second_evil_car.setX(90);

	first_evil_car.move(ST7735s::Object::vertical, ST7735s::Object::direction_down);
	second_evil_car.move(ST7735s::Object::vertical, ST7735s::Object::direction_down);

	display.addObject(&first_evil_car);
	display.addObject(&second_evil_car);
	display.addObject(&player_car);

	display.connect(player_car.need_exit(), &display, ST7735s::Display::exit);

	return display.exec();
}