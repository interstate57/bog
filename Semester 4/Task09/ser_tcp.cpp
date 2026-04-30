#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <libgen.h>
#include <memory>
#include <string.h>

#include "enum.h"
#include "database.h"
#include "parser.h"
// Определимся с номером порта и другими константами.
#define BUFLEN 512

// Две вспомогательные функции для чтения/записи (см. ниже)
int readFromClient (int fd, char *buf);
int writeToClient (int fd, char *buf);
io_status convert_str_to_command(char* str, command& cmd);
void convert_record_to_str(char* res, record& cmd);

static bool read_config(const char* filename, int& k1, int& m1, int& k2, int& m2) {
    const char* config_name = "config.txt";
    std::unique_ptr<char []> exe_path = std::make_unique<char []>(strlen(filename) + 1);
    if (!exe_path)
        return false;
    strcpy(exe_path.get(), filename);
    char* dir = dirname(exe_path.get());
    if (!dir)
        return false;
    printf ("Executable dir = %s\n", dir);
    size_t path_len = strlen(dir) + 1 + strlen(config_name) + 1;
    std::unique_ptr<char []> config_path = std::make_unique<char []>(path_len);
    if (!config_path)
        return false;
    snprintf(config_path.get(), path_len, "%s/%s", dir, config_name);
    printf ("Config path = %s\n", config_path.get ());
    FILE* fp = fopen(config_path.get(), "r");
    if (!fp)
        return false;

    int found = 0;
    char str[LEN];
    while (fgets(str, sizeof(str), fp)) {
        const char* p = str;
        while (p[0] == ' ' || p[0] == '\t')
            p++;
        if (p[0] == '\0' || p[0] == '\n' || p[0] == '#')
            continue;
        while (p[0]) {
            while (p[0] == ' ' || p[0] == '\t')
                p++;
            if (p[0] == '\0' || p[0] == '\n' || p[0] == '#')
                break;
            char* end = nullptr;
            long v = strtol(p, &end, 10);
            if (end == p) {
                fclose(fp);
                return false;
            }
            if (found == 0)
                k1 = (int)v;
            else if (found == 1)
                m1 = (int)v;
            else if (found == 2)
                k2 = (int)v;
            else if (found == 3)
                m2 = (int)v;
            found++;
            p = end;
            if (found >= 4)
                break;
        }
        if (found >= 4)
            break;
    }
    fclose(fp);
    return found >= 4 && k1 > 0 && m1 > 0 && k2 > 0 && m2 > 0;
}

int main (int argc, char* argv[]){
    int i, err, opt = 1;
    int sock, new_sock;
    fd_set active_set, read_set;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    char buf[BUFLEN];
    socklen_t size;
    char* name = 0;
    io_status ret;
    double t = 0;
    int res = 0;
    int k1 = 0;
    int m1 = 0;
    int k2 = 0;
    int m2 = 0;
    int PORT;
    FILE* fp;
    if (argc != 3 || !read_config(argv[0], k1, m1, k2, m2) || sscanf(argv[2], "%d", &PORT) != 1){
        printf("Usage: %s filename port\n", argv[0]);
        return 1;
    }
    name = argv[1];
    // Создаем TCP сокет для приема запросов на соединение
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror ("Server: cannot create socket");
        exit (EXIT_FAILURE);
    }
    setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof (opt));
    // Заполняем адресную структуру и
    // связываем сокет с любым адресом
    addr.sin_family = AF_INET;
    addr.sin_port = htons (PORT);
    addr.sin_addr.s_addr = htonl (INADDR_ANY);
    err = bind (sock, (struct sockaddr *) &addr, sizeof (addr));
    if (err < 0){
        perror ("Server: cannot bind socket");
        exit (EXIT_FAILURE);
    }
    // Создаем очередь на 3 входящих запроса соединения
    err = listen (sock, 3);
    if (err < 0){
        perror ("Server: listen queue failure");
        exit (EXIT_FAILURE);
    }
    // Подготавливаем множества дескрипторов каналов ввода-вывода.
    // Для простоты не вычисляем максимальное значение дескриптора,
    // а далее будем проверять все дескрипторы вплоть до максимально
    // возможного значения FD_SETSIZE.
    FD_ZERO (&active_set);
    FD_SET (sock, &active_set);
    if (!(fp = fopen(name, "r"))) return -1;
    database data(k1, m1, k2, m2);
    ret = data.get_list().read(fp);
    do{
        switch(ret){
            case io_status::success: continue;
            case io_status::wrong_file: printf("Cannot open file!\n"); break;
            case io_status::format: printf("Wrong format in the file!\n"); break;
            case io_status::eof: printf("Cannot read file!\n"); break;
            case io_status::memory: printf("Cannot allocate memory!\n"); break;
            case io_status::parsing_error: printf("Parsing error!\n"); break;
            default: break;
        }
        fclose(fp);
        return 3;
    }while(0);
    for (list2_node* curr = data.get_list().get_head(); curr; curr = curr->get_next()){
        int res_ = data.get_solo().insert(curr);
        if (res_ == -1){
            printf("ERROR\n");
            fclose(fp);
            return 4;
        }
        res_ = data.get_kirpichek_i(curr->get_group() - 1).insert(curr);
        if (res_ == -1){
            printf("ERROR\n");
            fclose(fp);
            return 4;
        }
    }
    fclose(fp);
    // Основной бесконечный цикл проверки состояния сокетов
    while (1){
        // Проверим, не появились ли данные в каком-либо сокете.
        // В нашем варианте ждем до фактического появления данных.
        read_set = active_set;
        if (select (FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0){
            perror ("Server: select failure");
            exit (EXIT_FAILURE);
        }
        // Данные появились. Проверим в каком сокете.
        for (i = 0; i < FD_SETSIZE; i++){
            if (FD_ISSET (i, &read_set)){
                if (i == sock){
                    // пришел запрос на новое соединение
                    printf("New connection required\n");
                    size = sizeof (client);
                    new_sock = accept (sock, (struct sockaddr *) &client, &size);
                    if (new_sock < 0){
                        perror ("accept");
                        exit (EXIT_FAILURE);
                    }
                    fprintf (stdout, "Server: connect from host %s, port %d.\n",
                    inet_ntoa (client.sin_addr),
                    (unsigned int) ntohs (client.sin_port));
                    FD_SET (new_sock, &active_set);
                }
                else{
                    // пришли данные в уже существующем соединени
                    printf("Existing connection wants something\n");
                    err = readFromClient (i, buf);
                    if (err < 0){
                        // ошибка или конец данных
                        close (i);
                        FD_CLR (i, &active_set);
                    }
                    else{
                        // данные прочитаны нормально
                        command cmd;
                        io_status ret = convert_str_to_command(buf, cmd);
                        if (ret != io_status::success){
                            sprintf(buf, "ERROR\n");
                            writeToClient(i, buf);
                            close (i);
                            FD_CLR (i, &active_set);
                            break;
                        }
                        cmd.print();
                        list answer;
                        switch (cmd.get_command_type()){
                            int len;
                            list_node* curr;
                            case command_type::quit:
                                t = (clock() - t) / CLOCKS_PER_SEC;
                                sprintf(buf, "1\n");
                                writeToClient(i, buf);
                                sprintf (buf, "%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);
                                answer.delete_list();
                                writeToClient (i, buf);
                                close (i);
                                FD_CLR (i, &active_set);
                                break;
                            case command_type::stop:
                                t = (clock() - t) / CLOCKS_PER_SEC;
                                sprintf(buf, "1\n");
                                writeToClient(i, buf);
                                sprintf (buf, "%s : Result = %d Elapsed = %.2f\n", argv[0], res, t);
                                answer.delete_list();
                                writeToClient (i, buf);
                                close (i);
                                FD_CLR (i, &active_set);
                                close (sock);
                                return 0;
                            case command_type::del:
                                data.delete_command(cmd);
                                break;
                            case command_type::insert:
                                data.insert_command(cmd);
                                break;
                            case command_type::select:
                                data.select_command(cmd, answer);
                                len = answer.get_length();
                                res += len;
                                sprintf(buf, "%d\n", len);
                                writeToClient(i, buf);
                                curr = answer.get_head();
                                for (;curr;curr = curr->get_next()){
                                    convert_record_to_str(buf, *curr->get_data());
                                    writeToClient(i, buf);
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
}
int readFromClient (int fd, char *buf){
    int nbytes, len, i;
    // Получаем длину сообщения
    if (read (fd, &len, sizeof (int)) != (int) sizeof (int)){
        // ошибка чтения
        perror ("read length");
        return -1;
    }
    // Здесь неплохо бы проверить размер буфера
    // Получаем len байт
    for (i = 0; len > 0; i += nbytes, len -= nbytes){
        nbytes = read (fd, buf + i, len);
        if (nbytes < 0){
            perror ("read");
            return -1;
        }
        else if (nbytes == 0){
        perror ("read truncated");
        return -1;
        }
    }
    // Длина находится в i
    if (i == 0){
        // нет данных
        fprintf (stderr, "Server: no message\n");
        return -1;
    }
    else{
        // есть данные
        fprintf (stdout, "Server got %d bytes of message: %s\n", i, buf);
        return 0;
    }
}
int writeToClient (int fd, char *buf){
    int nbytes, len, i;
    unsigned char *s;
    for (s = (unsigned char *) buf, len = 0; *s; s++, len++)
    *s = toupper (*s);
    // Длина сообщения
    len++;
    // Пересылаем длину сообщения
    if (write (fd, &len, sizeof (int)) != (int) sizeof (int)){
        perror ("write length");
        return -1;
    }
    // Пересылаем len байт
    for (i = 0; len > 0; i += nbytes, len -= nbytes){
        nbytes = write (fd, buf + i, len);
        if (nbytes < 0){
            perror ("write");
            return -1;
        }
        else if (nbytes == 0){
            perror ("write truncated");
            return -1;
        }
    }
    // Длина находится в i
    fprintf (stdout, "Write back: %s\nnbytes=%d\n", buf, i);
    return 0;
}


io_status convert_str_to_command(char* str, command& cmd){
    parser prs;
    return prs.parse(cmd, str);
}

void convert_record_to_str(char* res, record& cmd){
    sprintf(res, "%s %d %d", cmd.get_name(), cmd.get_phone(), cmd.get_group());
}
