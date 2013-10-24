/*!
** Implementation of the shaders used by the [GUIRenderer]
**    
** @since 2013-09-16 
*/
#define TO_STRING(x) #x 


// namespace APP
// {
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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

        FragOut = vec4(textColor, alpha);
    }
    );
//------------------------------------------------------------------------------
// }
