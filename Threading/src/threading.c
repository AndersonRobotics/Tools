#include "threading.h"

#include <windows.h>

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