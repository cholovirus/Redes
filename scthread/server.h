#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>   
#include <iostream>
#include <sstream> 
#include <vector>
#include <map>
using namespace std;

class Protocolo{
  string funcion;
  int msgLen;
  string msg;
  public:
  Protocolo();
  Protocolo(string inst){
    funcion =inst[0];
    msgLen = stoi(inst.substr(1,2));
    msg = inst.substr(3,inst.size()-1);
  }
  void ingresarD(string inst){
    funcion =inst[0];
    msgLen = stoi(inst.substr(1,2));
    msg = inst.substr(3,inst.size()-1);
  }
  string accion(){ return funcion;}
};


class Server{
public:
  struct sockaddr_in stSockAddr;
  int server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  int cliente;
  char buffer[256];
  string msg;
  int n;
  Protocolo msgP;
  Server(){
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(45000);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;

    bind(server,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in));
    listen(server, 10);
    cout<<"Server escuchando"<<endl;
    cliente = accept(server, NULL, NULL);
    cout<<"conectado"<<endl;
  }
  string readR(){
    recv(cliente,buffer,255,0);
    cout<<endl;
    cout<<"cliente: "<<buffer<<endl;   
    if (strcmp(buffer,"chau") == 0){
      cout<<"fin conexcion"<<endl;
      closeSokedt();
      
    }
    stringstream stream;
    string tmp;
    stream << buffer;
    stream>>tmp;
    msgP.ingresarD(tmp);
    memset(buffer,0,sizeof(buffer));
    
    return tmp;
  }

  void enviarMsgUsuario(){
    getline(cin,msg);
    send(cliente,msg.c_str(),msg.size(),0);
  }
  void whileR(){
    string stop;
    do{
      stop=readR();
    //}while(stop=="chau");
    }while(1);
  }
  void threadR(){
    thread t(&Server::whileR,this);
    t.detach();
  }
  void writeW(){
    cout<<"servidor: ";
    getline(cin,msg);
    send(cliente,msg.c_str(),msg.size(),0);
  }

  void closeSokedt(){
    
    shutdown(cliente, SHUT_RDWR);
    close(cliente);
    cliente = accept(server, NULL, NULL);
    cout<<"conectado"<<endl;
  }
  void closeServer(){
    close(server);
  }

};