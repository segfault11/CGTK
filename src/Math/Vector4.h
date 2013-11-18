#ifndef VECTOR4_H__
#define VECTOR4_H__

#include "Tuple.h"
#include "../Error/Error.h"

template<typename T>
class CGKVector4
{
public:
    CGKVector4() {}
    CGKVector4(const T& x, const T& y, const T& z);
    ~CGKVector4() {};

    CGKVector4(const CGKVector4& orig);
    CGKVector4& operator=(const CGKVector4& orig);

    inline operator const T*() const {return data_;}
    inline operator T*() {return data_;}
        
    inline std::string ToString() const;

    inline CGKVector4<T>& operator=(const T& a);

    // class access
    inline const T& operator[](unsigned int i) const;
    inline T& operator[](unsigned int i);

    inline const T& GetX() const {return data_[0];}
    inline const T& GetY() const {return data_[1];}
    inline const T& GetZ() const {return data_[2];}
    inline const T& GetW() const {return data_[3];}

private:
    CGKTuple<4, T> data_;
};
  
#include "Vector4.inl" 
     
typedef CGKVector4<float> Vector4f;
typedef CGKVector4<int> Vector4i;
typedef CGKVector4<unsigned int> Vector4ui;

#endif /* end of include guard: VECTOR3_H__ */