#include "s_handler.h" 

int rcomm_init(void){

    int status = 0;

    #ifdef _WIN32
    
    WSADATA wsa_data;
    status = WSAStartup(MAKEWORD(1,1), &wsa_data);

    #endif



    return status;
}

int rcomm_quit(void){

    int status = 0;

    #ifdef _WIN32
    
    status = WSACleanup();
    
    #endif

    return status;
}

int rcomm_shutdown(SOCKET sock){
    int status = 0;

    #ifdef _WIN32
    
    status = shutdown(sock, SD_BOTH);
    if (status == 0) { 
        status = closesocket(sock); 
    }

    #else

    status = shutdown(sock, SD_RDWR);
    if(status == 0){
        status = close(sock);
    }

    #endif

    return status;
}