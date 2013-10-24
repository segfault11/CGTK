/*!
** Description of a 4x4 Matrix
**    
** @since 2013-09-10
*/
#ifndef MATRIX4_H__
#define MATRIX4_H__
 
#include "Vector4.h"
#include <string>

namespace Math
{
    /*!
    ** Declaration of a 4x4 Matrix. Note memory is layed out in ROW MAJOR 
    ** fashion.
    **    
    ** @since 2013-09-11 
    */
    template<typename T>
    class Matrix4
    {
    public:
        Matrix4() {};
        ~Matrix4() {};

        inline void Transpose();
        inline const Vector4<T>& operator[](unsigned int i) const;
        inline Vector4<T>& operator[](unsigned int i);

        /*!
        ** Gets the raw data in form of a linear array with 16 elements.
        */
        const T* GetData() const;

    private:    
        Vector4<Vector4<T> > data_;
    };

    #include "Matrix4.inl"

    typedef Matrix4<float> Matrix4F;
}
#endif /* end of include guard: MATRIX4_H__ */