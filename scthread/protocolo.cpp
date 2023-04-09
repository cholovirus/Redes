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
using namespace std;

class Protocolo{
  string funcion;
  int msgLen;
  string msg;
  public:
  Protocolo(){
    funcion = "";
    msgLen=0;
    msg ="";
  }
  void recivir(string inst){
    funcion =inst[0];
    msgLen = stoi(inst.substr(1,4));
    msg = inst.substr(5,msgLen);
    cout<<funcion
  }
  string enviar(string inst){
    string F="M";
    string len=to_string(inst.size());
    string cero = "0000";
    len = cero.substr(0,cero.size()-len.size())+len;
    return F+len+inst;

  }
  string accion(){ return funcion;}
};

int main(){
  Protocolo a;
  string b=a.enviar("lee:hola");
  a.
  return 0;
}



