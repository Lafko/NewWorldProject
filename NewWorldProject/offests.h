#pragma once

int ver = 18;

//Speed offsets 
int Offset_speed = 0x069887F0;
int Offset_speedPointer = 0x234;
//Base offsets
int Offset_manager = 0x6977B18;
int Offset_camera = 0x697B0D8;
int Offset_animation = 0xD45B19;
//Cords offsets
int Offset_cam = 0x3B4;
int Offset_cameraFOV = 0xC0;
int Offset_playerLocationX = 0x18C;
int Offset_playerLocationY = 0x19C;
int Offset_playerLocationZ = 0x1AC;

struct pLocation
{
	char pad0[0x18C];
	float Offset_playerLocationX;
	char pad1[0xc];
	float Offset_playerLocationY;
	char pad2[0xc];
	float Offset_playerLocationZ;
};

int Offset_playerLocalLocation = 0x1A4;

int Offset_cameraLocation = 0x38;
int Offset_cameraRotationX = 0x48;
int Offset_cameraRotationY = 0x44;
//Obj offsets
int Offset_obj = 0x298;
int Offset_objSize = 0x288;
int Offset_objPtr = 0x108;
int Offset_namePtr = 0x38;
int Offset_nameLen = 0x10;
int Offset_firstComponent = 0x10;
int Offset_lastComponent = 0x18;
//Player offsets
int Offset_playerName = 0x1B8;
int Offset_playerLvl = 0x0;
int Offset_playerFaction = 0x0;
int Offset_playerPvpFlag = 0x0;
int Offset_mobLvl = 0x0;
//Gatherable offsets
int Offset_gatherableName = 0x158;
int Offset_isGather = 0x378;

DWORD64 Speed = 0;
DWORD64 transformComponent = 0;
DWORD64 transformComponentBack = 0;
DWORD64 playerComponent = 0;
DWORD64 cam = 0;
float CameraFOV = 0;
DWORD64 manager_base = 0;
int AFOV = 75.f;