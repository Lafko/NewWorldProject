#pragma once

#include <math.h>
#include <C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9math.h>
#include "structs.h"

map<DWORD, ID2D1Bitmap*> TexturesFactionMap;

extern "C" void LoadImageFile(const char* itemName, DWORD factionId)
{
	//deleted
}

extern "C" void LoadTexturesImage()
{
	//deleted

void LoadResources()
{
	//deleted
}

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FTransform
{
	FQuat q;
	FVector t;

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX Result;
		FVector v2; 
		v2.x = this->q.x + this->q.x;
		v2.y = this->q.y + this->q.y;
		v2.y = this->q.z + this->q.z;

		float xx = 1 - v2.x * this->q.x;        float yy = v2.y * this->q.y;        float xw = v2.x * this->q.w;
		float xy = v2.y * this->q.x;            float yz = v2.z * this->q.y;        float yw = v2.y * this->q.w;
		float xz = v2.z * this->q.x;            float zz = v2.z * this->q.z;        float zw = v2.z * this->q.w;

		Result.m[0][0] = (1 - yy - zz);                Result.m[0][1] = (xy - zw);                Result.m[0][2] = (xz + yw);        Result.m[0][3] = (this->t.x);
		Result.m[1][0] = (xy + zw);                    Result.m[1][1] = (xx - zz);                Result.m[1][2] = (yz - xw);        Result.m[1][3] = (this->t.y);
		Result.m[2][0] = (xz - yw);                    Result.m[2][1] = (yz + xw);                Result.m[2][2] = (xx - yy);        Result.m[2][3] = (this->t.z);

		return Result;
	}
};

D3DXMATRIX Matrix(FVector rot)
{
	auto origin = FVector(0, 0, 0);
	rot.z = 0;
	float radPitch = (rot.x * M_PI / 180.f);
	float radYaw = (rot.y * M_PI / 180.f);
	float radRoll = (rot.z * M_PI / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

bool WorldToScreen(FVector WorldLocation, FVector cameraLocation, FVector cameraRotation, float fieldOfView, FVector& SLock)
{
	D3DMATRIX tempMatrix = Matrix(cameraRotation);

	auto vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	auto vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	auto vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	FVector vDelta = WorldLocation - cameraLocation;
	auto vTransformed = FVector(vDelta.Dot(vDelta, vAxisY), vDelta.Dot(vDelta, vAxisZ), vDelta.Dot(vDelta, vAxisX));
	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float ScreenCenterX = Width / 2;
	float ScreenCenterY = Height / 2;

	SLock.x = ScreenCenterX - vTransformed.x * (ScreenCenterX / tanf(fieldOfView * M_PI / 360.f)) / vTransformed.z;
	SLock.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(fieldOfView * M_PI / 360.f)) / vTransformed.z;

	/*if (SLock.x > Width || SLock.y > Height || SLock.x < 0 || SLock.y < 0)
	{
		return false;
	}*/
	return true;
}

extern "C" FVector GetBoneWithRotation(DWORD64 mesh, int id)
{
	DWORD64 bonearray = READ64(READ64(mesh + 0x0520) + 0xcb8);

	FTransform BoneMatrix = RPMFT(bonearray + (id * 0x1C));
	D3DMATRIX WorldTransform = read<D3DMATRIX>(mesh + 0x0400);
	auto BoneWorldPosition = FVector
	{
		(WorldTransform.m[0][0] * BoneMatrix.ToMatrixWithScale().m[0][3]) + (WorldTransform.m[0][1] * BoneMatrix.ToMatrixWithScale().m[1][3]) + (WorldTransform.m[0][2] * BoneMatrix.ToMatrixWithScale().m[2][3]) + WorldTransform.m[0][3],
		(WorldTransform.m[1][0] * BoneMatrix.ToMatrixWithScale().m[0][3]) + (WorldTransform.m[1][1] * BoneMatrix.ToMatrixWithScale().m[1][3]) + (WorldTransform.m[1][2] * BoneMatrix.ToMatrixWithScale().m[2][3]) + WorldTransform.m[1][3],
		(WorldTransform.m[2][0] * BoneMatrix.ToMatrixWithScale().m[0][3]) + (WorldTransform.m[2][1] * BoneMatrix.ToMatrixWithScale().m[1][3]) + (WorldTransform.m[2][2] * BoneMatrix.ToMatrixWithScale().m[2][3]) + WorldTransform.m[2][3]
	};
	return BoneWorldPosition;
}

extern "C" void Esp2DBox_5567(FVector rootHeadOut, FVector rootOut, ID2D1SolidColorBrush * col, float thickness)
{
	float Height1 = labs(rootHeadOut.y - rootOut.y);
	float Width1 = Height1 * 0.65;

	renderer.DrawBox(rootHeadOut.x - (Width1 / 2), rootHeadOut.y, Width1, Height1, col, thickness, 0);
}

extern "C" void DrawCornerBox(float X, float Y, float W, float H, ID2D1SolidColorBrush * col, float thickness, FVector rootHeadOut, FVector rootOut)
{
	float Div = W / 3;
	float Height1 = labs(rootHeadOut.y - rootOut.y);
	float Width1 = Height1 * 0.65;
	renderer.DrawBox(rootHeadOut.x - (Width1 / 2), rootHeadOut.y, Width1, Height1, cBalckFilled, thickness, 1);

	renderer.DrawLine(X, Y, X + Div, Y, col, thickness);
	renderer.DrawLine(X, Y, X, Y + Div, col, thickness);

	renderer.DrawLine(X + W - Div, Y, X + W, Y, col, thickness);
	renderer.DrawLine(X + W, Y, X + W, Y + Div, col, thickness);

	renderer.DrawLine(X, Y + H, X + Div, Y + H, col, thickness);
	renderer.DrawLine(X, Y + H, X, Y + H - Div, col, thickness);

	renderer.DrawLine(X + W - Div, Y + H, X + W, Y + H, col, thickness);
	renderer.DrawLine(X + W, Y + H, X + W, Y + H - Div, col, thickness);
}

const unsigned int DIM1 = 3;
const unsigned int DIM2 = 13;

int skeleton[DIM1][DIM2] = {
	{ 5, 43, 103 },
	{ 53, 50, 48, 49, 47, 41, 43, 42, 73, 75, 78, 76, 80 },
	{ 20, 21, 18, 19, 7, 5, 8, 24, 23, 26, 25 }
};

extern "C" void DrawSkeleton(DWORD64 mesh, ID2D1SolidColorBrush * col, float thickness, FVector CameraLocation, FVector CameraRotation, float CameraFOV, int distance, FVector neckpos)
{
	FVector pelvispos = GetBoneWithRotation(mesh, 5);

	FVector previous(0, 0, 0);
	FVector current, p1, c1;

	for (int i = 0; i < DIM1; i++)
	{
		previous = FVector(0, 0, 0);

		for (int bone = 0; bone < DIM2; bone++)
		{
			if (skeleton[i][bone])
			{
				current = skeleton[i][bone] == 103 ? neckpos : (skeleton[i][bone] == 5 ? pelvispos : GetBoneWithRotation(mesh, skeleton[i][bone]));

				if (previous.x == 0.f)
				{
					previous = current;
					continue;
				}

				if (WorldToScreen(previous, CameraLocation, CameraRotation, CameraFOV, p1) && WorldToScreen(current, CameraLocation, CameraRotation, CameraFOV, c1))
				{
					renderer.DrawLine(p1.x, p1.y, c1.x, c1.y, col, thickness);
					if (skeleton[i][bone] == 103)
					{
						renderer.DrawCircle(c1.x, c1.y, distance > 15 ? (int)((7.f / (float)distance) * 20.f) : 7, col, 0);
					}
					previous = current;
				}	
			}
		}
	}
}

bool W2SAim(FVector WorldLocation, FVector cameraLocation, FVector cameraRotation, float fieldOfView, FVector& SLock)
{
	D3DMATRIX tempMatrix = Matrix(cameraRotation);

	auto vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	auto vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	auto vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	FVector vDelta = WorldLocation - cameraLocation;
	auto vTransformed = FVector(vDelta.Dot(vDelta, vAxisY), vDelta.Dot(vDelta, vAxisZ), vDelta.Dot(vDelta, vAxisX));
	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float ScreenCenterX = Width / 2;
	float ScreenCenterY = Height / 2;

	SLock.x = ScreenCenterX - vTransformed.x * (ScreenCenterX / tanf(fieldOfView * M_PI / 360.f)) / vTransformed.z;
	SLock.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(fieldOfView * M_PI / 360.f)) / vTransformed.z;

	if (SLock.x > Width || SLock.y > Height || SLock.x < 0 || SLock.y < 0)
	{
		return false;
	}
	return true;
}

extern "C" float GetCrossDistance(float X, float Y)
{
	float ydist = (Y - (Height / 2));
	float xdist = (X - (Width / 2));
	float Hypotenuse = sqrt(pow(ydist, 2) + pow(xdist, 2));
	return Hypotenuse;
}

static DWORD64 closestPawn;
static DWORD64 closestPawnMesh;
extern "C" void GetClosestPlayerToCrossHair(FVector Pos, float& max, DWORD64 entity, DWORD64 entityMesh)
{
	float Dist = GetCrossDistance(Pos.x, Pos.y/*, Width / 2, Height / 2*/);
	if (Dist < max)
	{
		max = Dist;
		closestPawn = entity;
		closestPawnMesh = entityMesh;
	}
}

extern "C" bool InsideCircle(int xc, int yc, int r, int x, int y)
{
	int dx = xc - x;
	int dy = yc - y;
	return dx * dx + dy * dy <= r * r;
}

extern "C" void mouse_move(int dx, int dy) {
	INPUT input{ INPUT_MOUSE };
	input.mi = MOUSEINPUT{ dx, dy, 0, MOUSEEVENTF_MOVE, 0, 0 };
	SendInput(1, &input, sizeof(INPUT));
}

extern "C" void aimbot(float x, float y)
{
	float ScreenCenterX = Width / 2;
	float ScreenCenterY = Height / 2;
	int AimSpeed = 1;

	float TargetX = 0;
	float TargetY = 0;

	if ((int)x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if ((int)x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if ((int)y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}
	mouse_move(TargetX, TargetY);
}

void AimAt()
{
	FVector Location;
	Location.x = ReadFloat(closestPawn + Offset_playerLocationX);
	Location.y = ReadFloat(closestPawn + Offset_playerLocationY);
	Location.z = ReadFloat(closestPawn + Offset_playerLocationZ);

	//FVector LocalLocation = READV(cam + Offset_playerLocalLocation);

	FVector CameraLocation = READV(cam + Offset_cameraLocation);
	FVector CameraRotation = { 0, 0, 0 };
	CameraRotation.x = ReadFloat(cam + Offset_cameraRotationX);
	CameraRotation.y = ReadFloat(cam + Offset_cameraRotationY) - 270;
	CameraRotation.z = 0;

	FVector W2SA = { 0, 0, 0 };
	if (W2SAim(GetBoneWithRotation(closestPawnMesh, 103), CameraLocation, CameraRotation, CameraFOV, W2SA))
	{
		if (InsideCircle(Width / 2, Height / 2, AFOV, W2SA.x, W2SA.y))
		{
			aimbot(W2SA.x, W2SA.y);
		}
	}
}

BOOL IsElevated() {
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}