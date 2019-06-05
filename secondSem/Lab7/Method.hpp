#ifndef LAB7_METHOD_HPP
#define LAB7_METHOD_HPP

#include <functional>
#include <boost/callable_traits.hpp>

template <class MethodType, class ObjType>
class Method {

    MethodType mMethod;
    ObjType& mObject;

public:

    Method (MethodType &&method, ObjType &object)
            : mMethod (method),
              mObject (object)
    {}

    auto& object () const {
        return mObject;
    }

    auto method () const {

        return mMethod;
    }

    auto wrapperFunc () const {

        return [&] {



        };
    }


};

#endif //LAB7_METHOD_HPP
