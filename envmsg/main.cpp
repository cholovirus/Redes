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
#include "protocolo.h"

using namespace std;

struct Server{
    struct sockaddr_in stSockAddr;
    int server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int cliente;
    char buffer[256];
    string msg;
    int n;
    Protocolo protomsg;
    map<string,int> clienteConectado;
    map<int,string> nomcliente;
    Server(){
        memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
        stSockAddr.sin_family = AF_INET;
        stSockAddr.sin_port = htons(45000);
        stSockAddr.sin_addr.s_addr = INADDR_ANY;
        if(-1 == server){
            perror("can not create socket");
            exit(EXIT_FAILURE);
        }
        //Bind
        if(-1 == bind(server,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in))){
            perror("error bind failed"); 
            close(server);
            exit(EXIT_FAILURE);
        }
        //Listen
        if(-1 == listen(server, 10)){
            perror("error listen failed");
            close(server);
            exit(EXIT_FAILURE);
        }
        //cout<<"server"<<endl;
    }

    void conex(){
        cout<<"Server escuchando"<<endl;
        while(true){
            cliente = accept(server, NULL, NULL);
            cout<<"conectado"<<endl;
            if(0 > cliente) {
                perror("error accept failed");
                close(server);
                exit(EXIT_FAILURE);
            }
            
            string yi = readR();
            funtion(yi,0);
        }
    }

    string readR(){
        int n;
        //cout<<"read"<<endl;
        n = recv(cliente,buffer,5,0);
        
        stringstream stream; string tmp;
        stream << buffer; stream>>tmp;
        protomsg.ingresarFlen(tmp);
        //cout<<proto.msgLen<<endl;
        //recv(cliente,buffer,proto.msgLen,0);
        recv(cliente,buffer,protomsg.msgLen,0);

        stringstream streamtemp; string tmsg;
        streamtemp << buffer; streamtemp>>tmsg;
        protomsg.ingresarM(tmsg);
        //cout<<protomsg.msg<<endl;
        
        
        memset(buffer,0,sizeof(buffer));
        
        return tmp;
    }
    
    void threadR(int FDS){
        thread ser(&Server:: cliente_process_thread,this,FDS);
        ser.detach();
    }
    
    void writeW(int FDS,string msgw){
        //getline(cin,msg);
        send(FDS,msgw.c_str(),msgw.size(),0);
    }



    void funtion(string var,int FDS){

        
        if(var[0] == 'L'){
            Log();
        }
        else if(var[0] == 'O'){
            Olof();
        }
        else if(var[0] == 'N'){
            msgrU(FDS);
        }
        else if(var[0] == 'A'){
            allmsg();
        }
        else if(var[0] == 'K'){
            keepAlive();
        }
        else{
            closeSokedt();
        }
    }
    
    void cliente_process_thread(int FDS){
        int stop=1;
        int nn,s;
        //cout<<"entro al tread"<<nomcliente[FDS]<<endl;
        do{
            string msg;
            string nickname;
            char buff[1000];
            nn = read(FDS,buff,1);
            stringstream stream; 
            stream << buff; stream>>msg;
            funtion(msg,FDS);
            
            //if (nn < 0) perror("ERROR reading from socket");
            memset(buff,0,sizeof(buff));
        }while(stop);
    }


    void Log(){
        string temp =protomsg.msgU();
        clienteConectado[temp]=cliente;
        nomcliente[cliente] = temp;
        threadR(cliente);
    }
    void msgrU(int FDS){
        int nn,s;
        string msg;
        string nickname;
        char buff[1000];
        nn = read(FDS,buff,4); // size msg
        
        buff[nn]='\0';
        s = atoi (buff);
        nn = read(FDS,buff,s);
        //cout<<"mensaje de buff"<<buff<<endl;
        stringstream stream(buff); 
        //stream << buff; stream>>msg;
        getline(stream,msg);
        //cout<<msg<<endl;
        buff[nn]='\0';
        //msg = buff; 
        
        nn = read(FDS,buff,4); // size nikename
        buff[nn]='\0';
        s = atoi (buff);
        nn = read(FDS,buff,s); // leer nickname
        buff[nn]='\0';
        stringstream stream2; 
        stream2 << buff; stream2>>nickname;
        
        writeW(clienteConectado[nickname],msg);
    }
    void Olof(){}
    void allmsg(){}
    void keepAlive(){}
   

    void closeSokedt(){
        shutdown(cliente, SHUT_RDWR);
        close(cliente);
    }

    void closeServer(){
        close(server);
    }

};

int main(){
    Server *srv = new Server();
    srv->conex();
    srv->closeServer();
    return 0;
}