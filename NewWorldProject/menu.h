#pragma once
#include <time.h>
#include "xor.h"
#include "colors.h"

DWORD menu = 1;
DWORD lockMenu = 1;
DWORD bCharge = 1;
int rendererSleep = 1;
int warningDistance = 150;
float attackSpeed = 6.0f;
float f2Speed = 1.2f;
float f3Speed = 2.0f;
float f4Speed = 3.5f;
HWND hGameWnd = NULL;
extern "C" void SaveCfg();
DWORD hAimKey = 0;
DWORD ABotKey = VK_LSHIFT;

int TextSize = 11;

bool GetAKey()
{
    return GetAsyncKeyState(ABotKey);
}

void AimKeys()
{
    if (hAimKey == 0) ABotKey = VK_LSHIFT;
    if (hAimKey == 1) ABotKey = VK_CAPITAL;
    if (hAimKey == 2) ABotKey = VK_LBUTTON;
    if (hAimKey == 3) ABotKey = VK_RBUTTON;
    if (hAimKey == 4) ABotKey = 'X';
    if (hAimKey == 5) ABotKey = 'F';
    if (hAimKey == 6) ABotKey = VK_MENU;
    if (hAimKey == 7) ABotKey = VK_SPACE;
    if (hAimKey == 8) ABotKey = VK_CONTROL;
    if (hAimKey == 9) ABotKey = VK_MBUTTON;
    if (hAimKey == 10) ABotKey = VK_XBUTTON1;
    if (hAimKey == 11) ABotKey = VK_XBUTTON2;
}

struct FunctionMenu
{
	FunctionMenu() { }

	struct Esp
	{
		DWORD On = 1, Line, Box, BoxType, Skeleton, Distance = 1, InRadius = 1, Name = 1, NamesInRadius = 1, HP;
	} PlayerEsp;

    struct Tree
    {
        DWORD On;
    } TreeEsp;

    struct Minerals
    {
        DWORD On;
    } MineralEsp;

    struct Bush
    {
        DWORD On;
    } BushEsp;

	struct Creature
	{
        DWORD On = 1, Alligator, Bear, Bison, Boar, Cow, ElementalBear, ElementalWolf, Elk, ForestElemental, Goat, Leopard, Lion, Lynx, Named, Piglet, Rabbit, Sheep, Turkey, TurkeyNest, Wolf, Distance, LvlValueMin;
	} CreatureEsp;

	struct Aim
	{
        DWORD On, FOVCircle = 1;
	} AimBot;

	struct Others
	{
        DWORD Speed = 1, FPS = 1, FullScreen = 1, Chest;
	} Other;

	struct Colors
	{
		int cLine = 113, cDistance = 136, cName = 138, c2DBox = 51, cAimCircle = 136;
		/*
		113; //Red
		138; //Yellow
		9; //Blue
		52; //GreenYellow
		51; //Green
		109; //Pink
		67; //LightGreen
		*/
	} Color;
};
FunctionMenu Cheat;

int DrawNameHeight = 0;

extern "C" void menuEN()
{
	if (menu)
	{
        int DrawTextX = 10;
		int DrawTextY = 65;
		int Plus20 = 22;
        int BoxWidthMenu = 220;
        int SquareLength = 350;
            
        renderer.DrawStrokeText(DrawTextX - 5, DrawTextY, cYellow, " Main:", 15);
		renderer.DrawBox(DrawTextX - 5, DrawTextY, BoxWidthMenu, SquareLength, cBalckFilled2, 1, true);
		renderer.DrawBox(DrawTextX - 5, DrawTextY, BoxWidthMenu, SquareLength, cYellow, 1, false);

        
		auto ESP_ALL_ON = skCrypt("[NP1] ESP All >> ON");
		auto ESP_ALL_OFF = skCrypt("[NP1] ESP All >> OFF");
		renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.On ? cGreenYellow : cRed, Cheat.PlayerEsp.On ? ESP_ALL_ON : ESP_ALL_OFF, 13);
		ESP_ALL_ON.clear();
		ESP_ALL_OFF.clear();

		auto ESP_LINE_ON = skCrypt("[NP2] ESP Line >> ON");
		auto ESP_LINE_OFF = skCrypt("[NP2] ESP Line >> OFF");
		renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.Line ? cGreenYellow : cRed, Cheat.PlayerEsp.Line ? ESP_LINE_ON : ESP_LINE_OFF, 13);
		ESP_LINE_ON.clear();
		ESP_LINE_OFF.clear();

		auto ESP_DISTANCE_ON = skCrypt("[NP3] ESP Distance >> ON");
		auto ESP_DISTANCE_OFF = skCrypt("[NP3] ESP Distance >> OFF");
		renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.Distance ? cGreenYellow : cRed, Cheat.PlayerEsp.Distance ? ESP_DISTANCE_ON : ESP_DISTANCE_OFF, 13);
		ESP_DISTANCE_ON.clear();
		ESP_DISTANCE_OFF.clear();

		auto ESP_INRADIUS_ON = skCrypt("[NP4] ESP In Radius >> ON");
		auto ESP_INRADIUS_OFF = skCrypt("[NP4] ESP In Radius >> OFF");
		renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.InRadius ? cGreenYellow : cRed, Cheat.PlayerEsp.InRadius ? ESP_INRADIUS_ON : ESP_INRADIUS_OFF, 13);
		ESP_INRADIUS_ON.clear();
		ESP_INRADIUS_OFF.clear();

        auto ESP_NAMEINRADIUS_ON = skCrypt("[NP5] Player In Radius  >> ON");
        auto ESP_NAMEINRADIUS_OFF = skCrypt("[NP5] Player In Radius >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.NamesInRadius ? cGreenYellow : cRed, Cheat.PlayerEsp.NamesInRadius ? ESP_NAMEINRADIUS_ON.decrypt() : ESP_NAMEINRADIUS_OFF.decrypt(), 13);
        ESP_NAMEINRADIUS_ON.clear();
        ESP_NAMEINRADIUS_OFF.clear();

		auto ESP_NAME_ON = skCrypt("[NP6] ESP Name >> ON");
		auto ESP_NAME_OFF = skCrypt("[NP6] ESP Name >> OFF");
		renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.Name ? cGreenYellow : cRed, Cheat.PlayerEsp.Name ? ESP_NAME_ON : ESP_NAME_OFF, 13);
		ESP_NAME_ON.clear();
		ESP_NAME_OFF.clear();     

		auto OTHER_SPEED_ON = skCrypt("[NP7] Speed >> ON");
		auto OTHER_SPEED_OFF = skCrypt("[NP7] Speed >> OFF");
		renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.Other.Speed ? cGreenYellow : cRed, Cheat.Other.Speed ? OTHER_SPEED_ON : OTHER_SPEED_OFF, 13);
		OTHER_SPEED_ON.clear();
		OTHER_SPEED_OFF.clear();

        auto AIM_ON = skCrypt("[NP8] Aim >> ON");
        auto AIM_OFF = skCrypt("[NP8] Aim >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.AimBot.On ? cGreenYellow : cRed, Cheat.AimBot.On ? AIM_ON : AIM_OFF, 13);
        AIM_ON.clear();
        AIM_OFF.clear();

        auto ESP_HP_ON = skCrypt("[NP9] ESP Player HP >> ON");
        auto ESP_HP_OFF = skCrypt("[NP9] ESP Player HP >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.HP ? cGreenYellow : cRed, Cheat.PlayerEsp.HP ? ESP_HP_ON : ESP_HP_OFF, 13);
        ESP_HP_ON.clear();
        ESP_HP_OFF.clear();
      
        auto ESP_BOX_ON = skCrypt("[NP0] ESP Box >> ON");
        auto ESP_BOX_OFF = skCrypt("[NP0] ESP Box >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.Box ? cGreenYellow : cRed, Cheat.PlayerEsp.Box ? ESP_BOX_ON : ESP_BOX_OFF, 13);
        ESP_BOX_ON.clear();
        ESP_BOX_OFF.clear();

        auto ESP_BOX_TYPE_B = skCrypt("[F8] Box2D");
        auto ESP_BOX_TYPE_C = skCrypt("[F8] Box Corner");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cGreenYellow, Cheat.PlayerEsp.BoxType ? ESP_BOX_TYPE_B : ESP_BOX_TYPE_C, 13);
        ESP_BOX_TYPE_B.clear();
        ESP_BOX_TYPE_C.clear();

        auto ESP_Skeleton_ON = skCrypt("[F7] ESP Skeleton >> ON");
        auto ESP_Skeleton_OFF = skCrypt("[F7] ESP Skeleton >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.PlayerEsp.Skeleton ? cGreenYellow : cRed, Cheat.PlayerEsp.Skeleton ? ESP_Skeleton_ON : ESP_Skeleton_OFF, 13);
        ESP_Skeleton_ON.clear();
        ESP_Skeleton_OFF.clear();

        //KeyInfoMenu
        DrawTextX = BoxWidthMenu + 20;

        DrawTextY = 65;
        int BoxWidthKeyInfo = 250;

        renderer.DrawStrokeText(DrawTextX - 5, DrawTextY, cYellow, " Settings:", 15);
        renderer.DrawBox(DrawTextX - 5, DrawTextY, BoxWidthKeyInfo, SquareLength, cBalckFilled2, 1, true);
        renderer.DrawBox(DrawTextX - 5, DrawTextY, BoxWidthKeyInfo, SquareLength, cYellow, 1, false);

        char wÑ1[64], wÑ2[64], wÑ3[64], wÑ4[64], wÑ5[64], wÑ6[64], wÑ7[64], wÑ8[64], wÑ9[64], wÑ10[64], wÑ11[64], wÑ12[64], wÑ13[64], wÑ14[64], wÑ15[64], wÑ16[64];

        auto dwÑ1 = skCrypt("[W+4'+/-'] Warning Distance %i");
        sprintf_s(wÑ1, dwÑ1, warningDistance);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cWhite, wÑ1, 13);
        dwÑ1.clear();

        /*auto dwÑ2 = skCrypt("[S+4'+/-'] Attack Speed | x%.1f");
        sprintf_s(wÑ2, dwÑ2, attackSpeed);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cWhite, wÑ2, 13);
        dwÑ2.clear();*/

        auto dwÑ3 = skCrypt("[S+F2'+/-'] Speed F5 | x%.2f");
        sprintf_s(wÑ3, dwÑ3, f2Speed);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cWhite, wÑ3, 13);
        dwÑ3.clear();

        renderer.DrawLine(DrawTextX + 15, DrawTextY + Plus20 - 2, BoxWidthKeyInfo * 1.8, DrawTextY + Plus20 - 2, cWhite, 1);

        auto AIM_CIRCLE_ON = skCrypt("[C+2] Aim Circle >> ON");
        auto AIM_CIRCLE_OFF = skCrypt("[C+2] Aim Circle >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.AimBot.FOVCircle ? cGreenYellow : cRed, Cheat.AimBot.FOVCircle ? AIM_CIRCLE_ON : AIM_CIRCLE_OFF, 13);
        AIM_CIRCLE_ON.clear();
        AIM_CIRCLE_OFF.clear();

        char wAimCircleFOV[64];
        auto cAimCircleFOV = skCrypt("[C+3'+/-'] Aim Circle FOV >> %i");
        sprintf_s(wAimCircleFOV, cAimCircleFOV, AFOV);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cYellow, wAimCircleFOV, 13);
        cAimCircleFOV.clear();

        auto AimKey1 = skCrypt("[K+1] Aim Key [SHIFT]");
        auto AimKey2 = skCrypt("[K+1] Aim Key [CAPS]");
        auto AimKey3 = skCrypt("[K+1] Aim Key [Left MOUSE]");
        auto AimKey4 = skCrypt("[K+1] Aim Key [Right MOUSE]");
        auto AimKey5 = skCrypt("[K+1] Aim Key [X]");
        auto AimKey6 = skCrypt("[K+1] Aim Key [F]");
        auto AimKey7 = skCrypt("[K+1] Aim Key [ALT]");
        auto AimKey8 = skCrypt("[K+1] Aim Key [SPACE]");
        auto AimKey9 = skCrypt("[K+1] Aim Key [CTRL]");
        auto AimKey10 = skCrypt("[K+1] Aim Key [Midle MOUSE]");
        auto AimKey11 = skCrypt("[K+1] Aim Key [XB1 MOUSE]");
        auto AimKey12 = skCrypt("[K+1] Aim Key [XB2 MOUSE]");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.AimBot.On ? cHotPink : cRed, hAimKey == 0 ? AimKey1.decrypt() : hAimKey == 1 ? AimKey2.decrypt() : hAimKey == 2 ? AimKey3.decrypt() : hAimKey == 3 ? AimKey4.decrypt() : hAimKey == 4 ? AimKey5.decrypt() : hAimKey == 5 ? AimKey6.decrypt() : hAimKey == 6 ? AimKey7.decrypt() : hAimKey == 7 ? AimKey8.decrypt() : hAimKey == 8 ? AimKey9.decrypt() : hAimKey == 9 ? AimKey10.decrypt() : hAimKey == 10 ? AimKey11.decrypt() : hAimKey == 11 ? AimKey12.decrypt() : AimKey1.decrypt(), 13);
        AimKey1.clear();
        AimKey2.clear();
        AimKey3.clear();
        AimKey4.clear();
        AimKey5.clear();
        AimKey6.clear();
        AimKey7.clear();
        AimKey8.clear();
        AimKey9.clear();
        AimKey10.clear();
        AimKey11.clear();
        AimKey12.clear();

        renderer.DrawLine(DrawTextX + 15, DrawTextY + Plus20 - 2, BoxWidthKeyInfo * 1.8, DrawTextY + Plus20 - 2, cWhite, 1);

        auto ASC_ON = skCrypt("[J+4] Anti Screen Capture >> ON");
        auto ASC_OFF = skCrypt("[J+4] Anti Screen Capture >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, AntiScreenshot ? cGreenYellow : cRed, AntiScreenshot ? ASC_ON : ASC_OFF, 13);
        ASC_ON.clear();
        ASC_OFF.clear();

        char wRenderingDelay[64];
        auto cRenderingDelay = skCrypt("[J+5'+/-'] Rendering Delay >> %i");
        sprintf_s(wRenderingDelay, cRenderingDelay, rendererSleep);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cYellow, wRenderingDelay, 13);
        cRenderingDelay.clear();

        auto VSYNC_ON = skCrypt("[V+ENTER] Vertical Sync >> ON");
        auto VSYNC_OFF = skCrypt("[V+ENTER] Vertical Sync >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, VSync ? cGreenYellow : cRed, VSync ? VSYNC_ON : VSYNC_OFF, 13);
        VSYNC_ON.clear();
        VSYNC_OFF.clear();

        auto RAM_FPS_ON = skCrypt("[F+2] RAM FPS >> ON");
        auto RAM_FPS_OFF = skCrypt("[F+2] RAM FPS >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.Other.FPS ? cGreenYellow : cRed, Cheat.Other.FPS ? RAM_FPS_ON.decrypt() : RAM_FPS_OFF.decrypt(), 13);
        RAM_FPS_ON.clear();
        RAM_FPS_OFF.clear();

        auto FULL_SCREEN_ON = skCrypt("[F+3] Full screen >> ON");
        auto FULL_SCREEN_OFF = skCrypt("[F+3] Full screen >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.Other.FullScreen ? cGreenYellow : cRed, Cheat.Other.FullScreen ? FULL_SCREEN_ON.decrypt() : FULL_SCREEN_OFF.decrypt(), 13);
        FULL_SCREEN_ON.clear();
        FULL_SCREEN_OFF.clear();

        renderer.DrawLine(DrawTextX + 15, DrawTextY + Plus20 - 2, BoxWidthKeyInfo * 1.8, DrawTextY + Plus20 - 2, cWhite, 1);

        auto LockKeys_ON = skCrypt("[ALT+L+M] Lock Keys >> ON");
        auto LockKeys_OFF = skCrypt("[ALT+L+M] Lock Keys >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, lockMenu ? cGreenYellow : cRed, lockMenu ? LockKeys_ON : LockKeys_OFF, 13);
        LockKeys_ON.clear();
        LockKeys_OFF.clear();

        auto Charge_ON = skCrypt("[ALT+C] Animation Charge >> ON");
        auto Charge_OFF = skCrypt("[ALT+C] Animation Charge >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, bCharge ? cGreenYellow : cRed, bCharge ? Charge_ON : Charge_OFF, 13);
        Charge_ON.clear();
        Charge_OFF.clear();

        auto dwÑ17_ON = skCrypt("[J+1] Manual Cheat Size >> ON");
        auto dwÑ17_OFF = skCrypt("[J+1] Manual Cheat Size >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, ManualW_H ? cGreenYellow : cRed, ManualW_H ? dwÑ17_ON : dwÑ17_OFF, 13);
        dwÑ17_ON.clear();
        dwÑ17_OFF.clear();

        char wManualWidth[64];
        auto cManualWidth = skCrypt("[J+2'+/-'] Manual Width >> %i");
        sprintf_s(wManualWidth, cManualWidth, (int)ManualWidth);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cYellow, wManualWidth, 13);
        cManualWidth.clear();

        char wManualHeight[64];
        auto cManualHeight = skCrypt("[J+3'+/-'] Manual Height >> %i");
        sprintf_s(wManualHeight, cManualHeight, (int)ManualHeight);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, cYellow, wManualHeight, 13);
        cManualHeight.clear();

        //Resources
        DrawTextX = BoxWidthMenu + 20 + BoxWidthKeyInfo + 10;
        DrawTextY = 65;
        int BoxWidthResource = 210;
        DrawNameHeight = DrawTextX + BoxWidthResource;

        renderer.DrawStrokeText(DrawTextX - 5, DrawTextY, cYellow, " Resources/Creatures:", 15);
        renderer.DrawBox(DrawTextX - 5, DrawTextY, BoxWidthResource, SquareLength, cBalckFilled2, 1, true);
        renderer.DrawBox(DrawTextX - 5, DrawTextY, BoxWidthResource, SquareLength, cYellow, 1, false);

        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.TreeEsp.On ? cGreenYellow : cRed, Cheat.TreeEsp.On ? skCrypt("[R+2] Tree >> ON").decrypt() : skCrypt("[R+2] ESP Tree >> OFF").decrypt(), 13);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.BushEsp.On ? cGreenYellow : cRed, Cheat.BushEsp.On ? skCrypt("[R+3] Bush >> ON").decrypt() : skCrypt("[R+3] ESP Bush >> OFF").decrypt(), 13);
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.MineralEsp.On ? cGreenYellow : cRed, Cheat.MineralEsp.On ? skCrypt("[R+4] Mineral >> ON").decrypt() : skCrypt("[R+4] ESP Mineral >> OFF").decrypt(), 13);

        auto ESP_CHEST_ON = skCrypt("[T+3] Chest >> ON");
        auto ESP_CHEST_OFF = skCrypt("[T+3] Chest >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.Other.Chest ? cGreenYellow : cRed, Cheat.Other.Chest ? ESP_CHEST_ON.decrypt() : ESP_CHEST_OFF.decrypt(), 13);
        ESP_CHEST_ON.clear();
        ESP_CHEST_OFF.clear();

        auto ESP_MOB_ON = skCrypt("[T+2] MOB >> ON");
        auto ESP_MOB_OFF = skCrypt("[T+2] MOB >> OFF");
        renderer.DrawStrokeText(DrawTextX, DrawTextY = DrawTextY + Plus20, Cheat.CreatureEsp.On ? cGreenYellow : cRed, Cheat.CreatureEsp.On ? ESP_MOB_ON.decrypt() : ESP_MOB_OFF.decrypt(), 13);
        ESP_MOB_ON.clear();
        ESP_MOB_OFF.clear();
	}
}

extern "C" DWORD Buttons(LPVOID in)
{
	while (true)
	{
        //deleted
		Sleep(1);
	}
	return 0;
}
//deleted