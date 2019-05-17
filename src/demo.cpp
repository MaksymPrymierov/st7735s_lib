#include <st7735s/Display.h>
#include <st7735s/Object.h>

int main()
{
	ST7735s::Display display;

	ST7735s::Block block(20, 10, 30, 40, 0x5444);
	ST7735s::Block block1(51, 120, 30, 40, 0xA999);

	block.move(ST7735s::Object::vertical, ST7735s::Object::direction_down);
	block1.move(ST7735s::Object::vertical, ST7735s::Object::direction_up);

	display.addObject(&block);
	display.addObject(&block1);

	return display.exec();
}