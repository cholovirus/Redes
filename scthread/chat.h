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

class Chat{
    //vector<thread> sessiones;
    Chat();
    void login(){
    
}
void logout(){

}

void msg(){

}

void allmsg(){

}

void keepAlive(){

}

void funtion(string var){
    if(var == "L"){
        login();
    }
    if(var == "O"){
        logout();
    }
    if(var == "M"){
        msg();
    }
    if(var == "A"){
        allmsg();
    }
    if(var == "K"){
        keepAlive();
    }
}

};
