#pragma once

#include "Vector3.h"

class OMatrix4;

class OVector4
{
	friend class OMatrix4;
public:
        struct t_vector4 {
                OVector3 vec3_;
                float w_;
        };
public:
//constructors
	OVector4();
	OVector4(float, float, float, float);
	OVector4(const OVector3&, float);
	OVector4(const OVector4&);
	~OVector4();
//access functions
	OVector4& operator=(const OVector4&);
	float& operator[](int);
	inline float& X(){return x_;}
	inline float& Y(){return y_;}
	inline float& Z(){return z_;}
	inline float& W(){return w_;}
        inline OVector3& V3() {return *(OVector3*)this;}
        inline OVector3  V3() const {return *(OVector3*)this;}
	void Print();
//math operators
	OVector4 operator+(const OVector4&) const;
	OVector4 operator-(const OVector4&) const;
	OVector4 operator*(const float&) const;
	OVector4 operator*(const OMatrix4&) const;
	float Dot(const OVector4&) const;
	inline float FastNorm() const{return SQRT(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);}
	inline float Norm() const {return sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);}
	// 1 / FastNorm
	inline float FastInvertNorm() {return RSQRT(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);}
protected:
//data
	union {
		float vec_[4];
		
		struct {
			float x_, y_, z_, w_; 
		};
	};
};

OVector4 operator*(const float&, const OVector4&);
