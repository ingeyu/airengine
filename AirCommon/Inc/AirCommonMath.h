#ifndef COMMONMATH_HEAD_FILE
#define COMMONMATH_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

namespace Air{
	namespace	Common{
		class	Math{
		public:
// 			static	Vector3	Vector3Zero(Vector3&		val);
// 			static	Vector3	Vector3UnitScale(Vector3&	val);
// 			static	Vector3	Vector3UnitX(Vector3&		val);
// 			static	Vector3	Vector3UnitY(Vector3&		val);
// 			static	Vector3	Vector3UnitZ(Vector3&		val);
// 			static	Vector3	Vector3NegativeUnitX(Vector3& val);
// 			static	Vector3	Vector3NegativeUnitY(Vector3& val);
// 			static	Vector3	Vector3NegativeUnitZ(Vector3& val);
// 			
// 			static	Quaternion	QuatIdentity(Quaternion&	val);
// 			static	Matrix4		MatrixIdentity(Matrix4&		val);
		};

	};
	//比标准数学库中的调用快2~10倍 64位下会更明显
	inline	float	FastSin(float f){
		return	XMScalarSinEst(f);
	};
	inline	float	FastCos(float	f){
		return	XMScalarCosEst(f);
	};
	inline	float	FastASin(float	f){
		return	XMScalarASinEst(f);
	};
	inline	float	FastACos(float	f){
		return	XMScalarACosEst(f);
	};
	inline	void	FastSinCos(float*	fSin,float* fCos,float f){
		XMScalarSinCosEst(fSin,fCos,f);
	};

};
#endif // COMMONMATH_HEAD_FILE