/*!
** Description of an OpenGL camera
**    
** @since 2013-09-10
*/
#ifndef CAMERA_H__
#define CAMERA_H__

#include "../Math/Vector3.h"
#include <string>
#include <list>

namespace APP
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        Camera(
            const Math::Vector3F& eye, 
            const Math::Vector3F& f,
            const Math::Vector3F& up,
            float fovy, 
            float aspect, 
            float near, 
            float far
        );

        /*
        ** Move camera for a distance [dist] in U, V and/or N direction, or in 
        ** an arbitrary direction.
        */
        void Move(const Math::Vector3F& dir);
        void MoveU(float dist);
        void MoveV(float dist);
        void MoveN(float dist);
        void MoveUVN(float distU, float distV, float distN);
        
        /*
        ** Rotates the camera around U, V, N using Rodrigues formula.
        */
        void RotateU(float ang);
        void RotateV(float ang);

        Camera(const Camera& orig);
        Camera& operator=(const Camera& orig);

        std::string ToString() const;

        const float* GetViewData() const;
        const float* GetPerspectiveData() const;

    private:
        void updateViewData();
        void setPerspectiveData(
            float l, float r, 
            float b, float t, 
            float n, float f
        );

        Math::Vector3F eye_;
        Math::Vector3F u_, v_, n_;
        
        float fovy_, aspect_, near_, far_;
        

        float data_[16];
        float perspectiveData_[16];
    

    };
}
 
#endif /* end of include guard: CAMERA_H__ */