#Communications Library
This library is intended to be "cross-platform" (pretty much a shared windows/unix library) socket handler. This code is based off of the the way WPILIB handles sockets and contains definitions for certain tasks (I.E. Using port 6 for joystick communication on windows and unix). By having this library shared between two different platforms, this eliminates the need for the person writing the software to memorize which ports are used for what. Ideally this library should be fully automated and used as a library that will initialize when the robot is turned as a different process.

***

##Adding a method that hasnt been defined
>All tools in this library should share the same documentation, so this part will become repetitive among certain tools in this repo.

###Example, adding cross platform initializer:
Since sockets require initialization at runtime on the windows platform, an initializer should be added. A general rule of thumb for the way this library will handle cross-platformness is that if the function is required for one platform, it should be required on another platform for safety reasons, readability and consistency.

####Find windows definition
This part is fairly trivial, a quick google search comes up with examples on how to use the functions, microsoft will most-likely provide the documentation needed for certain functions/macros.

For initializing sockets on windows, the method `WSAStartup()` is required to run. We can also make the compiler use certain parts of the software we write using the precompiler `#ifdef`. On windows the macro definition that isolates windows machines is _WIN32 (for linux use `__linux__`). `WSAStartup()` takes two parameters, a `WORD` or a `short int`/`uint16_t` and a `WSADATA` parameter. Since this program is going to be cross-platform, we do not need to use the `WSADATA`.

####Find linux definition
There isnt any initialization needed for POSIX sockets but finding the definition is, again, fairly trivial and can be accomplished using a quick google search. Follow the steps for the windows definition.

###Add common typedefs and precompiler type definitions
Since the initializer only requires one uncommon data type, `WSADATA`, that isn't even used in our program, this step is not required in our example but is worth mentioning. In the function `rcomm_shutdown()` there is a paramter with a type `SOCKET`. `SOCKET` is a windows precompiler type definition that is used to isolate variables used with sockets. The `SOCKET` keyword is simply an `unsigned int`, but, the POSIX socket `shutdown()` method requires a signed integer type. Since we are making this platform specific, we can add a definition of `SOCKET` to the unix block of the header.
```c
#ifdef __unix__

#define SOCKET int

#endif
```

###Make our function
####Add prototype to header file
```c
int rcomm_init(void);
```

NOTE: the comm in rcomm stands for "communication", not "common"

####Define function in source file
```c
int rcomm_init(void){

    int status = 0;

    #ifdef _WIN32
    
    WSADATA wsa_data;
    status = WSAStartup(MAKEWORD(1,1), &wsa_data);

    #endif



    return status;
}
```

NOTE: There is no linux macro check, that is because linux does not require initialization. Also, status is outside of the macro check because we want to always return successful on unix systems.