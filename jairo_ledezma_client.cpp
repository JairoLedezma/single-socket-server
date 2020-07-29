/*
Name: Jairo Ledezma
COSC 3360
Purpose: Learn how to create a single socket server and communicate between 
the client and the server to find out what the wheather for the next day is
for a certain city


** i learned to do socket programming through this youtube video below 
https://www.youtube.com/watch?v=LtXEMwSG5-8&t=2157s



*/
#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <netinet/in.h>
#include <string>


using namespace std;

int main(){
   int PORT;
   // creating a socket
   int netsocket=0;
   netsocket = socket(AF_INET,SOCK_STREAM, 0);
   
// address for the socket
   struct sockaddr_in serv_address;
   serv_address.sin_family = AF_INET;

    // takes in port num
    cout<< "Enter your port number: ";
    cin >> PORT;
    
    // converts the port number into something the computer understands
    serv_address.sin_port = htons(PORT);


    serv_address.sin_addr.s_addr = INADDR_ANY; // sets the adress to lolcal host 

   // connects to the server socket
    connect(netsocket, (struct sockaddr *) &serv_address, sizeof(serv_address));
    
    // receive server data
      string cityname; // holds the cityname
      cout << "Enter a city name:";
      char serv_message[256]; // creates an array of 256 characters
      cin.ignore(); // ignores the trailing /n
      getline(cin,cityname);

      for(int i=0; i<sizeof(serv_message);i++){ // converts the string into the server message 
         serv_message[i] = cityname[i]; // array
      }
      
      send(netsocket , serv_message, sizeof(serv_message),0);
      // sends tge message to the server


// receives the server data

    char serv_response[256]; // a maximum size of 256 bits
      //takes in datra from client
      
    //recv(netsocket,&serv_response,sizeof(serv_response),0);
    
    cout<< "\nWeather report for: " << cityname << endl;


   recv(netsocket,&serv_response,sizeof(serv_response),0); // receives the first response from the server
   string nd = serv_response; // sets the response to a string

   if(nd == "nodata"){// compares if the message is no data, if it is then display no data
      cout << "NO DATA\n";
   }
   else{ // otherwise prints out everything as ususal

    cout << "Tommorow's maximum temperature is " << serv_response<< endl;
      char serv_response2[256];
   recv(netsocket,&serv_response2,sizeof(serv_response2),0);
    cout << "Tommorow's sky condition is " << serv_response2<< endl;

    
    close(netsocket); // closes the client side of the socket
    

   }

    return 0;
}// end of main

