#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>

#include <stdio.h>
#include <chrono>
#include <thread>
#include <xlocmon>
#include <dwmapi.h>

#include "Drawing.h"

using namespace std;

bool test;
bool escapejail;

#define address_ped 0x76F3B8
#define address_money1 0xB7CE50
#define address_money2 0xB7CE54
#define address_money3 0xBAA430
#define offset_health 0x540
#define offset_armor 0x548
#define offset_weaponslot_0 0x5A0
#define offset_weaponslot_2 0x5D8
#define offset_total_pistol_ammo 0x5E4

ImVec2 Drawing::vWindowSize = { 500, 500 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

#include "abc.h"

uintptr_t GetModuleBaseAddress(DWORD, const wchar_t*);

DWORD processID;
HANDLE handleProcess;

float XValue;
float YValue;
float ZValue;

uintptr_t GetModuleBaseAddress(DWORD processId, const wchar_t* moduleName)
{
	uintptr_t moduleBaseAddress = NULL;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);

		if (Module32First(hSnap, &moduleEntry))
		{
			do
			{
				if (!_wcsicmp(moduleEntry.szModule, moduleName))
				{
					moduleBaseAddress = (uintptr_t)moduleEntry.modBaseAddr;
					break;
				}
			} while (Module32First(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);

	return moduleBaseAddress;
}

template <class T>
void wpm(T valueToWrite, DWORD addressToWrite)
{
	handleProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	WriteProcessMemory(handleProcess, (LPVOID)addressToWrite, &valueToWrite, sizeof(T), NULL);
}

template <class T>
T rpm(T addressToRead)
{
	T rpmBuffer;
	handleProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	ReadProcessMemory(handleProcess, (LPCVOID)addressToRead, &rpmBuffer, sizeof(T), NULL);
	return rpmBuffer;
}

template<typename T>
inline T* ptr_add(T* cped, uint32_t n) noexcept {
	char* ptr = (char*)cped;
	ptr += n;
	return (T*)ptr;
};

uintptr_t GetPlayerBaseAddress()
{
	return rpm<uintptr_t>(GetModuleBaseAddress(processID, L"gta_sa.exe") + address_ped);
}

#include <vector>

DWORD GetPointerAddress(DWORD ptr, vector<DWORD> offsets) {
	DWORD addr = ptr;
	for (int i = 0; i < offsets.size(); ++i) {
		addr = *(DWORD*)addr;
		addr += offsets[i];
	}
	return addr;
}

uintptr_t moduleBase;

bool fly;
float cum = 0.0f;
bool isInvincible = false;
bool bStat;
bool term = false;
bool pMoney = false;
bool pWantedLevelPoints;
bool dar = false;
bool nospread = false;
bool wallhack = false;
bool boom_all_close_cars = false;
bool jetpeck = false;
bool thacar = false;
bool cargod = false;
bool ped = false;
bool isCrazyClr = false;
bool moneygive = false;
bool health = false;
bool random = false;
bool armorgive = false;
bool run = false;
bool speedy = false;
bool value;

HWND hwnd = NULL;

DWORD* actor = (DWORD*)0xB6F5F0;
DWORD* car2 = (DWORD*)0xB6F3B8;

void teleport(float x, float y, float z, DWORD rot_matrix)
{
	if (*actor == NULL && *car2 == NULL)
		return;

	BYTE* playerStatus = (BYTE*)((*actor) + 0x530);

	if (*playerStatus != 50)
	{
		DWORD* playerXYZ = (DWORD*)((*actor) + 0x14);
		float* playerX = (float*)((*playerXYZ) + 0x30);
		float* playerY = (float*)((*playerXYZ) + 0x34);
		float* playerZ = (float*)((*playerXYZ) + 0x38);
		float* playerROT = (float*)((*playerXYZ) + 0x0 + 0x2C);

		*playerX = x;
		*playerY = y;
		*playerZ = z;
		*playerROT = rot_matrix;
	}
	else
	{
		if (*car2)
		{
			float* xSpeed = (float*)((*car2) + 68);
			float* ySpeed = (float*)((*car2) + 72);
			float* zSpeed = (float*)((*car2) + 76);
			float* xSpin = (float*)((*car2) + 80);
			float* ySpin = (float*)((*car2) + 84);
			float* zSpin = (float*)((*car2) + 88);

			*xSpeed = 0.0f;
			*ySpeed = 0.0f;
			*zSpeed = 0.0f;
			*xSpin = 0.0f;
			*ySpin = 0.0f;
			*zSpin = 0.0f;
		}
		DWORD* carXYZ = (DWORD*)((*car2) + 0x14);
		float* carX = (float*)((*carXYZ) + 0x30);
		float* carY = (float*)((*carXYZ) + 0x34);
		float* carZ = (float*)((*carXYZ) + 0x38);
		float* carROT = (float*)((*carXYZ) + 0x0 + 0x2C);

		*carX = x;
		*carY = y;
		*carZ = z;
		*carROT = rot_matrix;
	}
}

void marker_teleport()
{
	if ((*(int*)0xBA6774 != 0))
	{
		float mapPos[3];
		for (int i = 0; i < (0xAF * 0x28); i += 0x28)
		{
			if (*(short*)(0xBA873D + i) == 4611)
			{
				float* pos = (float*)(0xBA86F8 + 0x28 + i);
				mapPos[0] = *pos;
				mapPos[1] = *(pos + 1);
				mapPos[2] = ((float(__cdecl*)(float, float))0x569660)(mapPos[0], mapPos[1]);
				teleport(mapPos[0], mapPos[1], mapPos[2] + 2, 0);
			}
		}
	}
}

bool get_cords = false;
bool marker_tp = false;
bool just_tp = false;

char* get_player_coords()
{
	if (*actor == NULL)
		return 0;

	char szCoords[256];

	DWORD* playerXYZ = (DWORD*)((*actor) + 0x14);
	float* playerX = (float*)((*playerXYZ) + 0x30);
	float* playerY = (float*)((*playerXYZ) + 0x34);
	float* playerZ = (float*)((*playerXYZ) + 0x38);
	float* playerRot = (float*)((*playerXYZ) + 0x0 + 0x2C);

	cout << "\nplayerX" << *playerX;
	cout << "\nplayerY" << *playerY;
	cout << "\nplayerZ" << *playerZ;
	cout << "\nplayerROT" << *playerRot;

	//sprintf(szCoords, "X: %d, Y: %d, Z: %d, Rot: %d", *playerX, *playerY, *playerZ, *playerROT);
	return szCoords;
}

float get_cur_x() {
	if (*actor == NULL)
		return 0;

	DWORD* playerXYZ = (DWORD*)((*actor) + 0x14);
	float* playerX = (float*)((*playerXYZ) + 0x30);

	return float(*playerX);
}

float get_cur_y() {
	if (*actor == NULL)
		return 0;

	DWORD* playerXYZ = (DWORD*)((*actor) + 0x14);
	float* playerY = (float*)((*playerXYZ) + 0x34);

	return float(*playerY);
}

float get_cur_z() {
	if (*actor == NULL)
		return 0;

	DWORD* playerXYZ = (DWORD*)((*actor) + 0x14);
	float* playerZ = (float*)((*playerXYZ) + 0x38);

	return float(*playerZ);
}

void Drawing::Draw()
{
	if (isActive())
	{
		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
		ImGui::Begin("samp sdk", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		{
			moduleBase = (uintptr_t)GetModuleHandle(NULL);

			if (armorgive) {
				wpm(100.0f, GetPlayerBaseAddress() + offset_armor);
			}

			if (run) {
				int* runnybabby = (int*)GetPointerAddress(moduleBase + 0x1591A0, { 0x17C });
				*runnybabby = 50;
			}

			if (health) {
				float* hp = (float*)GetPointerAddress(moduleBase + 0x17333C, { 0x588 });
				*hp = 1221;
			}

			if (moneygive) {
				int* muni = (int*)GetPointerAddress(moduleBase + 0x6488B8, { 0x38C, 0x264, 0xC, 0x160, 0x480, 0xB4 });
				*muni = 13333337;
			}

			if (speedy) {
				int* tary = (int*)GetPointerAddress(moduleBase + 0x15C1E0, { 0x160 });
				*tary = 3779805176;
			}

			if (get_cords) {
				cout << "AAA";
				get_player_coords();
				get_cords = false;
			}

			if (ped) {
				if (GetAsyncKeyState(VK_ADD)) {
					cum += 5.0f;
				}
				else if (GetAsyncKeyState(VK_SUBTRACT)) {
					cum -= 5.0f;
				}

				DWORD* ped = (DWORD*)0xB7CD98;
				DWORD* pMatrix = (DWORD*)(*ped + 0x14);
				float* x = (float*)((*pMatrix) + 0x30);
				float* y = (float*)((*pMatrix) + 0x34);
				float* z = (float*)((*pMatrix) + 0x38);

				DWORD* next = nullptr;
				float hp = 0;
				float hundred = 0;

				for (int i = 0; i < 500; i++) {
					next = (DWORD*)(*ped + (0x7C4 * i));

					hundred = *(float*)(next + 0xE); // 0xE because i'm dereferencing it as a float type.

					if (i != 0 && hundred == 100.0f) {

						DWORD* player_info = (DWORD*)(next + 0x5);
						hp = *(float*)(next + 0x150);
						float* _x = (float*)(*player_info + 0x30);
						float* _y = (float*)(*player_info + 0x34);
						float* _z = (float*)(*player_info + 0x38);
						if (hp >= 0) {

							*_x = *x + cum + i;
							*_y = *y;
							*_z = *z;

						}
					}
				}
			}
			if (thacar) {
				DWORD car = *(DWORD*)0xB6F980;
				*(DWORD*)(car + 0x4A8) = 0x5;
			}

			if (boom_all_close_cars) {
			}

			if (fly) {
				BYTE* playerStatus = (BYTE*)((*actor) + 0x530);

				DWORD* playerXYZ = (DWORD*)((*actor) + 0x14);
				DWORD* playerX = (DWORD*)((*playerXYZ) + 0x30);
				DWORD* playerY = (DWORD*)((*playerXYZ) + 0x34);
				DWORD* playerZ = (DWORD*)((*playerXYZ) + 0x38);

				DWORD* carXYZ = (DWORD*)((*car2) + 0x14);
				DWORD* carX = (DWORD*)((*carXYZ) + 0x30);
				DWORD* carY = (DWORD*)((*carXYZ) + 0x34);
				DWORD* carZ = (DWORD*)((*carXYZ) + 0x38);

				if (*playerStatus != 50)
				{
					if (GetAsyncKeyState(VK_SPACE)) {
						teleport(float(*playerX), float(*playerY), float(*playerZ + 173633), 0);
					}

					if (GetAsyncKeyState(0x57)) {
						teleport(float(*playerX + ZValue), float(*playerY), float(*playerZ), 0);
					}

					if (GetAsyncKeyState(0x53)) {
						teleport(float(*playerX - ZValue), float(*playerY), float(*playerZ), 0);
					}

					if (GetAsyncKeyState(0x44)) {
						teleport(float(*playerX), float(*playerY + ZValue), float(*playerZ), 0);
					}

					if (GetAsyncKeyState(0x41)) {
						teleport(float(*playerX), float(*playerY - ZValue), float(*playerZ), 0);
					}
				}
				else {
					if (GetAsyncKeyState(VK_SPACE)) {
						teleport(float(*carX), float(*carY), float(*carZ + ZValue + 17000), 0);
					}

					if (GetAsyncKeyState(0x57)) {
						teleport(float(*carX + ZValue), float(*carY), float(*carZ), 0);
					}

					if (GetAsyncKeyState(0x53)) {
						teleport(float(*carX - ZValue), float(*carY), float(*carZ), 0);
					}

					if (GetAsyncKeyState(0x44)) {
						teleport(float(*carX), float(*carY + ZValue), float(*carZ), 0);
					}

					if (GetAsyncKeyState(0x41)) {
						teleport(float(*carX), float(*carY - ZValue), float(*carZ), 0);
					}
				}
			}

			if (just_tp) {
				teleport(float(0), float(0), float(10), 0);
				just_tp = false;
			}

			if (dar) {
				DWORD car = *(DWORD*)0xB6F980;
				*(float*)(car + 0x4C0) = 0.0f;
			}

			if (cargod) {
				DWORD car = *(DWORD*)0xB6F980;
				*(float*)(car + 0x4C0) = 1000.0f;
			}

			if (wallhack) {
			}

			if (escapejail) {
				teleport(float(1025), float(1), float(12), 0);
				escapejail = false;
			}

			if (test) {
				BYTE* niiga = (BYTE*)0x96914A;
				*niiga = 1;
			}
			else {
				BYTE* niiga = (BYTE*)0x96914A;
				*niiga = 0;
			}

			if (jetpeck) {
				typedef void (*fptr)(void);
				fptr jetpack = (fptr)0x439600;
				jetpack();
			}

			if (random) {
				wpm(1, GetPlayerBaseAddress() + offset_weaponslot_0);
				wpm(22, GetPlayerBaseAddress() + offset_weaponslot_2);
				wpm(15, GetPlayerBaseAddress() + offset_total_pistol_ammo);
			}

			if (term) {
				unsigned int* termal = (unsigned int*)0xC402B9;
				*termal = bStat;
			}

			if (nospread) {
				// I will keep resetting
				float* spread = (float*)0xB7CDC8;
				*spread = 0.0f;
				this_thread::sleep_for(chrono::milliseconds(1));
			}

			if (marker_tp) {
				marker_teleport();
				marker_tp = false;
			}

			ImGui::Text("Weapon");
			ImGui::Checkbox("No Spread", &nospread);
			ImGui::Checkbox("Gun Slots Bug", &random);
			ImGui::Spacing();

			ImGui::Text("ESP");
			ImGui::Checkbox("ESP", &wallhack);
			if (wallhack == true) {
				ImGui::Spacing();
				ImGui::Text("\n Soon.");
			}
			ImGui::Spacing();
			ImGui::Text("Exploits");
			ImGui::Checkbox("Car Godmode", &cargod);
			ImGui::Checkbox("Blow up the car", &dar);
			//ImGui::Checkbox("Teleport to a random location [BETA, DETECTED]", &just_tp);
			//ImGui::Checkbox("Bomb All The Closed Vehicles", &boom_all_close_cars);
			ImGui::Checkbox("Place Bomb", &thacar);
			ImGui::Checkbox("Thermal", &term);
			ImGui::Checkbox("Push all closest peds to you [+ and -]", &ped);
			ImGui::Checkbox("Speedhack [bike]", &speedy);
			ImGui::Checkbox("Fly", &fly);
			ImGui::SliderFloat("Fly Speed", &ZValue, 0, 5000);
			ImGui::SliderFloat("Z Multiply", &XValue, 0, 1000000);
			if (ImGui::Button("Escape Jail")) {
				escapejail = true;
			}

			ImGui::Spacing();

			ImGui::Text("Health/Money/Spawn [Risky]");
			ImGui::Checkbox("Health Giver", &health);
			ImGui::Checkbox("Infinite Run", &run);
			ImGui::Checkbox("Money give [Broken]", &moneygive);
			ImGui::Checkbox("Spawn Jetpack [Risk]", &jetpeck);
			ImGui::Checkbox("Marker Teleport", &marker_tp);
			ImGui::Checkbox("Fly", &fly);
		}
		ImGui::End();
	}

#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
#endif
}
