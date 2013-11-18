//------------------------------------------------------------------------------
template<typename T>
CGKVector4<T>::CGKVector4(const T& x, const T& y, const T& z)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
}
//------------------------------------------------------------------------------
template<typename T>
CGKVector4<T>::CGKVector4(const CGKVector4& orig)
{
    data_ = orig.data_;
}
//------------------------------------------------------------------------------
template<typename T>
CGKVector4<T>& CGKVector4<T>::operator=(const CGKVector4<T>& orig)
{
    data_ = orig.data_;
    return *this;
}
//------------------------------------------------------------------------------
template<typename T>
CGKVector4<T>& CGKVector4<T>::operator=(const T& a)
{
    data_ = a;
    return *this;
}
//------------------------------------------------------------------------------
template<typename T>
T& CGKVector4<T>::operator[](unsigned int i)
{
    CGK_ASSERT(i < 4)

    return data_[i];
}
//------------------------------------------------------------------------------
template<typename T>
const T& CGKVector4<T>::operator[](unsigned int i) const
{
    CGK_ASSERT(i < 4)
    
    return data_[i];
}
//------------------------------------------------------------------------------
template<typename T>
std::string CGKVector4<T>::ToString() const
{
    std::stringstream s;
    s << "[x = " << data_[0] << " y = " << data_[1] << " z = " << data_[2] << "w = " << data_[3] << "]";
    return s.str();
}
//------------------------------------------------------------------------------