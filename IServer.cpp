#include "IServer.h"
IServer::IServer()
{}
IServer::~IServer()
{}


void IServer::get_connect()
{
    // Создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(sockert_file_descriptor == -1){
        std::cout << "Socket creation failed.!" << std::endl;
        exit(1);
    }
    //
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
                       sizeof(serveraddress));
    if(bind_status == -1)  {
        std::cout << "Socket binding failed.!" << std::endl;
        exit(1);
    }
    // Поставим сервер на прием данных
    connection_status = listen(sockert_file_descriptor, 5);
    if(connection_status == -1){
        std::cout << "Socket is unable to listen for new connections.!" << std::endl;
        exit(1);
    }  else  {
        std::cout << "Server is listening for new connection: " << std::endl;
    }
    length = sizeof(client);
    connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
    if(connection == -1)  {
        std::cout << "Server is unable to accept the data from client.!" << std::endl;
        exit(1);
    }
}

void IServer::send_data_to_client(const std::string &datastr)
{
    //char* data;

    size_t data_size = datastr.size();
    //strcpy(data, datastr.c_str());
    strcpy(message, datastr.c_str());
    ssize_t bytes = write(connection, message, sizeof(message));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0)  {
        std::cout << "Data successfully sent to the client.!" << std::endl;
    }
    bzero(message, MESSAGE_LENGTH);
    //bzero(data, data_size);
}
std::string IServer::recip_mes_from_client()
{
    std::cout << "test input: ";
    std::string str;
    std::getline(std::cin,str);
    return str;
}

// std::string IServer:: recip_mes_from_client()
// {
//     bzero(message, MESSAGE_LENGTH);
//     read(connection, message, sizeof(message));// sizeof(message)
//     std::cout << "Data received from client: " <<  message << std::endl;

//     std::string received_message(message);
//     return received_message;
// }

void IServer::close_socket()
{
 // закрываем сокет, завершаем соединение
 close(sockert_file_descriptor);
}

