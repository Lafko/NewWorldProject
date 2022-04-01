#ifndef	Q_MATH_H
#define	Q_MATH_H

//Globals
#define M_PI 3.14159265358979323846f
#define ANG_CLIP( ang )		if( ang > 180.0f ) { ang -= 360.0f; } else if( ang <- 180.0f ) { ang += 360.0f; }
#define	GENTITYNUM_BITS		10
#define	MAX_GENTITIES		( 1 << GENTITYNUM_BITS )
#pragma once

struct FVector2D;
struct FVector;
struct Matrix;
struct FRotator;

struct FRotator
{
	float Pitch;
	float Yaw;
	float Roll;

	FRotator();
	FRotator(float _Pitch, float _Yaw, float _Roll);

	float GetPitch();
	float GetYaw();
	float GetRoll();

	FRotator Normalize();
	//FRotator FRotator::Normalize180 ();

	FRotator operator+ (const FRotator& A);
	FRotator operator- (const FRotator& A);

	void GetVectors(FVector* Forward, FVector* Right, FVector* Up);

	FVector ToVector();


	//FRotator ClampAngles(FRotator& Ang);
	FRotator CalcAngle(FVector LocalHeadPosition, FVector AimPosition);
};

struct FVector2D
{
	float x;
	float y;

	FVector2D();
	FVector2D(float _X, float _Y);

	float GetX();
	float GetY();

	float Size();
};

struct FVector
{
	float x;
	float y;
	float z;

	FVector();
	FVector(float _X, float _Y, float _Z);

	FVector operator+ (const FVector& A);
	FVector operator+ (const float A);
	FVector operator+= (const FVector& A);
	FVector operator+= (const float A);
	FVector operator- (const FVector& A);
	FVector operator- (const float A);
	FVector operator-= (const FVector& A);
	FVector operator-= (const float A);
	FVector operator* (const FVector& A);
	FVector operator* (const float A);
	FVector operator*= (const FVector& A);
	FVector operator*= (const float A);
	FVector operator/ (const FVector& A);
	FVector operator/ (const float A);
	FVector operator/= (const FVector& A);
	FVector operator/= (const float A);

	bool operator== (const FVector& A);
	bool operator!= (const FVector& A);

	float GetX();
	float GetY();
	float GetZ();

	float Size();

	float Size2D();
	//float Dot (const FVector V1,const FVector V2);
	FRotator ToRotator();

	/*char* toString ()
	{
		static char buffer[ 256 ];
		ZeroMemory( buffer, 256 );

		sprintf( buffer, "vector( %.2f, %.2f, %.2f )", this->X, this->Y, this->Z );
		return buffer;
	};*/
	float		Distance(FVector v);
	float		Dot(FVector pStart, FVector pEnd);
	bool		InAngle(FVector pStart, FVector pEnd, FVector pRotation, int nAngle);
	int			round(float fValue);
	FVector2D	GetAngleToOrigin(FRotator ViewAngles, FVector vec_Start, FVector vec_End);
	FVector Clamp();
	//static	float		GetDistance(centity_t* pEntity, FVector Location);
	//static	bool		WorldToScreen(FVector vec_Location, FVector& vec_Return);

	bool IsValid();
};
extern FVector FVec;
extern FRotator Frot;
#endif