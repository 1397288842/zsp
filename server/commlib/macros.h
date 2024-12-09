#ifndef __MACROS_H__
#define __MACROS_H__

//#define ParsePacket(T,V) \
//  T t;

#define SafeDelete(p) if(p) {delete p;}p = nullptr;

#define CommonNew(T) new T

#endif // __MACROS

