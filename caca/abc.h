

#pragma once
#include "hacksalib.h"
#include <thread>
#define LOOP_DELAY 75
#define HOTKEY_DELAY 145
#define RUN_DELAY 10
#define RUN_DELAY_0 25
#define RUN_DELAY_1 50
#define RUN_DELAY_2 100
#define RUN_DELAY_3 150
#define RUN_DELAY_4 200
#define RUN_DELAY_5 250
#define RUN_DELAY_6 300

namespace cheats {

	static bool* isHandled;
	static HANDLE hCpy;
	void hotk();
	void loop();
	bool init_thread(HANDLE* hProc, bool* isHandled);
	static clock_t clk, clk1, _clk1, clk2, clk3, clk4, clk5, clk6, _clk6;
}

static class cPed {
private:
	DWORD baseDef = 0xB6F5F0,
		baseNew = 0x0;

	DWORD oCollision = 0x42,
		oHP = 0x540,
		oArmour = 0x548;

	BYTE vCollision = 252,
		vCollisionDef = 0;
public:
	bool isInvincible = false,
		isResetInvincible = false;
public:
	void loop();
	void translate();
}cP;

static class veh {
private:

	DWORD base = 0xB73458,
		oAccelerate = 0x20;
	BYTE vAccelerate = 0xFF;

	DWORD baseCrntPtr = 0xBA18FC,
		baseCrnt = 0x0,
		oPaint = 0x434;
	DWORD _Paint = 0xB4E3F0;
	

public:
	BYTE vPaint = 0;
	bool isAccelerate, isCrazyClr;
public:
	void loop();
	void translate();
}vh;