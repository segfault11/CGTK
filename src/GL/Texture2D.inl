//------------------------------------------------------------------------------
template<GLint INTERNAL, GLenum FORMAT, GLenum TYPE>
GL::Texture2D<INTERNAL, FORMAT, TYPE>::Texture2D(
    GLsizei width, 
    GLsizei height, 
    const GLvoid* data
)
: width_(width), height_(height)
{
    glGetError();

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // this is important for textrendering!!
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        INTERNAL, 
        width, height, 
        0, 
        FORMAT, 
        TYPE, 
        data
    );

    GLenum error = glGetError();

    if (GL_NO_ERROR != error)
    {
        CGTK_REPORT("Could not init texture", CGTK_GL_ERROR);
    }    
}
//------------------------------------------------------------------------------
template<GLint INTERNAL, GLenum FORMAT, GLenum TYPE>
GL::Texture2D<INTERNAL, FORMAT, TYPE>::~Texture2D()
{
    glDeleteTextures(1, &texture_);
}
//------------------------------------------------------------------------------
template<GLint INTERNAL, GLenum FORMAT, GLenum TYPE>
void GL::Texture2D<INTERNAL, FORMAT, TYPE>::Bind(int unit) const
{
    GLint maxUnits;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxUnits);
    CGTK_ASSERT(unit < maxUnits)

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture_);
}
//------------------------------------------------------------------------------
