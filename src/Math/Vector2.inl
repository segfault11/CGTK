//------------------------------------------------------------------------------
template<typename T>
CGKVector2<T>::CGKVector2(const T& x, const T& y)
{
    data_[0] = x;
    data_[1] = y;
}
//------------------------------------------------------------------------------
template<typename T>
CGKVector2<T>::CGKVector2(const CGKVector2& orig)
{
    data_ = orig.data_;
}
//------------------------------------------------------------------------------
template<typename T>
CGKVector2<T>& CGKVector2<T>::operator=(const CGKVector2& orig)
{
    data_ = orig.data_;
    return *this;
}
//------------------------------------------------------------------------------
template<typename T>
std::string CGKVector2<T>::ToString() const
{
    std::stringstream s;
    s << "[x = " << data_[0] << " y = " << data_[1] << "]";
    return s.str();
}
//------------------------------------------------------------------------------