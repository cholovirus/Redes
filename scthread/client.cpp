/* Client code in C */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>         // std::thread, std::this_thread::sleep_for
using namespace std;
 

class Client {
public:
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  char buffer[256];
  string msg;
  int stop=1;
  Client(){
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(45000);
    inet_pton(AF_INET,"127.0.0.1", &stSockAddr.sin_addr);//"127.0.0.1"
    connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in));
  }
  void readR(){
    recv(SocketFD,buffer,255,0);
    cout<<endl;
    cout<<"servidor: "<<buffer<<endl;
    if (strcmp(buffer,"chau") == 0){
      
      closeSokedt();
      stop=0;
    }
    memset(buffer,0,sizeof(buffer));
  }
  int stoP(){
    return stop;
  }
  void whileR(){
    int p=1;
    do{
      readR();
    }while(1);
    cout<<stop<<"fin conexcion"<<endl;
    cout<<"hola" <<stop<<endl;
  }
  void threadR(){
    thread t(&Client::whileR,this);
    t.detach();
  }

  int writeW(){
    cout<<endl;
    cout<<"cliente: ";
    getline(cin,msg);
    send(SocketFD,msg.c_str(),msg.size(),0);
    if(msg=="chau"){
      closeSokedt();
      stop=0;
      return 0;  
    }
    stop= 1;
  }

   void closeSokedt(){
    
    shutdown(SocketFD, SHUT_RDWR);
    close(SocketFD);
  }

}; 
 
int main(){
  Client *srv = new Client();
  
  srv->threadR();
  int stop=1;
  while(1){
    stop=srv->writeW();
    stop=srv->stoP();
    
  }
  //srv->closeSokedt();
  return 0;
}
//buff[n] ='\0';