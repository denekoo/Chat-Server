#pragma once

#include "Message.h"
#include "User.h"
#include"IServer.h"


#include <ios> //used to get stream size
#include <iostream>
#include <limits> //used to get numeric limits
#include <vector>


//сервер
// хранение польз, авторизация
// беседы: общая и личная
// прием сообщ
// отправка принятых сообщ клиенту


class Chat
{
private:

    std::vector<Message> m_messages;
    int m_messagesCount = 0;
    User m_user;
    std::vector<User> m_users_base;
    Message m_message;
    IServer m_iserver;
    std::string m_delim = "|+|";


public:
    Chat();
    ~Chat();


    void chat_start(); // старт работы программы
    void chat_stop();
    int numInput(); // Функция проверки ввода, с защитой от некорректного ввода
    void registrator(); // Регисратор, выполняет все функции по регистрации и входу пользователей

    // сервер:

    void setAdmin();

    std::string input_user_data();

    bool checkUser(std::string user_login);   // проверка существования пользователя на сервере
    bool checkPassword(User user, std::string password); ////

    bool regUser(std::string user_name, std::string user_password);                  // регистратор пользователя
    User logUser(std::string name, std::string password);

    void logOutUser();               // выход

    bool chatMessage(User user); // Функция отправки сообщения от выбранного пользователя

    Message send_message();
    Message recip_message();

    std::string str_subst_end(std::string mixed_string); // возвращает строку ПОСЛЕ идентификатора типа запроса по разделителю delim
    std::string str_subst_start(std::string mixed_string); // возвращает строку ДО идентификатора типа запроса по разделителю delin

    std::string cache_str(std::string str);


    void query_distributor(std::string query_from_client); // обработчик запросов от клиента
    void chat(); //  чат для общения пользователей




};

