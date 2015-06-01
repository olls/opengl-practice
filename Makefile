all:
	gcc `pkg-config --cflags glfw3` main.cpp -std=c++11 `pkg-config --static --libs glfw3` -lGLEW -DGLEW_STATIC && ./a.out
