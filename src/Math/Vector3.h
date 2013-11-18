#ifndef VECTOR3_H__
#define VECTOR3_H__

#include <cmath>
#include "Tuple.h"
#include "../Error/Error.h"

template<typename T>
class CGKVector3
{
public:
    CGKVector3() {}
    CGKVector3(const T& x, const T& y, const T& z);
    ~CGKVector3() {};

    CGKVector3(const CGKVector3& orig);
    CGKVector3& operator=(const CGKVector3& orig);

    inline operator const T*() const {return data_;}
    inline operator T*() {return data_;}
        
    inline std::string ToString() const;

    // class access
    inline const T& operator[](unsigned int i) const;
    inline T& operator[](unsigned int i);

    inline const T& GetX() const {return data_[0];}
    inline const T& GetY() const {return data_[1];}
    inline const T& GetZ() const {return data_[2];}

    // vector operations
    inline CGKVector3<T> operator-(const CGKVector3<T>& v) const;
    inline CGKVector3<T> operator+(const CGKVector3<T>& v) const;
    inline CGKVector3<T> operator*(const T& a) const;
    inline CGKVector3<T>& operator+=(const CGKVector3<T>& v);
    inline CGKVector3<T> Cross(const CGKVector3<T>& v) const;
    inline T Dot(const CGKVector3<T>& v) const;

    inline void Normalize();

private:
    CGKTuple<3, T> data_;
};

typedef CGKVector3<float> CGKVector3f;
typedef CGKVector3<int> CGKVector3i;
typedef CGKVector3<unsigned int> CGKVector3ui;

void CGKMathCross(CGKVector3f& res, const CGKVector3f& a, const CGKVector3f& b);

#include "Vector3.inl" 

#endif /* end of include guard: VECTOR3_H__ */