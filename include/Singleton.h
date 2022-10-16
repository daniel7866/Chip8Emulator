//
//  Singleton.h
//  chip8
//
//  Created by Daniel Fogel on 14/10/2022.
//

#ifndef Singleton_h
#define Singleton_h

template <class T>
class Singleton {
protected:
    Singleton() = default;
public:
    static T& Get_Instance()
    {
        static T instance;
        return instance;
    }
    Singleton (const Singleton&) = delete;
    Singleton& operator= (const Singleton&) = delete;
    
};

#endif /* Singleton_h */
