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

DWORD processIDA;
HANDLE handleProcessA;

float XValue;
float YValue;
float ZValue;

#ifdef STATICLIB1_EXPORTS
#define STATICLIB1_API __declspec(dllexport)
#else
#define STATICLIB1_API __declspec(dllimport)
#endif

#include <Windows.h>
#include <string>



namespace ACI25 {
	void init();
	void MouseMoveTo(int x, int y);
	void ErasePEHeaderFromMemory();
	HWND WindowCreature(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
		int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
	bool wishit(int vKey);
	LRESULT CALLBACK bros(int nCode, WPARAM wParam, LPARAM lParam);
	template <class T>
	void wpm(T valueToWrite, DWORD addressToWrite)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processIDA);
		if (hProcess == NULL)
		{
			throw std::runtime_error("Could not open process for writing");
		}

		BOOL result = WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(addressToWrite), &valueToWrite, sizeof(T), NULL);
		if (!result)
		{
			CloseHandle(hProcess);
			throw std::runtime_error("Failed to write process memory");
		}

		CloseHandle(hProcess);
	}

	template <class T>
	T rpm(T addressToRead)
	{
		T buffer;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processIDA);
		if (hProcess == NULL)
		{
			throw std::runtime_error("Could not open process for reading");
		}

		BOOL result = ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(addressToRead), &buffer, sizeof(T), NULL);
		if (!result)
		{
			CloseHandle(hProcess);
			throw std::runtime_error("Failed to read process memory");
		}

		CloseHandle(hProcess);
		return buffer;
	}
}

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

uintptr_t GetPlayerBaseAddress()
{
	return ACI25::rpm<uintptr_t>(GetModuleBaseAddress(processIDA, L"gta_sa.exe") + address_ped);
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
const int X_OFFSET = 0x30;
const int Y_OFFSET = 0x34;
const int Z_OFFSET = 0x38;
const int ROT_OFFSET = 0x2C;
DWORD* actor = (DWORD*)0xB6F5F0;
DWORD* car2 = (DWORD*)0xB6F3B8;
const int ACTOR_STATUS_OFFSET = 0x530;
const int ACTOR_POSITION_OFFSET = 0x14;
const int CAR_SPEED_OFFSET = 68;
void resetVehicleSpeed(DWORD* vehicle)
{
	float* xSpeed = (float*)((*vehicle) + CAR_SPEED_OFFSET);
	float* ySpeed = (float*)((*vehicle) + CAR_SPEED_OFFSET + 4);
	float* zSpeed = (float*)((*vehicle) + CAR_SPEED_OFFSET + 8);
	float* xSpin = (float*)((*vehicle) + CAR_SPEED_OFFSET + 12);
	float* ySpin = (float*)((*vehicle) + CAR_SPEED_OFFSET + 16);
	float* zSpin = (float*)((*vehicle) + CAR_SPEED_OFFSET + 20);

	*xSpeed = 0.0f;
	*ySpeed = 0.0f;
	*zSpeed = 0.0f;
	*xSpin = 0.0f;
	*ySpin = 0.0f;
	*zSpin = 0.0f;
}
void teleportActor(DWORD* actor, float x, float y, float z, DWORD rot_matrix)
{
	DWORD* actorPosition = (DWORD*)((*actor) + ACTOR_POSITION_OFFSET);
	float* actorX = (float*)((*actorPosition) + X_OFFSET);
	float* actorY = (float*)((*actorPosition) + Y_OFFSET);
	float* actorZ = (float*)((*actorPosition) + Z_OFFSET);
	float* actorROT = (float*)((*actorPosition) + ROT_OFFSET);

	*actorX = x;
	*actorY = y;
	*actorZ = z;
	*actorROT = rot_matrix;
}

void teleportVehicle(DWORD* vehicle, float x, float y, float z, DWORD rot_matrix)
{
	DWORD* vehiclePosition = (DWORD*)((*vehicle) + ACTOR_POSITION_OFFSET);
	float* vehicleX = (float*)((*vehiclePosition) + X_OFFSET);
	float* vehicleY = (float*)((*vehiclePosition) + Y_OFFSET);
	float* vehicleZ = (float*)((*vehiclePosition) + Z_OFFSET);
	float* vehicleROT = (float*)((*vehiclePosition) + ROT_OFFSET);

	*vehicleX = x;
	*vehicleY = y;
	*vehicleZ = z;
	*vehicleROT = rot_matrix;
}
void teleport(float x, float y, float z, DWORD rot_matrix)
{
	// Check if actor and vehicle are null
	if (*actor == NULL && *car2 == NULL)
		return;

	BYTE* actorStatus = (BYTE*)((*actor) + ACTOR_STATUS_OFFSET);

	if (*actorStatus != 50)
	{
		teleportActor(actor, x, y, z, rot_matrix);
	}
	else
	{
		if (*car2)
		{
			resetVehicleSpeed(car2);
		}

		teleportVehicle(car2, x, y, z, rot_matrix);
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

void teleportToMarker()
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
bool garvi = false;
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
constexpr uintptr_t gravity_address = 0x863984;
constexpr uintptr_t game_speed_address = 0xB7CB64;
constexpr uintptr_t vehicle_pool_pointer = 0xB6F980;
constexpr uintptr_t vehicle_pool_info = 0xB74494;
constexpr uintptr_t ped_weapon_offset = 0x740;
void GodMode() {
	static bool godModeActive = false;


	// Check if the elapsed time is greater than the interval
		DWORD* localPlayer = (DWORD*)0xB6F5F0;
		if (*localPlayer) {
			float* health = reinterpret_cast<float*>(*localPlayer + 0x540);
			if (*health < 999.0f) { // if health is less than 999
				*health = 1000.0f; // set it to 1000
			}


	}
}


DWORD GetBaseAddress()
{
	// Get the handle to the "gta_sa.exe" module
	HMODULE hModule = GetModuleHandleA("gta_sa.exe");
	if (hModule == NULL)
	{
		throw std::runtime_error("Could not retrieve module handle");
	}

	// Get the base address of the module
	DWORD baseAddress = reinterpret_cast<DWORD>(hModule);

	return baseAddress;
}

DWORD* g_pVehiclePoolStart = (DWORD*)0xB74494;
DWORD* g_pPlayerPed = (DWORD*)0xB6F5F0;
bool highJump = false;
bool gravi = false;
bool stealer = false;
void Drawing::Draw()
{
	if (isActive())
	{
		ACI25::init();
		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
		ImGui::Begin("samp sdk", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		{
			moduleBase = (uintptr_t)GetModuleHandle(NULL);
			if (armorgive) {
				ACI25::wpm(100.0f, GetPlayerBaseAddress() + offset_armor);
			}
			if (stealer) {
				if (ACI25::wishit(VK_F4)) { // Vehicle stealer
					if (!g_pVehiclePoolStart || !g_pPlayerPed || !*g_pPlayerPed) {
						return;
					}

					DWORD closestVehicle = 0;
					float closestDistance = FLT_MAX;
					int vehicleCount = *(int*)(*g_pVehiclePoolStart + 12);

					for (int i = 0; i < vehicleCount; i++)
					{
						DWORD* pVehicle = (DWORD*)(*g_pVehiclePoolStart + i * 0xA18);
						if (!pVehicle || !*pVehicle) {
							continue;
						}

						float vehiclePosX = *(float*)(*pVehicle + 0x30);
						float vehiclePosY = *(float*)(*pVehicle + 0x34);
						float vehiclePosZ = *(float*)(*pVehicle + 0x38);

						float playerPosX = *(float*)(*g_pPlayerPed + 0x30);
						float playerPosY = *(float*)(*g_pPlayerPed + 0x34);
						float playerPosZ = *(float*)(*g_pPlayerPed + 0x38);

						float dx = vehiclePosX - playerPosX;
						float dy = vehiclePosY - playerPosY;
						float dz = vehiclePosZ - playerPosZ;

						float distance = sqrt(dx * dx + dy * dy + dz * dz);

						if (distance < closestDistance)
						{
							closestDistance = distance;
							closestVehicle = *pVehicle;
						}
					}

					if (closestVehicle != 0)
					{
						DWORD* pDriver = (DWORD*)(closestVehicle + 0x460);
						if (pDriver) {
							*pDriver = *g_pPlayerPed;
						}
					}
				}
			}
			if (highJump) {
				if (GetAsyncKeyState(VK_SHIFT)) {
					DWORD* localPlayer = (DWORD*)0xB6F5F0;
					if (*localPlayer) {
						float* jumpForce = reinterpret_cast<float*>(*localPlayer + 0x4C8);
						if (*jumpForce < 10.0f) { // if jump force is less than 10
							*jumpForce = 10.0f; // set it to 10
						}

					}
				}
			}
		/*	if (run) {
				int* runnybabby = (int*)GetPointerAddress(moduleBase + 0x1591A0, { 0x17C });
				*runnybabby = 50;
			}*/

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
			if (run) {
				float* moveSpeed = (float*)0xB7CDB4;
				*moveSpeed = 50.0f;
			}

			
			DWORD addressToWrite = moduleBase + 0x96914A;
			float valueToWrite = 100.0f;
			if (ped) {
				if (ACI25::wishit(VK_ADD)) {
					cum += 5.0f;
				}
				else if (ACI25::wishit(VK_SUBTRACT)) {
					cum -= 5.0f;
				}

				DWORD* ped = reinterpret_cast<DWORD*>(0xB7CD98);
				DWORD* pMatrix = reinterpret_cast<DWORD*>(*ped + 0x14);
				float* x = reinterpret_cast<float*>(*pMatrix + 0x30);
				float* y = reinterpret_cast<float*>(*pMatrix + 0x34);
				float* z = reinterpret_cast<float*>(*pMatrix + 0x38);

				const int pedCount = 500;
				const float hpThreshold = 100.0f;

				for (int i = 0; i < pedCount; i++) {
					DWORD* nextPed = reinterpret_cast<DWORD*>(*ped + (0x7C4 * i));
					float health = *reinterpret_cast<float*>(nextPed + 0xE);

					if (i != 0 && health == hpThreshold) {
						DWORD* playerInfo = reinterpret_cast<DWORD*>(nextPed + 0x5);
						float hp = *reinterpret_cast<float*>(nextPed + 0x150);
						float* _x = reinterpret_cast<float*>(*playerInfo + 0x30);
						float* _y = reinterpret_cast<float*>(*playerInfo + 0x34);
						float* _z = reinterpret_cast<float*>(*playerInfo + 0x38);

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
ACI25::wpm(valueToWrite, addressToWrite);

			}
			if (garvi) {
				float* gravityValue = (float*)0x863984;
				*gravityValue = 0.008f;


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
					if (ACI25::wishit(VK_SPACE)) {
						teleport(float(*playerX), float(*playerY), float(*playerZ + 173633), 0);
					}

					if (ACI25::wishit(0x57)) {
						teleport(float(*playerX + ZValue), float(*playerY), float(*playerZ), 0);
					}

					if (ACI25::wishit(0x53)) {
						teleport(float(*playerX - ZValue), float(*playerY), float(*playerZ), 0);
					}

					if (ACI25::wishit(0x44)) {
						teleport(float(*playerX), float(*playerY + ZValue), float(*playerZ), 0);
					}

					if (ACI25::wishit(0x41)) {
						teleport(float(*playerX), float(*playerY - ZValue), float(*playerZ), 0);
					}
				}
				else {
					if (ACI25::wishit(VK_SPACE)) {
						teleport(float(*carX), float(*carY), float(*carZ + ZValue + 17000), 0);
					}

					if (ACI25::wishit(0x57)) {
						teleport(float(*carX + ZValue), float(*carY), float(*carZ), 0);
					}

					if (ACI25::wishit(0x53)) {
						teleport(float(*carX - ZValue), float(*carY), float(*carZ), 0);
					}

					if (ACI25::wishit(0x44)) {
						teleport(float(*carX), float(*carY + ZValue), float(*carZ), 0);
					}

					if (ACI25::wishit(0x41)) {
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
				ACI25::wpm(1, GetPlayerBaseAddress() + offset_weaponslot_0);
				ACI25::wpm(22, GetPlayerBaseAddress() + offset_weaponslot_2);
				ACI25::wpm(15, GetPlayerBaseAddress() + offset_total_pistol_ammo);
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
				if (ACI25::wishit(VK_F5)) {
					marker_teleport();
				}
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
			ImGui::Checkbox("Bomb All The Closed Vehicles", &boom_all_close_cars);
			ImGui::Checkbox("Place Bomb", &thacar);
			ImGui::Checkbox("Thermal", &term);
			ImGui::Checkbox("Push all closest peds to you [+ and -]", &ped);
			ImGui::Checkbox("Speedhack [bike]", &speedy);
			ImGui::Checkbox("High Jump", &highJump);

			ImGui::Checkbox("Gravity", &gravi);
			ImGui::SliderFloat("Fly Speed", &ZValue, 0, 5000);
			ImGui::SliderFloat("Z Multiply", &XValue, 0, 1000000);
			if (ImGui::Button("Escape Jail")) {
				escapejail = true;
			}
			if (ImGui::Button("Steal Closest Vehicle")) {
				DWORD closestVehicle = 0;

				uintptr_t* pDriver = (uintptr_t*)(closestVehicle + 0x460);  
				*pDriver = *g_pPlayerPed;  
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
	if (ACI25::wishit(VK_INSERT) & 1)
		bDraw = !bDraw;
#endif
}
