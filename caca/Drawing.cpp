#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <dwmapi.h>
#include "Drawing.h"
#include <thread>
#include <xlocmon>
#include <dwmapi.h>

bool test;
bool escapejail;

#include  <iostream>
#define address_CPed 0x76F3B8

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

template<typename T>
inline T* ptr_add(T* cped, uint32_t n) noexcept {
	char* ptr = (char*)cped;
	ptr += n;
	return (T*)ptr;
};



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

uintptr_t GetPlayerBaseAddress()
{
	return rpm<uintptr_t>(GetModuleBaseAddress(processID, L"gta_sa.exe") + address_CPed);
}

#include <vector>

DWORD GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets) {
	DWORD addr = ptr;
	for (int i = 0; i < offsets.size(); ++i) {
		addr = *(DWORD*)addr;
		addr += offsets[i];
	}
	return addr;
}

bool fly;
float cum = 0.0f;
bool isInvincible = false;
bool bStat;
bool term = false;
uintptr_t moduleBase;
bool pMoney = false;
bool pWantedLevelPoints;
bool dar = false;
bool nospread = false;
bool wallhack = false;
bool teleport = false;
bool BoomAllCloseVehicles = false;
bool jetpeck = false;
#define address_Money 0xB7CE50
#define adderss_Muni  0xB7CE54
#define adderss_Muni12  0xBAA430
#define offset_HEALTH 0x540
#define ARMOUR 0x548
#define offset_WEAPONSLOT_0 0x5A0
#define offset_WEAPONSLOT_2 0x5D8
#define offset_TOTAL_PISTOL_AMMO 0x5E4
bool thacar = false;
bool imp = false;
bool ped = false;
bool isCrazyClr = false;
bool muni = false;
bool hel = false;
bool random = false;
bool armur = false;
bool run = false;
bool speedy = false;
bool value;
HWND hwnd = NULL;

DWORD* Balls = (DWORD*)0xB6F5F0;
DWORD* Balls2 = (DWORD*)0xB6F3B8;

void ILuvAcTeleport(float x, float y, float z, DWORD rot_matrix)
{

	if (*Balls == NULL && *Balls2 == NULL)
		return;

	BYTE* ptrPlayerStatus = (BYTE*)((*Balls) + 0x530);

	if (*ptrPlayerStatus != 50)
	{
		DWORD* ptrPlayerXYZ = (DWORD*)((*Balls) + 0x14);
		DWORD* ptrPlayerX = (DWORD*)((*ptrPlayerXYZ) + 0x30);
		DWORD* ptrPlayerY = (DWORD*)((*ptrPlayerXYZ) + 0x34);
		DWORD* ptrPlayerZ = (DWORD*)((*ptrPlayerXYZ) + 0x38);
		DWORD* ptrPlayerRot = (DWORD*)((*ptrPlayerXYZ) + 0x0 + 0x2C);

		*ptrPlayerX = x;
		*ptrPlayerY = y;
		*ptrPlayerZ = z;
		*ptrPlayerRot = rot_matrix;
	}
	else
	{
		if (*Balls2)
		{
			float* xSpeed = (float*)((*Balls2) + 68);
			float* ySpeed = (float*)((*Balls2) + 72);
			float* zSpeed = (float*)((*Balls2) + 76);
			float* xSpin = (float*)((*Balls2) + 80);
			float* ySpin = (float*)((*Balls2) + 84);
			float* zSpin = (float*)((*Balls2) + 88);

			*xSpeed = 0.0f;
			*ySpeed = 0.0f;
			*zSpeed = 0.0f;
			*xSpin = 0.0f;
			*ySpin = 0.0f;
			*zSpin = 0.0f;
		}
		DWORD* ptrVehicleXYZ = (DWORD*)((*Balls2) + 0x14);
		DWORD* ptrVehicleX = (DWORD*)((*ptrVehicleXYZ) + 0x30);
		DWORD* ptrVehicleY = (DWORD*)((*ptrVehicleXYZ) + 0x34);
		DWORD* ptrVehicleZ = (DWORD*)((*ptrVehicleXYZ) + 0x38);
		DWORD* ptrVehicleRot = (DWORD*)((*ptrVehicleXYZ) + 0x0 + 0x2C);

		*ptrVehicleX = x;
		*ptrVehicleY = y;
		*ptrVehicleZ = z;
		*ptrVehicleRot = rot_matrix;
	}
}

bool GetCords;

char szCoords[256];

char* GetPlayerCoordinates()
{
	if (*Balls == NULL)
		return 0;

	DWORD* ptrPlayerXYZ = (DWORD*)((*Balls) + 0x14);
	DWORD* ptrPlayerX = (DWORD*)((*ptrPlayerXYZ) + 0x30);
	DWORD* ptrPlayerY = (DWORD*)((*ptrPlayerXYZ) + 0x34);
	DWORD* ptrPlayerZ = (DWORD*)((*ptrPlayerXYZ) + 0x38);
	DWORD* ptrPlayerRot = (DWORD*)((*ptrPlayerXYZ) + 0x0 + 0x2C);

	std::cout << "\nptrPlayerX" << *ptrPlayerX;
	std::cout << "\nptrPlayerY" << *ptrPlayerY;
	std::cout << "\nptrPlayerZ" << *ptrPlayerZ;
	std::cout << "\nptrPlayerROT" << *ptrPlayerRot;

	//sprintf(szCoords, "X: %d, Y: %d, Z: %d, Rot: %d", *ptrPlayerX, *ptrPlayerY, *ptrPlayerZ, *ptrPlayerRot);
	return szCoords;
}


float GetCurrentX() {
	if (*Balls == NULL)
		return 0;

	DWORD* ptrPlayerXYZ = (DWORD*)((*Balls) + 0x14);
	DWORD* ptrPlayerX = (DWORD*)((*ptrPlayerXYZ) + 0x30);

	return float(*ptrPlayerX);
}


float GetCurrentY() {
	if (*Balls == NULL)
		return 0;

	DWORD* ptrPlayerXYZ = (DWORD*)((*Balls) + 0x14);
	DWORD* ptrPlayerY = (DWORD*)((*ptrPlayerXYZ) + 0x34);

	return float(*ptrPlayerY);
}

float GetCurrentZ() {
	if (*Balls == NULL)
		return 0;

	DWORD* ptrPlayerXYZ = (DWORD*)((*Balls) + 0x14);
	DWORD* ptrPlayerZ = (DWORD*)((*ptrPlayerXYZ) + 0x38);

	return float(*ptrPlayerZ);
}

void Drawing::Draw()
{
	if (isActive())
	{


		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin("", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		{
			moduleBase = (uintptr_t)GetModuleHandle(NULL);


			if (armur) {
				wpm(100.0f, GetPlayerBaseAddress() + ARMOUR);
			}

			if (run) {
				int* runnybabby = (int*)GetPointerAddress(moduleBase + 0x1591A0, { 0x17C });
				*runnybabby = 50;
			}

			if (hel) {
				float* hel = (float*)GetPointerAddress(moduleBase + 0x17333C, { 0x588 });
				*hel = 1221;
			}

			if (muni) {
				int* muni = (int*)GetPointerAddress(moduleBase + 0x6488B8, { 0x38C, 0x264, 0xC, 0x160, 0x480, 0xB4 });
				*muni = 13333337;
			}


			if (speedy) {
				int* tary = (int*)GetPointerAddress(moduleBase + 0x15C1E0, { 0x160 });
				*tary = 3779805176;
			}

			if (GetCords) {
				std::cout << "AAA";
				GetPlayerCoordinates();
				GetCords = false;
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
				DWORD CCar = *(DWORD*)0xB6F980;
				*(DWORD*)(CCar + 1192) = 0x5;
			}

			if (BoomAllCloseVehicles) {
				
			}
			
			if (fly) {

				BYTE* ptrPlayerStatus = (BYTE*)((*Balls) + 0x530);

				DWORD* ptrPlayerXYZ = (DWORD*)((*Balls) + 0x14);
				DWORD* ptrPlayerX = (DWORD*)((*ptrPlayerXYZ) + 0x30);
				DWORD* ptrPlayerY = (DWORD*)((*ptrPlayerXYZ) + 0x34);
				DWORD* ptrPlayerZ = (DWORD*)((*ptrPlayerXYZ) + 0x38);

				DWORD* CARptrPlayerXYZ = (DWORD*)((*Balls2) + 0x14);
				DWORD* CARptrPlayerX = (DWORD*)((*CARptrPlayerXYZ) + 0x30);
				DWORD* CARptrPlayerY = (DWORD*)((*CARptrPlayerXYZ) + 0x34);
				DWORD* CARptrPlayerZ = (DWORD*)((*CARptrPlayerXYZ) + 0x38);

				if (*ptrPlayerStatus != 50)
				{
				


					if (GetAsyncKeyState(VK_SPACE)) {
	
						ILuvAcTeleport(float(*ptrPlayerX), float(*ptrPlayerY), float(*ptrPlayerZ + 173633), 0);
					}

					if (GetAsyncKeyState(0x57)) {
						ILuvAcTeleport(float(*ptrPlayerX + ZValue), float(*ptrPlayerY), float(*ptrPlayerZ), 0);
					}


					if (GetAsyncKeyState(0x53)) {
						ILuvAcTeleport(float(*ptrPlayerX - ZValue), float(*ptrPlayerY), float(*ptrPlayerZ), 0);
					}


					if (GetAsyncKeyState(0x44)) {
						ILuvAcTeleport(float(*ptrPlayerX), float(*ptrPlayerY + ZValue), float(*ptrPlayerZ), 0);
					}


					if (GetAsyncKeyState(0x41)) {
						ILuvAcTeleport(float(*ptrPlayerX), float(*ptrPlayerY - ZValue), float(*ptrPlayerZ), 0);
					}
				}
				else {

					if (GetAsyncKeyState(VK_SPACE)) {

						ILuvAcTeleport(float(*CARptrPlayerX), float(*CARptrPlayerY), float(*CARptrPlayerZ + ZValue + 17000), 0);
					}

					if (GetAsyncKeyState(0x57)) {
						ILuvAcTeleport(float(*CARptrPlayerX + ZValue), float(*CARptrPlayerY), float(*CARptrPlayerZ), 0);
					}


					if (GetAsyncKeyState(0x53)) {
						ILuvAcTeleport(float(*CARptrPlayerX - ZValue), float(*CARptrPlayerY), float(*CARptrPlayerZ), 0);
					}


					if (GetAsyncKeyState(0x44)) {
						ILuvAcTeleport(float(*CARptrPlayerX), float(*CARptrPlayerY + ZValue), float(*CARptrPlayerZ), 0);
					}


					if (GetAsyncKeyState(0x41)) {
						ILuvAcTeleport(float(*CARptrPlayerX), float(*CARptrPlayerY - ZValue), float(*CARptrPlayerZ), 0);
					}
				}


				//if (GetA)
			}


			if (teleport) {
				ILuvAcTeleport(float(1148036875), float(3302538432), float(1096335360), 0);
				teleport = false;
			}
			if (dar) {
				DWORD CCar = *(DWORD*)0xB6F980;
				*(float*)(CCar + 1216) = 0.0f; // Health of the Car sir
			}

			if (imp) {
				DWORD CCar = *(DWORD*)0xB6F980;
				*(float*)(CCar + 1216) = 60.0f; // Health of the Car sir
			}

			if (wallhack) {
				DWORD ped = *(DWORD*)0xB7CD98;
				*(float*)(ped + 0x2C) = (float)value;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
			}

			if (escapejail) {
				ILuvAcTeleport(float(1147988971), float(3302567894), float(1096343490), 0);
				escapejail = false;
			}

			if (test)
			{
				BYTE* niiga = (BYTE*)0x96914A;
				*niiga = 1;
			}
			else
			{
				BYTE* niiga = (BYTE*)0x96914A;
				*niiga = 0;
			}

			if (jetpeck) {
				DWORD addr = 0x439600;
				__asm call addr;
			}

			if (random) {
				wpm(1, GetPlayerBaseAddress() + offset_WEAPONSLOT_0);
				wpm(22, GetPlayerBaseAddress() + offset_WEAPONSLOT_2);
				wpm(15, GetPlayerBaseAddress() + offset_TOTAL_PISTOL_AMMO);
			}

			if (term) {
				unsigned int* termal = (unsigned int*)0xC402B9;

				*termal = bStat;
			}

			if (nospread) {
				// I will keep resetting
				float* spread = (float*)0xB7CDC8;
				*spread = 0.0f; 

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}

			ImGui::Text("Aim");
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
			ImGui::Checkbox("Invicibile Car", &imp);
			ImGui::Checkbox("Set car on fire", &dar);
		//	ImGui::Checkbox("Teleport to a random location [BETA, DETECTED]", &teleport);
	//		ImGui::Checkbox("Bomb All The Closed Vehicles", &BoomAllCloseVehicles);
			ImGui::Checkbox("Place Bomb", &thacar);
			ImGui::Checkbox("Thermal", &term);
			ImGui::Checkbox("Push all closest peds to you [+ and -]", &ped);
			ImGui::Checkbox("speedhack [bike]", &speedy);		
			ImGui::Checkbox("Fly", &fly);
			ImGui::SliderFloat("Fly Speed", &ZValue, 0, 5000);
			ImGui::SliderFloat("Z Multiply", &XValue, 0, 1000000);
			if (ImGui::Button("Escape Jail")) {
				escapejail = true;
			}

			ImGui::Spacing();

			ImGui::Text("Health/Money/Spawn [Risky]");
			ImGui::Checkbox("Health Giver", &hel);
			ImGui::Checkbox("Infinite Run", &run);
			ImGui::Checkbox("Money give [Broken]", &muni);
			ImGui::Checkbox("Spawn JetPack [Risk]", &jetpeck);
			ImGui::Checkbox("Fly", &fly);
		


		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
	}
