/*!
** Description of an Object
**    
** @since 2013-09-12
*/
#ifndef IOBJECT_H__
#define IOBJECT_H__
 
namespace APP
{
    class IObject
    {
    public:
        IObject() {};
        ~IObject() {};
    
        virtual void Update();
    };
}

 
#endif /* end of include guard: IOBJECT_H__ */