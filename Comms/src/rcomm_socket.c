#include "rcomm_socket.h"

void *master_socket_thread(void *args){

    rcomm_socket_t socket = *(*rcomm_socket_t)args;

    listen(socket.sockfd, 3);

    int size;
    *socket.client = accept(socket.sockfd, (sockaddr*)socket.cli_addr, &size);

    int read_size;

    char data[socket.read_size];

    for(;;){
        socket = *(*rcomm_socket_t)args;
        *socket.callback(socket);
    }

    return 0;
}

rcomm_socket_t* rcomm_create_socket(int port, int data_size, void (*func)(rcomm_socket_t* socket)){
    rcomm_socket_t* socket = (rcomm_socket_t*)malloc(sizeof(rcomm_socket_t));
    
    (*socket).sockfd = socket(AF_INET, SOCK_STREAM, 0);
    (*socket).port = port;
    (*socket).serv_addr.sin_family = AF_INET;
    (*socket).serv_addr.sin_addr.s_addr = INADDR_ANY;
    (*socket).serv_addr.sin_port = htons(port);
    (*socket).callback = func;

    bind((*socket).sockfd, 
        (struct sockaddr*)sockets.serv_addr, 
        sizeof((*sockets).serv_addr));

    rthread_create((*socket).thread, master_socket_thread, socket);

}

