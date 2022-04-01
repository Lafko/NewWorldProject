#include <Windows.h>
#include <stdio.h>
#include <winternl.h>
#include <iostream>
#include <map>
#include <thread>
#include <mutex>

#include "xor.h"
#include "utils.h"
#include "driver.h"
#include "vector.h"
#include "dx_renderer.h"
#include "offests.h"
#include "function.h"
#include "menu.h"
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "Winmm.lib")

#define TYPE_PLAYER 1
#define TYPE_TREE 2
#define TYPE_MINERALS 3
#define TYPE_BUSH 4
#define TYPE_MOB 5
#define TYPE_CHEST 6
#define TYPE_CHEST_RANGE 7

#define PVP_Peaceful 0
#define PVP_War 1

struct Entity
{
	int type;
	int Faction;
	int PvPFlag;
	DWORD64 CharacterComponent;
	DWORD64 GatherableControllerComponent;
	int HP;
	int HPMax;
	DWORD64 GameTransformComponent;
	DWORD64 PlayerComponent;
	char objName[64];
	char objFullName[64];
	BYTE isGather;
	DWORD64 SkinnedMeshComponent;
};

int ObjCount = 0;
Entity ObjList[5000];

int ObjCountCache = 0;
Entity ObjListCache[5000];

map<DWORD64, string> ObjComponentNameMap;
bool shift = false;
float SpeedVal = 0.f;
float SpeedValCache = 0.f;

time_t preTime = clock();
time_t showTime = clock();
float fps = 0.f;

mutex g_lock;
int playersCountInRadius = 0;
int playersCountInRadiusCache = 0;

DWORD SpeedHack(PVOID in)
{
	timeBeginPeriod(1);
	while (!Speed) {
		Speed = READ64(BaseAddr + Offset_speed);
		Sleep(100);
	}
	Speed += Offset_speedPointer;

	while (!GetAsyncKeyState(VK_END))
	{
		if (Cheat.Other.Speed && BaseAddr && manager_base)
		{
			AimKeys();
			if (Speed)
			{
				if (GetAsyncKeyState(VK_F5) & 1)
				{
					SpeedVal = WriteFloat(Speed, 1);
				}
				else if (GetAsyncKeyState(VK_F2) & 1)
				{
					SpeedVal = WriteFloat(Speed, f2Speed);
				}
				else if (GetAsyncKeyState(VK_CAPITAL) & 0x8000)
				{
					if (shift == false)
					{
						WriteByte(BaseAddr + Offset_animation + 0x2, 0x4F);
						shift = true;
					}
				}
				else if (GetAsyncKeyState(VK_CAPITAL) == 0 && shift == true)
				{
					WriteByte(BaseAddr + Offset_animation + 0x2, 0x47);
					shift = false;
				}
				else if (bCharge && GetAsyncKeyState(0x57) & GetAsyncKeyState(0x52) & 0x8000)
				{
					WriteByte(BaseAddr + Offset_animation + 0x2, 0x4F);
					Sleep(708);
					mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					Sleep(1);
					if (shift == false)
					{
						shift = true;
					}
				}
				else if (GetAsyncKeyState(0x52) == 0 && shift == true)
				{
					WriteByte(BaseAddr + Offset_animation + 0x2, 0x47);
					Sleep(1);
					shift = false;
				}
				else if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					Sleep(200);
					keybd_event(0x46, 0, 0, 0);
					keybd_event(0x46, 0, 0x02, 0);
					Sleep(30);
					keybd_event(0x49, 0, 0, 0);
					keybd_event(0x49, 0, 0x02, 0);
					Sleep(30);
				}
				else if (GetAsyncKeyState(VK_XBUTTON2) & 0x1)
				{
					WriteByte(BaseAddr + Offset_animation + 0x2, 0x4F);
					keybd_event(0x46, 0, 0, 0);
					keybd_event(0x46, 0, 0x02, 0);
					Sleep(250);
					mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					WriteByte(BaseAddr + Offset_animation + 0x2, 0x47);
					Sleep(15);
				}
				if (SpeedValCache != SpeedVal)
				{
					SpeedVal = WriteFloat(Speed, SpeedVal);
				}
				SpeedValCache = SpeedVal;
			}
		}
		else if (BaseAddr && manager_base)
		{
			if (Speed)
			{
				if (SpeedVal != 1.f)
				{
					SpeedVal = WriteFloat(Speed, 1.f);
				}
			}
		}
		Sleep(1);
	}
	return 0;
}

void Draw()
{
	menuEN();
	if (manager_base)
	{
		g_lock.lock();
		int y1 = 50;
		playersCountInRadius = 0;
		for (int i = 0; i < ObjCountCache; i++)
		{
			pLocation LocationPlayer = read<pLocation>(ObjListCache[i].GameTransformComponent);
			FVector Location = { LocationPlayer.Offset_playerLocationX, LocationPlayer.Offset_playerLocationY, LocationPlayer.Offset_playerLocationZ };
			FVector LocalLocation = READV(cam + Offset_playerLocalLocation);

			auto dist = (Location - LocalLocation).Size();

			if (dist < 250 && dist > 2)
			{
				FVector CameraLocation = READV(cam + Offset_cameraLocation);
				FVector CameraRotation = { 0, 0, 0 };
				CameraRotation.x = ReadFloat(cam + Offset_cameraRotationX);
				CameraRotation.y = ReadFloat(cam + Offset_cameraRotationY) - 270;

				//printf("CameraLocation %f %f %f %p\n", CameraLocation.x, CameraLocation.y, CameraLocation.z, cam);

				if (ObjListCache[i].type == TYPE_PLAYER)
				{
					FVector rootHeadOut = FVector(0, 0, 0);
					FVector rootDownOut = FVector(0, 0, 0);

					FVector HeadOut = GetBoneWithRotation(ObjListCache[i].SkinnedMeshComponent, 103);
					FVector	DownOut = GetBoneWithRotation(ObjListCache[i].SkinnedMeshComponent, 138);

					if (WorldToScreen(HeadOut, CameraLocation, CameraRotation, CameraFOV, rootHeadOut) && WorldToScreen(DownOut, CameraLocation, CameraRotation, CameraFOV, rootDownOut))
					{
						//string sPlayerName = ObjListCache[i].objFullName;
						//FVector CameraLocationLocal;

						////printf("sPlayerName %s\n", sPlayerName.c_str());
						//if (sPlayerName == "eas01")
						//{
						//	printf("%p %p\n", ObjListCache[i].GameTransformComponent, ObjListCache[i].SkinnedMeshComponent);
						//	for (int ia = 0; ia < 139; ia++)
						//	{
						//		FVector rootPos = FVector(0, 0, 0);
						//		WorldToScreen(GetBoneWithRotation(ObjListCache[i].SkinnedMeshComponent, ia), CameraLocation, CameraRotation, CameraFOV, rootPos);

						//		renderer.DrawStrokeText(rootPos.x, rootPos.y, ColorVector[ia], to_string(ia), 9);
						//	}
						//}

						if (Cheat.AimBot.On)
						{
							float max = AFOV / 2;
							GetClosestPlayerToCrossHair(rootHeadOut, max, ObjListCache[i].GameTransformComponent, ObjListCache[i].SkinnedMeshComponent);
						}

						if (Cheat.PlayerEsp.On)
						{
							if (Cheat.PlayerEsp.Box)
							{
								if (Cheat.PlayerEsp.BoxType == 0)
								{
									Esp2DBox_5567(rootHeadOut, rootDownOut, cGreenYellow, 1);
								}
								else if (Cheat.PlayerEsp.BoxType == 1)
								{
									float h_player = rootDownOut.y - rootHeadOut.y;
									float w = h_player / 3;
									DrawCornerBox(rootHeadOut.x - w, rootHeadOut.y, w * 2, h_player, cGreenYellow, 1, rootHeadOut, rootDownOut);
								}
							}
							if (Cheat.PlayerEsp.Skeleton)
							{
								DrawSkeleton(ObjListCache[i].SkinnedMeshComponent, cGreenYellow, 0.5, CameraLocation, CameraRotation, CameraFOV, dist, HeadOut);
							}
							if (Cheat.PlayerEsp.Name)
							{
								int xName = rootHeadOut.x - 30 + ((int)dist / 15);
								int yName = rootHeadOut.y - 30 + ((int)dist / 30);
								renderer.DrawStrokeText(xName, yName - (TextSize - 11) * 2, cYellow, ObjListCache[i].objFullName, TextSize);
							}
							if (Cheat.PlayerEsp.Line)
							{
								renderer.DrawLine(Width / 2, 0, rootHeadOut.x, rootHeadOut.y, ObjListCache[i].PvPFlag ? cRed : cGreenYellow, 0.5);
							}
							if (Cheat.PlayerEsp.Distance)
							{
								char cDist[64];
								float TextSizeDistance = TextSize - ((int)dist / 100);
								auto dDist = skCrypt("[%d]");
								sprintf_s(cDist, dDist, (int)dist);
								dDist.clear();
								renderer.DrawStrokeText(rootDownOut.x, rootDownOut.y, cWhite, cDist, TextSize);
							}
							if (Cheat.PlayerEsp.HP)
							{
								int rootOutXHP = rootHeadOut.x - (22 - ((int)dist / 50));
								int rootOutYHP = rootHeadOut.y - (18 - ((int)dist / 80));
								char cHp[64];
								auto dHp = skCrypt("%d");
								sprintf_s(cHp, dHp, (int)ObjListCache[i].HP);
								renderer.DrawStrokeText(rootOutXHP - (TextSize - 11) * 2 - strlen(cHp), rootOutYHP - (TextSize - 11), cWhite, cHp, TextSize - 2);
								dHp.clear();
							}
							if (Cheat.PlayerEsp.InRadius && dist < warningDistance)
							{
								playersCountInRadius++;
								if (Cheat.PlayerEsp.NamesInRadius)
								{
									/*string sAllLineText = (Cheat.PlayerEsp.Name ? sPlayerName + " " : "") + to_string((int)dist);
									renderer.DrawStrokeText(7 + (menu ? DrawNameHeight : 0), y1 = y1 + 21, ObjListCache[i].PvPFlag ? cRed : cOrange, sAllLineText, 12);
									if (ObjListCache[i].Faction)
									{
										renderer.DrawImage((menu ? DrawNameHeight : 0) + sAllLineText.length() * 8, y1 - 6, 28, 27, TexturesFactionMap[ObjListCache[i].Faction], 1);
									}*/
								}
							}
						}
					}
				}

				FVector objLocation = { 0, 0, 0 };
				if (ObjListCache[i].type != TYPE_PLAYER && WorldToScreen(Location, CameraLocation, CameraRotation, CameraFOV, objLocation))
				{
					if (Cheat.BushEsp.On && ObjListCache[i].type == TYPE_BUSH)
					{
						string sObjFullName = ObjListCache[i].objFullName;
						renderer.DrawStrokeText(objLocation.x, objLocation.y, ObjListCache[i].isGather == 0x4 ? cWhite : cGray, sObjFullName + " [" + to_string((int)dist) + " m]", 12);
					}
					else if (Cheat.MineralEsp.On && ObjListCache[i].type == TYPE_MINERALS)
					{
						string sObjFullName = ObjListCache[i].objFullName;
						renderer.DrawStrokeText(objLocation.x, objLocation.y, ObjListCache[i].isGather == 0x4 ? cPlum : cGray, sObjFullName + " [" + to_string((int)dist) + " m]", 12);
					}
					else if (Cheat.TreeEsp.On && ObjListCache[i].type == TYPE_TREE)
					{
						string sObjFullName = ObjListCache[i].objFullName;
						renderer.DrawStrokeText(objLocation.x, objLocation.y, ObjListCache[i].isGather == 0x4 ? cWhite : cGray, sObjFullName + " [" + to_string((int)dist) + " m]", 12);
					}
					else if (Cheat.CreatureEsp.On && ObjListCache[i].type == TYPE_MOB)
					{
						/*if (Cheat.AimBot.On)
						{
							float max = AFOV / 2;
							GetClosestPlayerToCrossHair(rootHeadOut, max, ObjListCache[i].GameTransformComponent, ObjListCache[i].SkinnedMeshComponent);
						}*/

						/*for (int ia = 0; ia < 100; ia++)
						{
							FVector rootPos = FVector(0, 0, 0);
							WorldToScreen(GetBoneWithRotation(ObjListCache[i].SkinnedMeshComponent, ia), CameraLocation, CameraRotation, CameraFOV, rootPos);

							renderer.DrawStrokeText(rootPos.x, rootPos.y, ColorVector[ia], to_string(ia), 9);
						}*/

						string sObjFullName = ObjListCache[i].objFullName;

						std::string BASE = "BASE - Wildlife - ";
						std::string BASE2 = "BASE - Corrupted - ";
						std::string BASE3 = "BASE - Angry Earth - ";
						std::string::size_type ii = sObjFullName.find(BASE);
						std::string::size_type i2 = sObjFullName.find(BASE2);
						std::string::size_type i3 = sObjFullName.find(BASE3);
						if (ii != std::string::npos)
						{
							sObjFullName.erase(ii, BASE.length());
						}
						if (i2 != std::string::npos)
						{
							sObjFullName.erase(i2, BASE2.length());
						}
						if (i3 != std::string::npos)
						{
							sObjFullName.erase(i3, BASE3.length());
						}
						renderer.DrawStrokeText(objLocation.x, objLocation.y, cOrangeRed, sObjFullName + " [" + to_string((int)dist) + " m] " + to_string(ObjListCache[i].HP), 12);
					}
					else if (Cheat.Other.Chest && ObjListCache[i].type == TYPE_CHEST)
					{
						string sObjFullName = ObjListCache[i].objFullName;

						if (sObjFullName.find(skCrypt("House_").decrypt()) == string::npos)
						{
							renderer.DrawStrokeText(objLocation.x, objLocation.y, ObjListCache[i].isGather == 0x4 ? cSteelBlue : cGray, sObjFullName + " [" + to_string((int)dist) + " m]", 12);
						}
					}
					else if (Cheat.Other.Chest && ObjListCache[i].type == TYPE_CHEST_RANGE)
					{
						string sObjFullName = ObjListCache[i].objFullName;

						if (sObjFullName.find(skCrypt("House_").decrypt()) == string::npos)
						{
							renderer.DrawStrokeText(objLocation.x, objLocation.y + 15, cSteelBlue, sObjFullName + " [" + to_string((int)dist) + " m]", 12);
						}
					}
				}
			}
		}
		g_lock.unlock();
	}

	int miniX = 10;
	int miniY = 15;

	if (Cheat.Other.FPS)
	{
		time_t postTime = clock();
		time_t frameTime = postTime - preTime;
		preTime = postTime;
		if (postTime - showTime > 100)
		{
			fps = 1000.f / (float)frameTime;
			showTime = postTime;
		}
		renderer.DrawStrokeText(miniX, miniY, cGreenYellow, skCrypt("RAM FPS:\t[ ").decrypt() + to_string((int)fps) + " ]", 13);
	}
	if (Cheat.Other.Speed)
	{
		char cSpeed[32] = { NULL };
		sprintf_s(cSpeed, skCrypt("Speed:\t[ x%.2f ]"), SpeedVal);
		renderer.DrawStrokeText(miniX, miniY * 2, cGreenYellow, cSpeed, 13);
	}
	if (Cheat.PlayerEsp.InRadius)
	{
		playersCountInRadiusCache = playersCountInRadius;
		renderer.DrawStrokeText(miniX, miniY * (Cheat.Other.Speed ? 3 : 2), playersCountInRadiusCache ? cRed : cGreenYellow, skCrypt("Players:\t[ ").decrypt() + to_string(playersCountInRadiusCache) + " ] in " + to_string(warningDistance) + " m", 13);
	}
	if (Cheat.AimBot.On)
	{
		if (Cheat.AimBot.FOVCircle)
		{
			renderer.DrawCircle(Width / 2, Height / 2, AFOV, cWhite, 0);
		}
	}
	
}

void Renderer()
{
	timeBeginPeriod(1);

	while (!GetAsyncKeyState(VK_END))
	{
		if (!VSync)
		{
			Sleep(rendererSleep);
		}

		auto CryENGINE = skCrypt("CryENGINE");
		hGameWnd = FindWindowA(CryENGINE, 0);
		CryENGINE.clear();
		if (!hGameWnd)
		{
			renderer.manual_destruct();
			TerminateProcess(GetCurrentProcess(), 0);
			return;
		}
		else if (ManualW_H)
		{
			Width = ManualWidth;
			Height = ManualHeight;
		}
		else
		{
			RECT GameRect = { NULL };
			GetClientRect(hGameWnd, &GameRect);
			POINT xy;
			ClientToScreen(hGameWnd, &xy);
			GameRect.left = xy.x;
			GameRect.top = xy.y;
			Width = GameRect.right;
			Height = GameRect.bottom;
		}

		renderer.begin_scene();
		Draw();
		renderer.end_scene();
	}
	renderer.manual_destruct();
	TerminateProcess(GetCurrentProcess(), 0);
}

DWORD tAim(PVOID in)
{
	while (true)
	{
		if (Cheat.AimBot.On)
		{
			if (GetAKey())
			{
				AimAt();
			}
		}
		Sleep(15);
	}
}

int startCheat()
{
	timeBeginPeriod(1);

	if (!Init())
	{
		if (LoadDriverKmemNew())
		{
			if (!Init())
			{
				printf(skCrypt("[-] Failed Load 2\n"));
				system("pause");
				TerminateProcess(GetCurrentProcess(), 0);
				return 0;
			}
		}
	}

	LoadConfig();


	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	d2d_window_t window{ };

	auto StartGame = skCrypt("[+] Start game...\n");
	printf(StartGame);
	StartGame.clear();
	hGameWnd = NULL;
	auto CryENGINE = skCrypt("CryENGINE");
	while (hGameWnd == NULL)
	{
		hGameWnd = FindWindowA(CryENGINE, 0);
		if (GetAsyncKeyState(VK_END))
		{
			TerminateProcess(GetCurrentProcess(), 0);
		}
		Sleep(10);
	}
	CryENGINE.clear();

	RECT GameRect = { NULL };
	GetClientRect(hGameWnd, &GameRect);
	POINT xy;
	ClientToScreen(hGameWnd, &xy);
	GameRect.left = xy.x;
	GameRect.top = xy.y;
	Width = GameRect.right;
	Height = GameRect.bottom;

	renderer = { true, hGameWnd };
	LoadResources();
	LoadTexturesImage();

#ifndef DEBUG
	system("CLS");
	FreeConsole();
#endif
	GetWindowThreadProcessId(hGameWnd, &GamePid);

#ifdef DEBUG
	printf("[+] Game found\n");
#endif
	BaseAddr = get_baseaddr(GamePid);
#ifdef DEBUG
	printf("BaseAddr %p \n", BaseAddr);
#endif
	
	if (BaseAddr)
	{

		renderer.LoadGameHijack(window._handle, hGameWnd);
		window.~d2d_window_t();

		thread thrRenderer(Renderer);
		HANDLE hButtons, hSpeedHack, hAim;
		CreateThreadProtected(&hButtons, &Buttons);
		CreateThreadProtected(&hSpeedHack, &SpeedHack);
		CreateThreadProtected(&hAim, &tAim);
		

		while (true)
		{
			Sleep(1);
			manager_base = READ64(BaseAddr + Offset_manager); if (manager_base == NULL) continue;

			auto cameraBase = READ64(BaseAddr + Offset_camera); if (cameraBase == NULL) continue;

			auto entity_mgr = READ64(manager_base); if (entity_mgr == NULL) continue;

			auto camera = READ64(cameraBase); if (camera == NULL) continue;

			cam = camera + Offset_cam;
			CameraFOV = ReadFloat(camera + Offset_cameraFOV) * 84.2;

			//printf("CameraFOV %f\n", CameraFOV);

			auto obj = READ64(entity_mgr - Offset_obj); if (obj == NULL) continue;
			auto obj_count = READ64(entity_mgr - Offset_objSize); if (obj_count == NULL) continue;

			//printf("obj_count %i \n", obj_count);

			int index = 0;
			for (DWORD64 k = 0; k < obj_count; k++)
			{
				auto compsomething = READ64(obj + (3 * 8));
				//printf("compsomething %p\n", compsomething);
				if (compsomething == NULL) continue;

				auto objPtr = READ64(compsomething + Offset_objPtr);
				if (objPtr == NULL) continue;

				auto namePtr = objPtr + Offset_namePtr;
				auto nameLen = READ64(namePtr + Offset_nameLen);

				if (nameLen >= 64)
				{
					obj = READ64(obj);
					continue;
				}

				if (nameLen >= 16) namePtr = READ64(namePtr);

				auto firstComponent = READ64(objPtr + Offset_firstComponent);
				auto lastComponent = READ64(objPtr + Offset_lastComponent);

				if (firstComponent == 0 || lastComponent == 0) continue;

				auto size = (lastComponent - firstComponent) / 8;
				if (size > 150) continue;

				char cObjName[64];
				READS(namePtr, cObjName, cObjName);
				string sObjName = cObjName;

				for (auto i = 0; i < size; i++)
				{
					auto component = READ64(firstComponent + (i * 8)); if (component == 0) continue;
					auto GetComponentFunc = READ64(component); if (GetComponentFunc == NULL) continue;
					char cObjComponentName[64] = { NULL };

					if (ObjComponentNameMap.find(GetComponentFunc) == ObjComponentNameMap.end())
					{
						auto GetObjComponentName = GetComponentFunc + 0x8;
						auto GetObjComponentNameAddr = READ64(GetObjComponentName); if (GetObjComponentNameAddr == NULL) continue;
						auto ObjComponentNameOffset = READ32(GetObjComponentNameAddr + 0x3);

						READS(GetObjComponentNameAddr + 7 + ObjComponentNameOffset, cObjComponentName, cObjComponentName);

						ObjComponentNameMap.insert(pair<DWORD64, string>(GetComponentFunc, cObjComponentName));
					}
					string sObjComponentName = ObjComponentNameMap[GetComponentFunc];

					if (strcmp(cObjComponentName, skCrypt("AttachmentComponent").decrypt()) == 0) continue;

					if (sObjName == skCrypt("RootPlayer").decrypt())
					{
						//printf("%s %p\n", sObjComponentName.c_str(), component);
						if (sObjComponentName == skCrypt("GameTransformComponent").decrypt())
						{
							ObjList[index].GameTransformComponent = component;
						}
						else if (sObjComponentName == skCrypt("CharacterComponent").decrypt())
						{
							ObjList[index].CharacterComponent = component;
							ObjList[index].type = TYPE_PLAYER;
						}
						else if (sObjComponentName == skCrypt("PlayerComponent").decrypt())
						{
							char cPlayerName[64] = { NULL };
							auto cPlayerNameAddr = READ64(component + Offset_playerName);

							if (cPlayerNameAddr > 0x7ffffffffff || cPlayerNameAddr < 0x00000100000)
							{
								READS(component + Offset_playerName, cPlayerName, cPlayerName);
							}
							else
							{
								READS(cPlayerNameAddr, cPlayerName, cPlayerName);
							}

							strcpy(ObjList[index].objFullName, cPlayerName);
						}
						else if (sObjComponentName == skCrypt("DamageReceiverComponent").decrypt())
						{
							DWORD64 HealthAddr = READ64(READ64(component + 0x3F0) + 0xDB8);
							//printf("component %p\n", component);
							ObjList[index].HP = (int)ReadFloat(HealthAddr + 0x20);
							ObjList[index].HPMax = (int)ReadFloat(HealthAddr + 0x24);
						}
						else if (sObjComponentName == skCrypt("SkinnedMeshComponent").decrypt())
						{
							ObjList[index].SkinnedMeshComponent = component;
						}
					}
					else if (Cheat.TreeEsp.On && sObjName == skCrypt("Master_Tree").decrypt())
					{
						if (sObjComponentName == skCrypt("GameTransformComponent").decrypt())
						{
							ObjList[index].GameTransformComponent = component;
						}
						else if (sObjComponentName == skCrypt("GatherableControllerComponent").decrypt())
						{
							char cTreeName[64] = { NULL };
							auto cTreeNameAddr = READ64(component + Offset_gatherableName);

							if (cTreeNameAddr > 0x7ffffffffff || cTreeNameAddr < 0x00000100000)
							{
								READS(component + Offset_gatherableName, cTreeName, cTreeName);
							}
							else
							{
								READS(cTreeNameAddr, cTreeName, cTreeName);
							}

							string sTreeName = cTreeName;
							//printf("sTreeName %s %p\n", sTreeName.c_str());
							if (sTreeName.find(skCrypt("Ironwood").decrypt()) != string::npos)
							{
								ObjList[index].type = TYPE_TREE;
								ObjList[index].GatherableControllerComponent = component;
								//Need find offset
								ObjList[index].isGather = READB(component + Offset_isGather);

								strcpy(ObjList[index].objFullName, cTreeName);
							}
						}
					}
					else if (Cheat.MineralEsp.On && sObjName == skCrypt("Master_Minerals").decrypt() || Cheat.MineralEsp.On && sObjName == skCrypt("Master_Stones").decrypt())
					{
						if (sObjComponentName == skCrypt("GameTransformComponent").decrypt())
						{
							ObjList[index].GameTransformComponent = component;
						}
						else if (sObjComponentName == skCrypt("GatherableControllerComponent").decrypt())
						{
							char cMineralName[64] = { NULL };
							auto cMineralNameAddr = READ64(component + Offset_gatherableName);

							if (cMineralNameAddr > 0x7ffffffffff || cMineralNameAddr < 0x00000100000)
							{
								READS(component + Offset_gatherableName, cMineralName, cMineralName);
							}
							else
							{
								READS(cMineralNameAddr, cMineralName, cMineralName);
							}
							string sMineralName = cMineralName;

							if (sMineralName != skCrypt("SingleStone").decrypt() && sMineralName.find(skCrypt("Boulder").decrypt()) == string::npos && sMineralName.find(skCrypt("Flint").decrypt()) == string::npos)
							{
								strcpy(ObjList[index].objFullName, cMineralName);

								ObjList[index].type = TYPE_MINERALS;
								ObjList[index].GatherableControllerComponent = component;
								//Need find offset
								ObjList[index].isGather = READB(component + Offset_isGather);
							}
						}
					}
					else if (/*Cheat.BushEsp.On && sObjName == skCrypt("Master_Bush").decrypt() ||*/ Cheat.BushEsp.On && sObjName == skCrypt("Master_Plants").decrypt() || Cheat.BushEsp.On && sObjName == skCrypt("Master_Alchemy").decrypt())
					{
						if (sObjComponentName == skCrypt("GameTransformComponent").decrypt())
						{
							ObjList[index].GameTransformComponent = component;
						}
						else if (sObjComponentName == skCrypt("GatherableControllerComponent").decrypt())
						{
							char cBushName[64] = { NULL };
							auto cBushNameAddr = READ64(component + Offset_gatherableName);

							if (cBushNameAddr > 0x7ffffffffff || cBushNameAddr < 0x00000100000)
							{
								READS(component + Offset_gatherableName, cBushName, cBushName);
							}
							else
							{
								READS(cBushNameAddr, cBushName, cBushName);
							}

							string sBushName = cBushName;

							if (sBushName.find(skCrypt("BulRush").decrypt()) == string::npos && sBushName.find(skCrypt("CatTail").decrypt()) == string::npos)
							{
								strcpy(ObjList[index].objFullName, cBushName);

								ObjList[index].type = TYPE_BUSH;
								ObjList[index].GatherableControllerComponent = component;
								//Need find offset
								ObjList[index].isGather = READB(component + Offset_isGather);
								//printf("component %p %s\n", component, sBushName);
							}
						}
					}
					else if (Cheat.Other.Chest && sObjName == skCrypt("Master_LootContainer").decrypt())
					{
						//printf("%s\n", sObjComponentName.c_str());
						if (sObjComponentName == skCrypt("GameTransformComponent").decrypt())
						{
							ObjList[index].GameTransformComponent = component;

							strcpy(ObjList[index].objFullName, cObjName);
						}
						else if (sObjComponentName == skCrypt("GatherableControllerComponent").decrypt())
						{
							char cChestName[64] = { NULL };
							auto cChestNameAddr = READ64(component + Offset_gatherableName);

							if (cChestNameAddr > 0x7ffffffffff || cChestNameAddr < 0x00000100000)
							{
								READS(component + Offset_gatherableName, cChestName, cChestName);
							}
							else
							{
								READS(cChestNameAddr, cChestName, cChestName);
							}
							strcpy(ObjList[index].objFullName, cChestName);

							string sChestName = cChestName;

							if (sChestName.find(skCrypt("Loot").decrypt()) != string::npos)
							{
								ObjList[index].type = TYPE_CHEST;
								ObjList[index].GatherableControllerComponent = component;
								ObjList[index].isGather = READB(component + Offset_isGather);
							}
						}
					}
					else if (Cheat.Other.Chest && sObjName.find(skCrypt("Chest").decrypt()) != string::npos)
					{
						if (sObjComponentName == skCrypt("GameTransformComponent").decrypt())
						{
							ObjList[index].GameTransformComponent = component;
							ObjList[index].type = TYPE_CHEST_RANGE;
							strcpy(ObjList[index].objFullName, cObjName);
						}
					}
					else if (Cheat.CreatureEsp.On
						&& sObjName.find(skCrypt("Alligator").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Bear").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Bison").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Boar").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Cow").decrypt()) != string::npos
						|| sObjName.find(skCrypt("ElementalBear").decrypt()) != string::npos
						|| sObjName.find(skCrypt("ElementalWolf").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Elk").decrypt()) != string::npos
						|| sObjName.find(skCrypt("ForestElemental").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Goat").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Leopard").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Lion").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Lynx").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Named").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Piglet").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Rabbit").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Sheep").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Turkey").decrypt()) != string::npos
						|| sObjName.find(skCrypt("TurkeyNest").decrypt()) != string::npos
						//|| sObjName.find(skCrypt("Corruption").decrypt()) != string::npos
						//|| sObjName.find(skCrypt("Corrupted").decrypt()) != string::npos
						|| sObjName.find(skCrypt("Wolf").decrypt()) != string::npos)
					{
						if (sObjComponentName == skCrypt("GameTransformComponent").decrypt())
						{
							ObjList[index].GameTransformComponent = component;
						}
						else if (sObjComponentName == skCrypt("CharacterComponent").decrypt())
						{
							ObjList[index].type = TYPE_MOB;
							ObjList[index].CharacterComponent = component;
							//Need find offset
							//ObjList[index].Lvl = ReadInteger(component + Offset_mobLvl);
							strcpy(ObjList[index].objFullName, cObjName);
						}
						else if (sObjComponentName == skCrypt("DamageReceiverComponent").decrypt())
						{
							DWORD64 HealthAddr = READ64(READ64(component + 0x3F0) + 0xDB8);
							//printf("HealthAddr %p\n", component);
							ObjList[index].HP = (int)ReadFloat(HealthAddr + 0x20);
							ObjList[index].HPMax = (int)ReadFloat(HealthAddr + 0x24);
						}
						else if (sObjComponentName == skCrypt("SkinnedMeshComponent").decrypt())
						{
							ObjList[index].SkinnedMeshComponent = component;
						}
					}
				}
				obj = READ64(obj);
				index++;
			}
			ObjCount = index;
			g_lock.lock();
			ObjCountCache = index;
			memset(&ObjListCache, 0, sizeof(ObjListCache));
			memcpy(ObjListCache, ObjList, sizeof(ObjList));
			memset(&ObjList, 0, sizeof(ObjList));
			g_lock.unlock();
		}
	}
}

int main(int argc, char* argv[])
{
	system("CLS");

	auto version = skCrypt("RAM New World ver: ").decrypt() + to_string(ver) + "\n";

	printf(version.c_str());
	printf(skCrypt("[+] Loading...\n"));

	if (!IsElevated())
	{
		printf(skCrypt("[-] Run as admin...\n"));
		system("pause");
		TerminateProcess(GetCurrentProcess(), 0);
	}

	HANDLE hprinter;
	LoadResources();
	startCheat();

	return 0;
	
}