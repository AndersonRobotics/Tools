#include "s_handler.h" 

rcomm_socket_t sockets[SOCKET_COUNT];

void *socket_listener(void *args){

    rcomm_socket_t socket = *(*rcomm_socket_t)args;

    listen(socket.sockfd, 3);

    int size;
    socket.client = accept(socket.sockfd, (sockaddr*)socket.cli_addr, &size);

    return 0;
}

int rcomm_init(void){

    int status = 0;

    #ifdef _WIN32
    
    WSADATA wsa_data;
    status = WSAStartup(MAKEWORD(1,1), &wsa_data);

    #endif

    for(int i = 0; i < SOCKET_COUNT; i++){
        sockets[i].sockfd = socket(AF_INET, SOCK_STREAM, 0);
        sockets[i].port = i;
        sockets[i].serv_addr.sin_familiy = AF_INET;
        sockets[i].serv_addr.sin_addr.s_addr = INADDR_ANY;
        sockets[i].serv_addr.sin_port = htons(i);

        bind(
            sockets[i].sockfd,
            (struct sockaddr *)sockets[i].serv_addr, 
            sizeof(sockets[i].serv_addr));

        rthread_create(&sockets[i].thread, socket_listener, &sockets[i]);
    }

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