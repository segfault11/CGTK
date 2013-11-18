/*!
** A simple loader for .obj files. Supports only triangle meshes.
**
** Some remarks:
** - [Positions], [TexCoords] & [Normals] in the [File]-class have all a 
**   null vector as first element.
** - A face always also stores indices to tex coordinates and normal coordinates 
**   , if these do not exist in the .obj file the tex coords and normal  
**   coordinates are set to null tuples and reference the null vectors in the
**   [File]'s data arrays (see first remark).
** - The first material in [Materials] of the [File] class is a default material
**   for faces that were no material assigned to.
** @since 2013-09-27 
*/
/*
    TODO's:
        - For Materials
            - read textures (bump)
            - read emission and transmission
        - Specify what materials should be supported
        - Triangulate Quads if they appear in the obj file.
        - Validate Data
*/
#ifndef OBJECT_H__
#define OBJECT_H__
 
#include <string>
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>


    /// Stores the material for each face.
class CGKObjMaterial
{
public:
    CGKObjMaterial()
    :
        Name(""), 
        Ambient(CGKVector3f(0.0f, 0.0f, 0.0f)),
        Diffuse(CGKVector3f(0.0f, 0.0f, 0.0f)),
        Specular(CGKVector3f(0.0f, 0.0f, 0.0f)),
        Shininess(1.0f),
        Refraction(0.0f),
        AmbientTexture(""),
        DiffuseTexture(""),
        SpecularTexture("")
    {

    }

    std::string ToString() const
    {
        std::stringstream s;
        s << "Name: " << Name << std::endl;
        s << "Ambient Reflection:  " << Ambient.ToString() << std::endl;
        s << "Diffuse Reflection:  " << Diffuse.ToString() << std::endl;
        s << "Specular Reflection: " << Specular.ToString() << std::endl;
        s << "Shininess:  " << Shininess << std::endl;
        s << "Refraction: " << Refraction << std::endl;
        s << "AmbientTexture: " << AmbientTexture << std::endl;
        s << "DiffuseTexture: " << DiffuseTexture << std::endl;
        s << "SpecularTexture: " << SpecularTexture << std::endl;

        return s.str();
    }

    std::string Name;

    CGKVector3f Ambient;
    CGKVector3f Diffuse;
    CGKVector3f Specular;

    float Shininess;
    float Refraction;

    std::string AmbientTexture;
    std::string DiffuseTexture;
    std::string SpecularTexture;
};

/// Stores a face, that is a triangle.
class CGKObjFace
{
public:
    CGKTuple3ui PositionIndices; 
    CGKTuple3ui TexCoordsIndices; 
    CGKTuple3ui NormalIndices;
    unsigned int MaterialIndex; 
};

/// Stores the name of the group and its faces
class CGKObjGroup
{
public:
    std::string Name;
    std::vector<CGKObjFace> Faces;
};

/// Stores an Object
class CGKObjObject
{
public:
    std::string Name;
    std::vector<CGKObjGroup> Groups;
};

/// A description of an .obj file
class CGKObjFile
{
public:
    std::string Name;
    std::vector<CGKVector3f> Positions;
    std::vector<CGKVector2f> TexCoords;
    std::vector<CGKVector3f> Normals;

    std::vector<CGKObjMaterial> Materials;
    std::vector<CGKObjObject> Objects;
};

/// Loads an .obj file. Returns NULL if it fails.
///
/// @param filename Filename of the .obj file.
CGKObjFile* CGKObjLoad(const std::string& filename);

/// Releases the .obj file. 
///
/// @param file File to be released.
void CGKObjFileRelease(CGKObjFile** file);
    
/// Sets an error handler that handles in the event a line cannot be 
/// interpreted.
void SetErrorHander(
    void (*errorHandler)(
        const std::string& filename,
        unsigned int lineNumber, 
        const std::string& line
    )
);

// Dumps the file to the console.
void CGKObjDump(const CGKObjFile* file);


 
#endif /* end of include guard: OBJECT_H__ */