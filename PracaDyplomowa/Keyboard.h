#pragma once
class Keyboard
{
private:
	Keyboard(void);
public:
	static bool *keys;
	static void KeyboardInit();
	static void KeyboardKill();
	static bool isPressed(unsigned char key);
	static bool isPressed(int key);
	static bool isPressedAndReleased(unsigned char key);
	static bool isPressedAndReleased(int key);
	static void KeyPressFunc(unsigned char key, int x, int y);
	static void KeyUpFunc(unsigned char key, int x, int y);
	static void KeySpecPressFunc(int key, int x, int y);
	static void KeySpecUpFunc(int key, int x, int y);
	~Keyboard(void);
};

