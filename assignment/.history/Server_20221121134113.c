// uses TCP/IP connection

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to the set port and IP:
    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    // Listen for clients:
    if (listen(socket_desc, 1) < 0)
    {
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");

    // Accept an incoming connection:
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);

    if (client_sock < 0)
    {
        printf("Can't accept\n");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Receive client's message:
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
    {
        printf("Couldn't receive\n");
        return -1;
    }
    printf("Msg from client: %s\n", client_message);

    // Respond to client:
    strcpy(server_message, "This is the server's message.");

    if (send(client_sock, server_message, strlen(server_message), 0) < 0)
    {
        printf("Can't send\n");
        return -1;
    }

    // Closing the socket:
    pclose(client_sock);
    pclose(socket_desc);

    return 0;
}
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define SER_PORT 1200
int main()
{
    int a, sersock, newsock, n;
    char str[25], str2[25];
    struct sockaddr_in seraddr;
    struct sockaddr_in cliinfo;
    socklen_t csize = sizeof(cliinfo);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(SER_PORT);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((sersock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error("\n socket");
        exit(0);
    }
    if (bind(sersock, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0)
    {
        error("\nBIND");
        exit(0);
    }
    if (listen(sersock, 1) < 0)
    {
        error("\n LISTEN");
    }
    if ((newsock = accept(sersock, (struct sockaddr *)&cliinfo, &csize)) < 0)
    {
        error("\n ACCEPT");
        exit(0);
    }
    else
        printf("\n now connected to %s\n", inet_ntoa(cliinfo.sin_addr));
    read(newsock, str, sizeof(str));
    do
    {
        printf("\n client msg:%s", str);
        printf("\n server msg:");
        scanf("%s", str2);
        write(newsock, str2, sizeof(str2));
        listen(newsock, 1);
        read(newsock, str, sizeof(str));
        n = strcmp(str, "BYE");
        a = strcmp(str2, "BYE");
    } while (n != 0 || a != 0);
    close(newsock);
    close(sersock);
    return 0;
}