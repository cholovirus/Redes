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

struct Protocolo{
  string funcion;
  int msgLen;
  string msg;
  Protocolo(){}
  Protocolo(string inst){
    funcion =inst[0];
    msgLen = stoi(inst.substr(1,4));
    //msg = inst.substr(5,inst.size()-1);
  }
  void ingresarM(string inst){
    msg = inst.substr(0,msgLen);
  }

  void ingresarFlen(string inst){
    funcion =inst[0];
    msgLen = stoi(inst.substr(1,4));
    //msg = inst.substr(5,inst.size()-1);
  }
  string msgU(){
    return msg;
  }

  string enviarML(string inst){
    string cero= "0000";
    string num = to_string(inst.size());

    cero = cero.substr(0,cero.size()-num.size()) +num;
    return "L"+cero+inst;
  }
    string completeZero(string inst){
        string cero= "0000";
        string num = to_string(inst.size());

        cero = cero.substr(0,cero.size()-num.size()) +num;
        return cero;
    }
  string enviarMU(string inst){
    string msgNick;
    string msgMen;
    int i=0;
    for (;i<inst.size();i++){
        if(inst[i] == ':'){
            //nickname de a quien le envio
            msgNick =inst.substr(0,i);
            i++;
            break;
        }
    }
    //mensaje que se envia
    //hola
    msgMen = inst.substr(i,inst.size());
    
    return "N"+completeZero(msgMen)+msgMen+completeZero(msgNick)+msgNick;
    
  }
  
};