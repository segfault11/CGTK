#ifndef VECTOR2_H__
#define VECTOR2_H__

#include "Tuple.h"

template<typename T>
class CGKVector2
{
    public:
        CGKVector2() {}
        CGKVector2(const T& x, const T& y);
        ~CGKVector2() {};

        CGKVector2(const CGKVector2& orig);
        CGKVector2& operator=(const CGKVector2& orig);

        inline std::string ToString() const;

        inline operator const T*() const {return data_;}
        inline operator T*() {return data_;}

        inline const T& GetX() const {return data_[0];}
        inline const T& GetY() const {return data_[1];}
        inline const T& GetZ() const {return data_[2];}  
                      
    private:
        CGKTuple<2, T> data_;
};


#include "Vector2.inl" 
     
typedef CGKVector2<float> CGKVector2f;
typedef CGKVector2<int> CGKVector2i;
typedef CGKVector2<unsigned int> CGKVector2ui;

 
#endif /* end of include guard: VECTOR2_H__ */