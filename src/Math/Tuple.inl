//------------------------------------------------------------------------------
template<unsigned int DIM, typename TYPE>
CGKTuple<DIM, TYPE>::CGKTuple()
{
    for (unsigned int i = 0; i < DIM; i++)
    {
        data_[i] = 0;
    }
}
//------------------------------------------------------------------------------
template<unsigned int DIM, typename TYPE>
CGKTuple<DIM, TYPE>::CGKTuple(const CGKTuple& orig)
{
    *this = orig; 
}
//------------------------------------------------------------------------------
template<unsigned int DIM, typename TYPE>
CGKTuple<DIM, TYPE>& CGKTuple<DIM, TYPE>::operator=(const CGKTuple& orig)
{
    for (unsigned int i = 0; i < DIM; i++)
    {
        data_[i] = orig.data_[i];
    }
    return *this;    
}
//------------------------------------------------------------------------------
template<unsigned int DIM, typename TYPE>
CGKTuple<DIM, TYPE>& CGKTuple<DIM, TYPE>::operator=(const TYPE& a)
{
    for (unsigned int i = 0; i < DIM; i++)
    {
        data_[i] = a;
    }
    return *this;    
}
//------------------------------------------------------------------------------
template<unsigned int DIM, typename TYPE>
TYPE& CGKTuple<DIM, TYPE>::operator[](unsigned int i)
{
    return data_[i];
}
//------------------------------------------------------------------------------
template<unsigned int DIM, typename TYPE>
const TYPE& CGKTuple<DIM, TYPE>::operator[](unsigned int i) const
{
    return data_[i];
}
//------------------------------------------------------------------------------