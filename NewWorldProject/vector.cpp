#include "Vector.h"
#include <math.h>

FVector FVec;
FRotator Frot;

FRotator::FRotator()
{
	this->Pitch = 0.0f;
	this->Yaw = 0.0f;
	this->Roll = 0.0f;
}

FRotator::FRotator(float _Pitch, float _Yaw, float _Roll)
{
	this->Pitch = _Pitch;
	this->Yaw = _Yaw;
	this->Roll = _Roll;
}

float FRotator::GetPitch()
{
	return this->Pitch;
}

float FRotator::GetYaw()
{
	return this->Yaw;
}

float FRotator::GetRoll()
{
	return this->Roll;
}

FRotator FRotator::Normalize()
{
	while (this->Yaw > 180.0f)
		this->Yaw -= 360.0f;

	while (this->Yaw < -180.0f)
		this->Yaw += 360.0f;

	while (this->Pitch > 180.0f)
		this->Pitch -= 360.0f;

	while (this->Pitch < -180.0f)
		this->Pitch += 360.0f;
	return Normalize();
}

FRotator FRotator::operator+ (const FRotator& A)
{
	return FRotator(this->Pitch + A.Pitch, this->Yaw + A.Yaw, this->Roll + A.Roll);
}

FRotator FRotator::operator- (const FRotator& A)
{
	return FRotator(this->Pitch - A.Pitch, this->Yaw - A.Yaw, this->Roll - A.Roll);
}

FVector FRotator::ToVector()
{
	float angle, sr, sp, sy, cr, cp, cy;

	angle = this->Yaw * (M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);

	angle = this->Pitch * (M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);

	angle = this->Roll * (M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	return FVector(cp * cy, cp * sy, -sp);
}

void FRotator::GetVectors(FVector* Forward, FVector* Right, FVector* Up)
{
	static float sr, sp, sy, cr, cp, cy;
	float angle;

	angle = (float)this->Pitch * ((float)M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);


	angle = (float)this->Yaw * ((float)M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);

	angle = (float)this->Roll * ((float)M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (Forward)
		*Forward = FVector(cp * cy, cp * sy, -sp);

	if (Right)
		*Right = FVector(-1 * sr * sp * cy + -1 * cr * -sy, -1 * sr * sp * sy + -1 * cr * cy, -1 * sr * cp);

	if (Up)
		*Up = FVector(cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp);
};

FVector::FVector()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

FVector::FVector(float _X, float _Y, float _Z)
{
	this->x = _X;
	this->y = _Y;
	this->z = _Z;
}

FVector FVector::operator+ (const FVector& A)
{
	return FVector(this->x + A.x, this->y + A.y, this->z + A.z);
}

FVector FVector::operator+ (const float A)
{
	return FVector(this->x + A, this->y + A, this->z + A);
}

FVector FVector::operator+= (const FVector& A)
{
	this->x += A.x;
	this->y += A.y;
	this->z += A.z;
	return *this;
}

FVector FVector::operator+= (const float A)
{
	this->x += A;
	this->y += A;
	this->z += A;
	return *this;
}

FVector FVector::operator- (const FVector& A)
{
	return FVector(this->x - A.x, this->y - A.y, this->z - A.z);
}

FVector FVector::operator- (const float A)
{
	return FVector(this->x - A, this->y - A, this->z - A);
}

FVector FVector::operator-= (const FVector& A)
{
	this->x -= A.x;
	this->y -= A.y;
	this->z -= A.z;
	return *this;
}

FVector FVector::operator-= (const float A)
{
	this->x -= A;
	this->y -= A;
	this->z -= A;
	return *this;
}

FVector FVector::operator* (const FVector& A)
{
	return FVector(this->x * A.x, this->y * A.y, this->z * A.z);
}

FVector FVector::operator* (const float A)
{
	return FVector(this->x * A, this->y * A, this->z * A);
}

FVector FVector::operator*= (const FVector& A)
{
	this->x *= A.x;
	this->y *= A.y;
	this->z *= A.z;
	return *this;
}

FVector FVector::operator*= (const float A)
{
	this->x *= A;
	this->y *= A;
	this->z *= A;
	return *this;
}

FVector FVector::operator/ (const FVector& A)
{
	return FVector(this->x / A.x, this->y / A.y, this->z / A.z);
}

FVector FVector::operator/ (const float A)
{
	return FVector(this->x / A, this->y / A, this->z / A);
}

FVector FVector::operator/= (const FVector& A)
{
	this->x /= A.x;
	this->y /= A.y;
	this->z /= A.z;
	return *this;
}

FVector FVector::operator/= (const float A)
{
	this->x /= A;
	this->y /= A;
	this->z /= A;
	return *this;
}

bool FVector::operator== (const FVector& A)
{
	if (this->x == A.x
		&& this->y == A.y
		&& this->z == A.z)
		return true;

	return false;
}

bool FVector::operator!= (const FVector& A)
{
	if (this->x != A.x
		|| this->y != A.y
		|| this->z != A.z)
		return true;

	return false;
}

float FVector::GetX()
{
	return this->x;
}

float FVector::GetY()
{
	return this->y;
}

float FVector::GetZ()
{
	return this->z;
}

float FVector::Size()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

FRotator FRotator::CalcAngle(FVector LocalHeadPosition, FVector AimPosition)
{
	FVector vecDelta = FVector((LocalHeadPosition.x - AimPosition.x), (LocalHeadPosition.y - AimPosition.y), (LocalHeadPosition.z - AimPosition.z));
	float hyp = (float)sqrt(vecDelta.x * vecDelta.x + vecDelta.y * vecDelta.y);

	FRotator ViewAngles = FRotator();
	ViewAngles.Pitch = -(float)atan(vecDelta.z / hyp) * (float)(180.0f / M_PI);
	ViewAngles.Yaw = (float)atan(vecDelta.y / vecDelta.x) * (float)(180.0f / M_PI);
	ViewAngles.Roll = (float)0;

	if (vecDelta.x >= 0.0f)
		ViewAngles.Yaw += 180.0f;

	return ViewAngles;
}

FVector FVector::Clamp()
{
	FVector clamped;
	while (clamped.y < -180.0f)
		clamped.y += 360.0f;
	while (clamped.y > 180.0f)
		clamped.y -= 360.0f;
	if (clamped.x < -74.0f)
		clamped.x = -74.0f;
	if (clamped.x > 74.0f)
		clamped.x = 74.0f;
	return clamped;
}
FRotator FVector::ToRotator()
{
	float Yaw;
	float Pitch;
	float Forward;

	if (this->x == 0.0f
		&& this->y == 0.0f)
	{
		Yaw = 0.0f;

		if (this->z > 0.0f)
			Pitch = 90.0f;

		else
			Pitch = 270.0f;
	}
	else
	{
		if (this->x)
			Yaw = (atan2(this->y, this->x) * (180.0f / M_PI));

		else if (this->y > 0)
			Yaw = 90.0f;

		else
			Yaw = 270.0f;

		if (Yaw < 0.0f)
			Yaw += 360.0f;

		Forward = sqrt((this->x * this->x) + (this->y * this->y));
		Pitch = (atan2(this->z, Forward) * (180.0f / M_PI));

		if (Pitch < 0.0f)
			Pitch += 360.0f;
	}

	return FRotator(-Pitch, Yaw, 0);
}


FVector2D::FVector2D()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

FVector2D::FVector2D(float _X, float _Y)
{
	this->x = _X;
	this->y = _Y;
}

float FVector2D::GetX()
{
	return this->x;
}

float FVector2D::GetY()
{
	return this->y;
}

float FVector2D::Size()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}

/*
-=-=-=-=-=-=-=-=
3D to 2D Convert
-=-=-=-=-=-=-=-=
*/
float FVector::Dot(FVector pStart, FVector pEnd)
{
	return (pStart.x * pEnd.x) + (pStart.y * pEnd.y) + (pStart.z * pEnd.z);
}
float FVector::Distance(FVector v)
{
	return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
}
bool FVector::InAngle(FVector pStart, FVector pEnd, FVector pRotation, int nAngle)
{
	return (Dot((pStart - pEnd) / (pStart - pEnd).Size(), pRotation) > cos(nAngle * M_PI / 360));
}

int FVector::round(float fValue)
{
	return int(fValue + 0.5f);
}

/*
-=-=-=-=-=-=-=-=
Vector to Origin
-=-=-=-=-=-=-=-=
*/
FVector2D FVector::GetAngleToOrigin(FRotator ViewAngles, FVector vec_Start, FVector vec_End)
{
	FRotator rot_Angle = (vec_End - vec_Start).ToRotator();

	if (rot_Angle.Yaw > 180.0f) { rot_Angle.Yaw -= 360.0f; }
	else if (rot_Angle.Yaw < -180.0f) { rot_Angle.Yaw += 360.0f; }

	if (rot_Angle.Pitch > 180.0f) { rot_Angle.Pitch -= 360.0f; }
	else if (rot_Angle.Pitch < -180.0f) { rot_Angle.Pitch += 360.0f; }

	rot_Angle.Yaw -= ViewAngles.Yaw;
	rot_Angle.Pitch -= ViewAngles.Pitch;

	if (rot_Angle.Yaw > 180.0f) { rot_Angle.Yaw -= 360.0f; }
	else if (rot_Angle.Yaw < -180.0f) { rot_Angle.Yaw += 360.0f; }

	if (rot_Angle.Pitch > 180.0f) { rot_Angle.Pitch -= 360.0f; }
	else if (rot_Angle.Pitch < -180.0f) { rot_Angle.Pitch += 360.0f; }

	return FVector2D(rot_Angle.Yaw, rot_Angle.Pitch);
}