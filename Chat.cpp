#include "Chat.h"

// Chat::Chat(const std::vector<Message> &messages, int messagesCount, const User &user, const std::vector<User> &users_base, const Message &message, const IServer &iserver, const std::string &delim) : m_messages(messages),
//     m_messagesCount(messagesCount),
//     m_user(user),
//     m_users_base(users_base),
//     m_message(message),
//     m_iserver(iserver),
//     m_delim(delim)
// {}

Chat::Chat() {}

Chat::~Chat() {}



// главный метод, который вызывает вызывает все остальные
void Chat::chat_start()
{

    m_iserver.get_connect();// подключение к серверу

    //registrator(); //вызов регистратора
   std::string recip;
    recip = m_iserver.recip_mes_from_client();
   //std::cout << "recip mess: " << recip << "\n";
    query_distributor(recip);
    //chat();

}

void Chat::chat_stop()
{
    m_iserver.close_socket();
}

int Chat::numInput() // функция проверки ввода
{
    int num;
    bool f = true;
    while (f) {
        std::cout << "Enter your choice: \n" << std::endl;
        std::cin >> num;
        if (!std::cin) {
            std::cout << "It`s not a digit" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            f = true;
        } else
            f = false;
    }
    return num;
}

// Выбор действий с пользователем.
// Регистрация, вход и выход

void Chat::registrator()
{
    int choice = 0;
    std::cout << "Registrator." << std::endl;
    std::cout << "What do you want? \n";

    while (choice < 4)
    {
        std::cout << "Please choose the action: 1 - register, 2 - login, 3 - login out, 4 - exit from registrator  \n"
                  << std::endl;

        choice = numInput();

        switch (choice) {
        case 1: // register
        {
            std::cout << "Reg user. Enter your name:\n";
            std::string user_name = input_user_data();
            std::cout << " Enter your password:\n";
            std::string user_password = input_user_data();

            if (regUser(user_name, user_password) == true)
            {
                std::cout << "User registred sucsefully!" << std::endl;
                // choice = 4;
            }
            else
            {
                std::cout << "User not register!" << std::endl;
            }
            break;
        }

        case 2: //login
        {
            std::string name = input_user_data();
            std::string pass = input_user_data();
            logUser(name, pass);
            break;
        }

        case 3: // logout
        {
            //logOutUser(m_user);
            break;
        }

        case 4: // out of reg
        {
            choice = 4;
            break;
        }

        default:
        {
            std::cout << "Incorrect input!\n";
            break;
        }
        }
        std::cout << "Done!\n";
    }
}

void Chat::setAdmin() ///????
{
    m_users_base.push_back(User("Admin", "qwerty"));

}

std::string Chat::input_user_data() // ввод данных
{
    std::string user_data;
    std::cin >> user_data;
    return user_data;
}

//проверка пользователей на сервере
// false == есть в базе
// true  == нет  в базе
bool Chat::checkUser(std::string user_login)
{
    size_t usersCount = m_users_base.size();
    for (size_t iii = 0; iii <= usersCount; ++iii) {
        std::string userName = m_users_base[iii].getUser();
        if (userName == user_login)
            return false;
    }
    return true;
}


bool Chat::checkPassword(User user, std::string password) ////
{
    if (user.getPassword() == password) {
        std::cout << "Welcome to chat! \n";
        return true;
    } else {
        std::cout << "Incorrect password! \n";
        user.setActiveUser(false);
        return false;
    }
}

bool Chat::regUser(std::string user_name, std::string user_password)
{
    User temp_user;

    if(checkUser(user_name) == false) // false - такого пользователя не существует, можно регистрировать
    {
        //добавляем данные о пользователе
        temp_user.setName(user_name);
        temp_user.setPassword(user_password); //добавить проверку и шифрование
        temp_user.setActiveUser(false);
        temp_user.setAuthStatus(true);
        m_users_base.push_back(temp_user); // добавляем пользователя в базу
        return true;
    }

    else
    {
        std::cout << "A user with name " << user_name << "already exists! Choose another name or Login. \n ";
        return false;
    }
}


User Chat::logUser(std::string name, std::string password)
{
    size_t usersCount = m_users_base.size();
    for(size_t i =0; i <= usersCount; ++i)
    {
        if(m_users_base[i].getUser()== name && m_users_base[i].getPassword() == password)
        {
            m_users_base[i].setActiveUser(true);
            return m_users_base[i];
        }
    }
    return m_users_base[0];
}



// void  Chat::logOutUser(User user) // доработать
// {
//     user.setAuthStatus(false);
//     std::string head = "log_offf"; // для идентификации пакета
//     m_iserver.send_data_to_client(head); // подтверждение запроса на выход

// }


Message Chat::send_message()
{

    std::string name = m_user.getUser();
    m_message.set_author(name);

    m_message.writeMessage();

    std::string message_to_send =  m_message.get_author() + m_delim +  m_message.get_message();
    m_iserver.send_data_to_client(message_to_send);

    return m_message;
}

Message Chat::recip_message()
{
    std::string rec_serv =  m_iserver.recip_mes_from_client();
    std::string name =str_subst_start(rec_serv);
    std::string mess = str_subst_end(rec_serv);

    Message msg(name, mess);
    return msg;
}

std::string Chat::str_subst_end(std::string mixed_string)
{
    size_t position = mixed_string.find(m_delim);
    size_t lenght = m_delim.size();
    std::string clear_string = mixed_string.substr(position+lenght, -1);
    return clear_string;
}


std::string Chat::str_subst_start(std::string mixed_string)
{
    //size_t position = mixed_string.find(m_delim);
    std::string clear_string = mixed_string.substr(0, mixed_string.find(m_delim));
    return clear_string;
}

std::string Chat::cache_str(std::string str)
{
    size_t pos = str.find(m_delim);
    std::string result;
    for(size_t i = 0; i < pos; ++i)
    {
        result.push_back(str[i]);
    }
    return result;
}

void Chat::query_distributor(std::string query_from_client)
{
    std::cout<<"query: " << query_from_client << "\n";
    std::string str_query = str_subst_start(query_from_client);
    //std::string str_query;
    //str_query = cache_str(query_from_client);

    std::cout<< "cathed string: " << str_query;

    std::string check = "check";
    if(str_query == check)
    {
        std::string substr = str_subst_end(query_from_client);

        bool check = checkUser(substr);
        if(check == false)
        {
           m_iserver.send_data_to_client("check_ok");
        }
        else
        {
            m_iserver.send_data_to_client("check_no");
        }
    }

    else if(str_query == "reg")
    {
            std::string name = str_subst_end(query_from_client);
            std::string pass = str_subst_end(name);
            if(regUser(name, pass))
            {
                m_iserver.send_data_to_client("reg_ok");
            }

            else
            {
                m_iserver.send_data_to_client("reg_no");
            }
    }

    else if(str_query == "log")
    {
            User temp_user;
            std::string name = str_subst_end(query_from_client);
            std::string pass = str_subst_end(name);
          temp_user = logUser(name, pass);
            if(temp_user.getActiveUser() == true)
            {
                m_iserver.send_data_to_client("log_ok");
            }

            else
            {
                m_iserver.send_data_to_client("log_no");
            }
    }
    else if(str_query == "log_off")
    {

    }

    else if(str_query == "chat_start")
    {
        chat();

    }
else
    {
        std::cout << "\n error";
    }

}


void Chat::chat() // чат для общения пользователей
{
    std::cout<< "Let`s get start to chat!\n";
    std::cout<< "Send end to exit\n";
    std::string head_st = "chat_ok"; // идентификатор для chat start

    m_iserver.send_data_to_client(head_st); // отправка запроса на старт чата
        //m_user.showUser();
        bool work_chat = true;
        std::string end_waiting = "end";
        while (true)
        {
            m_message = send_message();
            m_messages.push_back(m_message); // отправляем сообщение и кладем его в массив сообщений

            if(m_message.get_message() == end_waiting)
            {
                break;
            }

            m_message = recip_message();  // получаем сообщение, показываем и кладем его в массив сообщений
            m_message.showMessage();
            m_messages.push_back(m_message);

            if(m_message.get_message() == end_waiting) // дубль, чтобы после каждого сообщ  выйти
            {
                break;
            }
        }

        std::cout<< "Chat closed";
        std::string head_end = "chat_end"; // идентификатор для chat end
        m_iserver.send_data_to_client(head_end); // отправка запроса на старт чата
}


