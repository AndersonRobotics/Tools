#ifndef _THREADING_H
#define _THREADING_H

//POSIX threads wrapped for Win32
//Pretty much a renaming scheme for unix

/*
You might be thinking to yourself: "What is the point of this"

Well, great question;
Since the socket handler has been made cross platform, it is easier to just make
a threading library that is cross platform as well, making the socket handler software
more readable as a result, also making it nice for writting cross platform applications
for specific tasks...
*/

#if defined(__unix__) && defined(_WIN32)
#error _WIN32 and __unix__ macro defined under similar platform. Only one may be defined
#endif

#if !defined(__unix__) && !defined(_WIN32)
#error The RoboThread library is intended for use with Unix and Windows platforms
#endif

#ifdef _WIN32

typedef rthread_t HANDLE;
typedef rthread_mutex_t CRITICAL_SECTION;

#endif

#ifdef __unix__

typedef rthread_t pthread_t;
typedef rthread_mutex_t pthread_mutex_t;

#endif


int rthread_create(rthread_t *thread, void *(*start), void *(*args));



#endif