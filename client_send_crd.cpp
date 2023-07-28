#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>

#include<sys/socket.h>	//socket
#include<sys/types.h>
#include<netinet/in.h>

using namespace std;
using namespace cv;

#define PORT 7200

#define FRAME_WIDTH         640
#define FRAME_HEIGHT        480

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main()
{
  int sockfd, newsockfd, portno, n, size, bytes=0, IM_HEIGHT, IM_WIDTH;;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  // Mat img;

  sockfd=socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd<0) error("ERROR opening socket");

  bzero((char*)&serv_addr, sizeof(serv_addr));
  portno = PORT;

  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=INADDR_ANY;
  serv_addr.sin_port=htons(portno);

  if(bind(sockfd, (struct sockaddr *) &serv_addr,
          sizeof(serv_addr))<0) error("ERROR on binding");


  listen(sockfd,5);
  clilen=sizeof(cli_addr);

  newsockfd=accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if(newsockfd<0) error("ERROR on accept");

  uchar sock[3];
  cout << sock <<endl;
  cout << sock+3 <<endl;

  bool running = true;

  while(running)
  {
    int x0;
    pair<int, int> recv_points;

    if ((bytes=recv(newsockfd, &recv_points, sizeof(recv_points),0))==-1) 
      error("recv failed");
    else{
      cout << recv_points.first << " ";
      cout << recv_points.second << endl;
    }
  }

  close(newsockfd);
  close(sockfd);

  return 0;
}
