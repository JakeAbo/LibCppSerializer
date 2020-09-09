# LibCppSerializer
LibCppSerializer implements a modern C++ API library which providing a generic wrapper to boost serialization library that enables to add
new classes which will easily be serialized and deserialized. 
The library provides fast runtime serialization using templates, lambdas and macros using C++ 17.

----
*Author*:      [Jack Abulafia](https://www.linkedin.com/in/jack-abulafia-463a23199/)

## Dependencies
This library requires use of boost/serialization which can be obtained from:
* <https://github.com/boostorg/serialization>

Tested on boost version 1.70.

## Building 
The library is header-only. 

## How to use
Project should include boost library and inc directory of the repository which include all necessary header files of LibCppSerializer.

## Getting Started
```cpp
#include "ObjectSerilizer.hpp"

int main(int argc, char* argv[])
{
   

    return 0;
}
```


## License 
This project is open source and freely available.

  Copyright (c) 2020, Jack Abulafia 
  All rights reserved.


