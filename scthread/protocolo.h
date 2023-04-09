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
    msgLen = stoi(inst.substr(1,4));
    //msg = inst.substr(5,inst.size()-1);
  }
  void ingresarM(string inst){
    msg = inst.substr(5,inst.size()-1);
  }

  void ingresarFlen(string inst){
    funcion =inst[0];
    msgLen = stoi(inst.substr(1,4));
    //msg = inst.substr(5,inst.size()-1);
  }
  
  void userMsgUser(string inst){
    
  }
  //string accion(){ return funcion;}
};