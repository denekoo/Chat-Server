#pragma once

#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MESSAGE_LENGTH 100 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта


class IServer
{
private:
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int sockert_file_descriptor, connection, bind_status, connection_status;
    char message[MESSAGE_LENGTH];



public:
    IServer();
    ~IServer();

    void get_connect();
    void send_data_to_client(const std::string &datastr);
    std::string recip_mes_from_client();
    void  close_socket();





};
