#include "GUIElement.h"
#include "Application.h"
#include <iostream>

// DEFINITION OF THE SHADERS ///////////////////////////////////////////////////


#define TO_STRING(x) #x 

const char* VertexShader = 
    "#version 150\n"
    TO_STRING(
    uniform int ScreenWidth;
    uniform int ScreenHeight;
    uniform int AtlasWidth;
    uniform int AtlasHeight;

    in ivec4 GlyphData;  // x offset from the [Origin] and width of the glyph 

    out VertexData
    {
        float BitmapWidthNDC;  // Glyph width in NDC
        float BitmapHeightNDC; // Glyph height in NDC
        float TexStart;
        float TexEnd;        
    } 
    VertexOut;

    void main()
    {
        // compute position in NDC
        float posX = float(GlyphData.x)/ScreenWidth;
        float posY = float(GlyphData.y)/ScreenHeight;

        posX = 2.0f*posX - 1.0f;
        posY = 2.0f*posY - 1.0f;

        // compute texture coordinates
        VertexOut.TexStart = float(GlyphData.w)/AtlasWidth;
        VertexOut.TexEnd = float(GlyphData.w + GlyphData.z)/AtlasWidth;

        // compute width and height of the bmp in NDC
        VertexOut.BitmapWidthNDC = 2.0f*float(GlyphData.z)/ScreenWidth;
        VertexOut.BitmapHeightNDC = 2.0f*float(AtlasHeight)/ScreenHeight;

        gl_Position = vec4(posX, posY, 0.0f, 1.0f);
    }
    );

const char* GeometryShader = 
    "#version 150\n"
    TO_STRING(
    in VertexData
    {
        float BitmapWidthNDC;  // Glyph width in NDC
        float BitmapHeightNDC; // Glyph height in NDC
        float TexStart;
        float TexEnd;        
    } 
    VertexIn[];

    out VertexData
    {
        vec2 TexCoord;        
    } 
    VertexOut;    

    layout (points) in;
    layout (triangle_strip, max_vertices = 6) out;

    void main()
    {
        vec4 pos = gl_in[0].gl_Position;
        float w = VertexIn[0].BitmapWidthNDC;
        float h = -VertexIn[0].BitmapHeightNDC;
        float ts = VertexIn[0].TexStart;
        float te = VertexIn[0].TexEnd;


        gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(ts, 1.0f);
        EmitVertex(); 

        gl_Position = vec4(pos.x + w, pos.y, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(te, 1.0f);
        EmitVertex(); 

        gl_Position = vec4(pos.x + w, pos.y + h, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(te, 0.0f);
        EmitVertex();
        EndPrimitive();  

        gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(ts, 1.0f);
        EmitVertex(); 

        gl_Position = vec4(pos.x, pos.y + h, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(ts, 0.0f);
        EmitVertex();

        gl_Position = vec4(pos.x + w, pos.y + h, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(te, 0.0f);
        EmitVertex(); 

        EndPrimitive();         
    }
    );


const char* FragmentShader = 
    "#version 150\n"
    TO_STRING(

    uniform sampler2D Atlas;
    uniform vec3 TextColor;

    in VertexData
    {
        vec2 TexCoord;        
    } 
    VertexIn; 
    
    out vec4 FragOut;

    void main()
    {
        float alpha = texture(Atlas, VertexIn.TexCoord).r;
        vec3 textColor = vec3(
                alpha*TextColor.x, 
                alpha*TextColor.y, 
                alpha*TextColor.z
            );

        FragOut = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    );

// DEFINITION OF THE [GUIElement] //////////////////////////////////////////////


APP::GUIElement::GUIElement(
    const std::string& text, 
    const Math::Vector2I& pos,
    const TextureAtlas& atlas
)
:
     bufferObject_(NULL), atlas_(&atlas), text_(text), position_(pos)
{
    // CREATE PROGRAM ...
    program_.AttachShaderFromSource(VertexShader, GL_VERTEX_SHADER);
    program_.AttachShaderFromSource(GeometryShader, GL_GEOMETRY_SHADER);
    program_.AttachShaderFromSource(FragmentShader, GL_FRAGMENT_SHADER);
    program_.BindAttribLocation(0, "GlyphData");
    program_.BindFragDataLocation(0, "FragOutput");
    program_.Compile();

    // CONFIGURE IT ..
    program_.SetInt("ScreenWidth", APP::GetScreenWidth());
    program_.SetInt("ScreenHeight", APP::GetScreenHeight());
    program_.SetInt("AtlasHeight", atlas_->GetHeight());
    program_.SetInt("AtlasWidth", atlas_->GetWidth());
    program_.SetInt("Atlas", 1);

    // CREATE A VERTEX OBJ AND BUFFER OBJECT FOR THE GUI ELEMENT AND SAVE 
    // IT WITH THEM TO A LIST.

    vertexArray_ = new GL::VertexArray();

    // CREATE BUFFER OBJECT FOR THE GUI ELEMENT ...
    unsigned int length = text_.size();
    GLsizei size = sizeof(int)*4*length;
    int* glyphData = new int[4*length];
    int posX = position_.GetX();
    int posY = position_.GetY();

    for (unsigned int i = 0; i < length; i++)
    {
        char c = text_.c_str()[i];
        glyphData[4*i + 0] = posX + atlas_->GetBearing(c).GetX();
        glyphData[4*i + 1] = posY + atlas_->GetBearing(c).GetY();
        std::cout << glyphData[4*i + 0] << std::endl;
        std::cout << glyphData[4*i + 1] << std::endl;        
        glyphData[4*i + 2] = atlas_->GetBitmapWidth(c);
        glyphData[4*i + 3] = atlas_->GetAtlasOffX(c);
        posX += atlas_->GetAdvance(c).GetX();
        posY += atlas_->GetAdvance(c).GetY();
    }

    bufferObject_ = new GL::BufferObject(
            GL_ARRAY_BUFFER, 
            size, 
            GL_STATIC_DRAW
        );
    bufferObject_->SetData(size, glyphData);

    // ... AND ATTACH IT TO THE VERTEX ARRAY
    vertexArray_->SetAttribute(
        bufferObject_, 
        0, 4, GL_INT, GL_FALSE, 
        0, 0
    );

    delete[] glyphData;
}

APP::GUIElement::~GUIElement()
{
        delete vertexArray_;
        delete bufferObject_;
}

void APP::GUIElement::SetText(const std::string& text)
{
    // if the size of the new text is smaller or equal then the old text
    // simply override the current buffer objects memory
    if (text_.size() >= text.size())
    {
        text_ = text;
        refillBufferObject();
        return;
    }

    text_ = text;
    createVertexArray();

}

void APP::GUIElement::Draw()
{
    program_.Bind();
    atlas_->Bind(1);
    program_.SetVec3("TextColor", textColor_);
    vertexArray_->Bind();
    glDrawArrays(GL_POINTS, 0, text_.size());
}

void APP::GUIElement::refillBufferObject()
{
    // CREATE BUFFER OBJECT FOR THE GUI ELEMENT ...
    unsigned int length = text_.size();
    GLsizei size = sizeof(int)*4*length;
    int* glyphData = new int[4*length];
    int posX = position_.GetX();
    int posY = position_.GetY();

    for (unsigned int i = 0; i < length; i++)
    {
        char c = text_.c_str()[i];
        glyphData[4*i + 0] = posX + atlas_->GetBearing(c).GetX();
        glyphData[4*i + 1] = posY + atlas_->GetBearing(c).GetY();
        glyphData[4*i + 2] = atlas_->GetBitmapWidth(c);
        glyphData[4*i + 3] = atlas_->GetAtlasOffX(c);
        posX += atlas_->GetAdvance(c).GetX();
        posY += atlas_->GetAdvance(c).GetY();
    }

    bufferObject_->SetData(size, glyphData);  
    delete[] glyphData;  
}

void APP::GUIElement::createVertexArray()
{
    if (bufferObject_ != NULL)
    {
        delete bufferObject_;
    }

    unsigned int length = text_.size();
    GLsizei size = sizeof(int)*4*length;
    int* glyphData = new int[4*length];
    int posX = position_.GetX();
    int posY = position_.GetY();

    for (unsigned int i = 0; i < length; i++)
    {
        char c = text_.c_str()[i];
        glyphData[4*i + 0] = posX + atlas_->GetBearing(c).GetX();
        glyphData[4*i + 1] = posY + atlas_->GetBearing(c).GetY();
        glyphData[4*i + 2] = atlas_->GetBitmapWidth(c);
        glyphData[4*i + 3] = atlas_->GetAtlasOffX(c);
        posX += atlas_->GetAdvance(c).GetX();
        posY += atlas_->GetAdvance(c).GetY();
    }

    bufferObject_ = new GL::BufferObject(
            GL_ARRAY_BUFFER, 
            size, 
            GL_STATIC_DRAW
        );
    bufferObject_->SetData(size, glyphData);

    // ... AND ATTACH IT TO THE VERTEX ARRAY
    vertexArray_->SetAttribute(
        bufferObject_, 
        0, 4, GL_INT, GL_FALSE, 
        0, 0
    );

    delete[] glyphData;
}

