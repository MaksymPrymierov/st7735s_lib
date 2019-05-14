#include <st7735s/Display.h>

int main()
{
	ST7735s::Display display;

	display.fill(0x3333);

	return display.exec();
}