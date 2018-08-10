# Threading Library
This library is intended to be "cross-platform" (pretty much a shared windows/unix library) thread handler. This code is based off of the the way WPILIB handles threads. By having this library shared between two different platforms, this eliminates the need for software to be written twice (because this library does it for you).

***

## Adding a method that hasnt been defined
>All tools in this library should share the same documentation, so this part will become repetitive among certain tools in this repo.

### Example, adding cross platform initializer:
Since threads require initialization at runtime on the windows and linux platforms, an initializer must be added. A general rule of thumb for the way this library will handle cross-platformness is that if the function is required for one platform, it should be required on another platform for safety reasons, readability and consistency.

#### Find windows definition
This part is fairly trivial, a quick google search comes up with examples on how to use the functions, microsoft will most-likely provide the documentation needed for certain functions/macros. To create threads on windows the function `CreateThread()` is called. `CreateThread()` takes six parameters which contain the type of thread the system should create, the callback method it is using, the arguments for said callback thread, a return parameter for the id of the thread and the size of the arguments passed to the callback method.

#### Find linux definition
Initialization of POSIX threads is fairly simple, in fact it is more simple than the `CreateThread()` definition in windows. To initialize a thread, the function `pthread_create()` is used. This function takes four parameters which contain a return parameter for the thread data structure, the thread parameters, the callback function and the callback function parameters. The function returns an error code that indicated whether the thread creation was sucessful or not.

### Add common typedefs and precompiler type definitions
Threads on unix and windows differ only in one sense, where they are handled. Windows uses an integer to represent a thread ID that is passed to the system. POSIX threads are handled by the program and by the system. We want to create a common representation for this data type, so as a result, we are going to have threads represented as a `HANDLE` on windows, and as the thread structure `pthread_t` on unix.
```c
#ifdef _WIN32

typedef rthread_t HANDLE;

#endif

#ifdef __unix__

typedef rthread_t pthread_t;

#endif
```

This makes writing functions easier.

### Make our function

This function is going to be based off the POSIX definition, so as a result, the windows method will be adapted to the unix definition.

#### Add prototype to header file
```c
int rthread_create(rthread_t *thread, void *(*start), void *(*args));
```

#### Define function in source file
```c
int rthread_create(rthread_t *thread, void*(*start), void*(*args)){
    #ifdef _WIN32
    int threadid;

    *thread = CreateThread(NULL, 0, start, args, 0, &threadid);

    return *thread != 0;
    #endif

    #ifdef __unix__
    return pthread_create(thread, NULL, start, args);
    #endif
}
```