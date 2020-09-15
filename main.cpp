#include <iostream>

#include "WindowManager.h"

int main() {
	WindowManager wm = WindowManager(800, 500, "First window");
	int i = 0;
	while (!wm.update()) {
		i++;
		if (i == 600) {
			std::cout << "Going fullscreen" << std::endl;
			wm.fullscreen(true);
		}
	}
	return 0;
}