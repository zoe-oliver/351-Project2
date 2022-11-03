#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/

int main (int argc, char **argv)
{
 int listenfd, connfd, n;
 pid_t childpid;
 socklen_t clilen;
 char buf[MAXLINE];
 struct sockaddr_in cliaddr, servaddr;

 int fd[2];
 pipe(fd);

 int id = fork();

  /*check if it is a parent or a child */

 if(id == 0){
    //child reading from pipe
    close(fd[1]);
    char concat_str[100];

    read(fd[0], concat_str, 100);

    int k = strlen(concat_str);
    int i;
    for (i = 0; i < strlen(fixed_str); i++) {
      concat_str[k++] = fixed_str[i];
    }
    //concat_str[k] = '\0';

    close(fd[0]);
    close(fd[1]);

    //child writing to pipe
    write(fd[1], concat_str, strlen(concat_str) + 1); //check for error buf + 1, might be wrong length
    close(fd[1]);
 } else {
    //writing to pipe
    char concat_str[100];
    close(fd[0]);

    write(fd[1], buf, strlen(buf) + 1); //check for error buf + 1, might be wrong length
    close(fd[1]);
    wait(NULL);
    close(fd[1]);

    read(fd[1], concat_str, 100);
    printf("Concatenated string %s\n", concat_str);
    close(fd[0]);
 }

 //Create a socket for the server
 //If sockfd<0 there was an error in the creation of the socket
//  if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
//   perror("Problem in creating the socket");
//   exit(2);
//  }


//  //preparation of the socket address
//  servaddr.sin_family = AF_INET;
//  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//  servaddr.sin_port = htons(SERV_PORT);

//  //bind the socket
//  bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

//  //listen to the socket by creating a connection queue, then wait for clients
//  listen (listenfd, LISTENQ);

//  printf("%s\n","Server running...waiting for connections.");

//  for ( ; ; ) {

//   clilen = sizeof(cliaddr);
//   //accept a connection
//   connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);

//   printf("%s\n","Received request...");

//   if ( (childpid = fork ()) == 0 ) {//if itâ€™s 0, itâ€™s child process

//     printf ("%s\n","Child created for dealing with client requests");

//     //close listening socket
//     close (listenfd);

//     while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
//       printf("%s","String received from and resent to the client:");
//       puts(buf);
//       send(connfd, buf, n, 0);
//     }

//     if (n < 0)
//       printf("%s\n", "Read error");
//     exit(0);
//   }
//  close socket of the server
//  close(connfd);
 
//  }

}
