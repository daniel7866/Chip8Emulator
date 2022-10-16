//
//  Instance.h
//  chip8
//
//  Created by Daniel Fogel on 14/10/2022.
//

#ifndef Instance_h
#define Instance_h

#include "Singleton.h"

template <class T>
inline T& Instance()
{
    return Singleton<T>::Get_Instance();
}

#endif /* Instance_h */
