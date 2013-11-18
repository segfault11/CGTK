#ifndef TUPLE_H__
#define TUPLE_H__

#include <string>
#include <sstream>
#include <iostream>

template<unsigned int DIM, typename TYPE>
class CGKTuple
{
public:
    CGKTuple();
    ~CGKTuple() {};

    CGKTuple(const CGKTuple& orig);
    CGKTuple& operator=(const CGKTuple& orig);

    inline CGKTuple<DIM, TYPE>& operator=(const TYPE& a);
    inline operator const TYPE*() const {return data_;}
    inline operator TYPE*() {return data_;}

    inline const TYPE& operator[](unsigned int i) const;
    inline TYPE& operator[](unsigned int i);

private:
    TYPE data_[DIM];
};

#include "Tuple.inl"

typedef CGKTuple<2, unsigned int> CGKTuple2ui;
typedef CGKTuple<3, unsigned int> CGKTuple3ui;

#endif /* end of include guard: TUPLE_H__ */