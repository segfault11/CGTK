//------------------------------------------------------------------------------
template<typename T>
Math::Vector4<T>& Math::Matrix4<T>::operator[](unsigned int i)
{
    ERROR_ASSERT(i < 4)
    return data_[i];
}
//------------------------------------------------------------------------------
template<typename T>
void Math::Matrix4<T>::Transpose()
{
    unsigned int k = 1;
    for (unsigned int i = 1; i < 4; i++)
    {
        for (unsigned int j = k; j < 4; j++)
        {
            T ele = (*this)[i][j];
            (*this)[i][j] = (*this)[j][i];
            (*this)[j][i] = ele;
        }
        k++;
    }
}
//------------------------------------------------------------------------------
template<typename T>
const T* Math::Matrix4<T>::GetData() const
{
    return &data_[0][0];
}
//------------------------------------------------------------------------------

