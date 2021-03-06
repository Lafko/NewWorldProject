#pragma once
#include "dx_renderer.h"

static ID2D1SolidColorBrush* cBalckFilled;
static ID2D1SolidColorBrush* cBalckFilled2;
static ID2D1SolidColorBrush* hp_color = 0;

static ID2D1SolidColorBrush* ColorVector[140];

static ID2D1SolidColorBrush* cAliceBlue;
static ID2D1SolidColorBrush* cAntiqueWhite;
static ID2D1SolidColorBrush* cAqua;
static ID2D1SolidColorBrush* cAquamarine;
static ID2D1SolidColorBrush* cAzure;
static ID2D1SolidColorBrush* cBeige;
static ID2D1SolidColorBrush* cBisque;
static ID2D1SolidColorBrush* cBlack;
static ID2D1SolidColorBrush* cBlanchedAlmond;
static ID2D1SolidColorBrush* cBlue;
static ID2D1SolidColorBrush* cBlueViolet;
static ID2D1SolidColorBrush* cBrown;
static ID2D1SolidColorBrush* cBurlyWood;
static ID2D1SolidColorBrush* cCadetBlue;
static ID2D1SolidColorBrush* cChartreuse;
static ID2D1SolidColorBrush* cChocolate;
static ID2D1SolidColorBrush* cCoral;
static ID2D1SolidColorBrush* cCornflowerBlue;
static ID2D1SolidColorBrush* cCornsilk;
static ID2D1SolidColorBrush* cCrimson;
static ID2D1SolidColorBrush* cCyan;
static ID2D1SolidColorBrush* cDarkBlue;
static ID2D1SolidColorBrush* cDarkCyan;
static ID2D1SolidColorBrush* cDarkGoldenrod;
static ID2D1SolidColorBrush* cDarkGray;
static ID2D1SolidColorBrush* cDarkGreen;
static ID2D1SolidColorBrush* cDarkKhaki;
static ID2D1SolidColorBrush* cDarkMagenta;
static ID2D1SolidColorBrush* cDarkOliveGreen;
static ID2D1SolidColorBrush* cDarkOrange;
static ID2D1SolidColorBrush* cDarkOrchid;
static ID2D1SolidColorBrush* cDarkRed;
static ID2D1SolidColorBrush* cDarkSalmon;
static ID2D1SolidColorBrush* cDarkSeaGreen;
static ID2D1SolidColorBrush* cDarkSlateBlue;
static ID2D1SolidColorBrush* cDarkSlateGray;
static ID2D1SolidColorBrush* cDarkTurquoise;
static ID2D1SolidColorBrush* cDarkViolet;
static ID2D1SolidColorBrush* cDeepPink;
static ID2D1SolidColorBrush* cDeepSkyBlue;
static ID2D1SolidColorBrush* cDimGray;
static ID2D1SolidColorBrush* cDodgerBlue;
static ID2D1SolidColorBrush* cFirebrick;
static ID2D1SolidColorBrush* cFloralWhite;
static ID2D1SolidColorBrush* cForestGreen;
static ID2D1SolidColorBrush* cFuchsia;
static ID2D1SolidColorBrush* cGainsboro;
static ID2D1SolidColorBrush* cGhostWhite;
static ID2D1SolidColorBrush* cGold;
static ID2D1SolidColorBrush* cGoldenrod;
static ID2D1SolidColorBrush* cGray;
static ID2D1SolidColorBrush* cGreen;
static ID2D1SolidColorBrush* cGreenYellow;
static ID2D1SolidColorBrush* cHoneydew;
static ID2D1SolidColorBrush* cHotPink;
static ID2D1SolidColorBrush* cIndianRed;
static ID2D1SolidColorBrush* cIndigo;
static ID2D1SolidColorBrush* cIvory;
static ID2D1SolidColorBrush* cKhaki;
static ID2D1SolidColorBrush* cLavender;
static ID2D1SolidColorBrush* cLavenderBlush;
static ID2D1SolidColorBrush* cLawnGreen;
static ID2D1SolidColorBrush* cLemonChiffon;
static ID2D1SolidColorBrush* cLightBlue;
static ID2D1SolidColorBrush* cLightCoral;
static ID2D1SolidColorBrush* cLightCyan;
static ID2D1SolidColorBrush* cLightGoldenrodYellow;
static ID2D1SolidColorBrush* cLightGreen;
static ID2D1SolidColorBrush* cLightGray;
static ID2D1SolidColorBrush* cLightPink;
static ID2D1SolidColorBrush* cLightSalmon;
static ID2D1SolidColorBrush* cLightSeaGreen;
static ID2D1SolidColorBrush* cLightSkyBlue;
static ID2D1SolidColorBrush* cLightSlateGray;
static ID2D1SolidColorBrush* cLightSteelBlue;
static ID2D1SolidColorBrush* cLightYellow;
static ID2D1SolidColorBrush* cLime;
static ID2D1SolidColorBrush* cLimeGreen;
static ID2D1SolidColorBrush* cLinen;
static ID2D1SolidColorBrush* cMagenta;
static ID2D1SolidColorBrush* cMaroon;
static ID2D1SolidColorBrush* cMediumAquamarine;
static ID2D1SolidColorBrush* cMediumBlue;
static ID2D1SolidColorBrush* cMediumOrchid;
static ID2D1SolidColorBrush* cMediumPurple;
static ID2D1SolidColorBrush* cMediumSeaGreen;
static ID2D1SolidColorBrush* cMediumSlateBlue;
static ID2D1SolidColorBrush* cMediumSpringGreen;
static ID2D1SolidColorBrush* cMediumTurquoise;
static ID2D1SolidColorBrush* cMediumVioletRed;
static ID2D1SolidColorBrush* cMidnightBlue;
static ID2D1SolidColorBrush* cMintCream;
static ID2D1SolidColorBrush* cMistyRose;
static ID2D1SolidColorBrush* cMoccasin;
static ID2D1SolidColorBrush* cNavajoWhite;
static ID2D1SolidColorBrush* cNavy;
static ID2D1SolidColorBrush* cOldLace;
static ID2D1SolidColorBrush* cOlive;
static ID2D1SolidColorBrush* cOliveDrab;
static ID2D1SolidColorBrush* cOrange;
static ID2D1SolidColorBrush* cOrangeRed;
static ID2D1SolidColorBrush* cOrchid;
static ID2D1SolidColorBrush* cPaleGoldenrod;
static ID2D1SolidColorBrush* cPaleGreen;
static ID2D1SolidColorBrush* cPaleTurquoise;
static ID2D1SolidColorBrush* cPaleVioletRed;
static ID2D1SolidColorBrush* cPapayaWhip;
static ID2D1SolidColorBrush* cPeachPuff;
static ID2D1SolidColorBrush* cPeru;
static ID2D1SolidColorBrush* cPink;
static ID2D1SolidColorBrush* cPlum;
static ID2D1SolidColorBrush* cPowderBlue;
static ID2D1SolidColorBrush* cPurple;
static ID2D1SolidColorBrush* cRed;
static ID2D1SolidColorBrush* cRosyBrown;
static ID2D1SolidColorBrush* cRoyalBlue;
static ID2D1SolidColorBrush* cSaddleBrown;
static ID2D1SolidColorBrush* cSalmon;
static ID2D1SolidColorBrush* cSandyBrown;
static ID2D1SolidColorBrush* cSeaGreen;
static ID2D1SolidColorBrush* cSeaShell;
static ID2D1SolidColorBrush* cSienna;
static ID2D1SolidColorBrush* cSilver;
static ID2D1SolidColorBrush* cSkyBlue;
static ID2D1SolidColorBrush* cSlateBlue;
static ID2D1SolidColorBrush* cSlateGray;
static ID2D1SolidColorBrush* cSnow;
static ID2D1SolidColorBrush* cSpringGreen;
static ID2D1SolidColorBrush* cSteelBlue;
static ID2D1SolidColorBrush* cTan;
static ID2D1SolidColorBrush* cTeal;
static ID2D1SolidColorBrush* cThistle;
static ID2D1SolidColorBrush* cTomato;
static ID2D1SolidColorBrush* cTurquoise;
static ID2D1SolidColorBrush* cViolet;
static ID2D1SolidColorBrush* cWheat;
static ID2D1SolidColorBrush* cWhite;
static ID2D1SolidColorBrush* cWhiteSmoke;
static ID2D1SolidColorBrush* cYellow;
static ID2D1SolidColorBrush* cYellowGreen;