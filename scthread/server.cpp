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
#include "protocolo.h"
#include "chat.h"
#include "server.h"
using namespace std;


int main(){

  //Protocolo a("L03Juan");
  Server *srv = new Server();
  
  //thread (srv->threadRr,1).detach();
 /* string msg = srv->readR();
  
  Protocolo rev(msg);
  cout<<"aquei :"<<rev.accion()<<endl;
  */


  srv->threadR();
  while(true){
    //srv->readR();
    srv->writeW();
  }
  srv->closeServer();
  return 0;
}
