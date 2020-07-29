/*
Name: Jairo Ledezma
COSC 3360
Purpose: Learn how to create a single socket server and communicate between 
the client and the server to find out what the wheather for the next day is
for a certain city

*** i ran the program using g++ jairo_ledezma_server.cpp -o server
    then ./server for some reason every once in a while it will not print out anything after you use ./server a few times
    alsmost as if nothing is being sent over to the client. if you re-build the program though
    the problem goes away and everything goes on as usual.



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
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>

using namespace std;


// used to make a list of structs. i used the list library mainly because
// of the prebuilt functions already made such as begin(), empty()
// the list library has linked list properties so it is easy to traverse
struct weatherData
{
    string city;
    string temp;
    string weather;
};

int main(){
    list<weatherData> cityWeather; // list of files weather
    list<weatherData>::iterator it; // creates the iterator to travers the list
    it = cityWeather.begin(); // sets iterator to beginning of list


    // reads in from file and creates a list of all wheather
    string line; // holds the line from file
    ifstream filestream("weather20.txt"); // opens weather20
    // best way to take in a string with spaces 
    while(getline(filestream, line)){ 
        weatherData temp; // creates a temp struct
        stringstream ss(line);
        getline(ss, temp.city, ','); // takes in a string up to delimiter ,
        getline(ss, temp.temp, ',');
        getline(ss, temp.weather, ',');
        cityWeather.push_back(temp); // after setting all the strings to temp i push the struct onto the list
        it++; // imncreases iterator
    }
    //for()

                
    //serv socket
    int serv_socket, PORT;
    string hostname;
    serv_socket = socket(AF_INET, SOCK_STREAM,0);

    // server address
    struct sockaddr_in serv_address;
    serv_address.sin_family = AF_INET;
    

    cout << "\nEnter the server host name: ";
    cin >> hostname;
    cout<< "Enter your port number: ";
    cin >> PORT;
    
    serv_address.sin_port = htons(PORT); // sets port into something computer understands
    serv_address.sin_addr.s_addr = INADDR_ANY; // is the samething as using local host

    // bind the socket to our ip and port
    bind(serv_socket, (struct sockaddr*) &serv_address,sizeof(serv_address));

    listen(serv_socket, 1); // listens to just 1 client
// here
for(;;){
    int clientSocket = accept(serv_socket, NULL, NULL); // accepts the connection from client

    char serv_response[256]; // a maximum size of 256 bits
      //takes in datra from client
      
    recv(clientSocket,&serv_response,sizeof(serv_response),0); // receives the city name
      

    int counter=0;
    it = cityWeather.begin(); // re sets the iterator to reuse it
    //
    // this for loop loops through the list and looks for the city that was sent by the client
    //
    
    bool found = false;
    for(int i = 0; i < cityWeather.size(); i++){
        if(it->city == serv_response){
           // cout<< "\nWeather report for: " << serv_response << endl;
            //char serv_message[256];
            //
           // for(int i=0; i<sizeof(serv_message);i++){ // converts the string into the server message 
            // serv_message[i] = serv_response[i]; // array
            //}
            //send(clientSocket , serv_message, sizeof(serv_message),0);
        //cout << "Tommorow's maximum temperature is " << it->temp<< endl;
            char serv_message2[256];

            for(int i=0; i<sizeof(serv_message2);i++){ // converts the string into the server message 
             serv_message2[i] = it->temp[i]; // array
            }
            send(clientSocket , serv_message2, sizeof(serv_message2),0);
        //
            char serv_message3[256];

            for(int i=0; i<sizeof(serv_message3);i++){ // converts the string into the server message 
             serv_message3[i] = it->weather[i]; // array
            }
            send(clientSocket , serv_message3, sizeof(serv_message3),0);

            //cout << "Tommorow's sky condition is " << it->weather<< endl;
            it++;
            found = true; // when found wont print out no data
            //counter++;
        }
        else{
            //counter++;
            it++;
        }
    }
    
    
    if(found==false){ // if not found then there is no data of that city
    string nd = "nodata";
    char serv_message4[256];

            for(int i=0; i<sizeof(serv_message4);i++){ // converts the string into the server message 
             serv_message4[i] = nd[i]; // array
            }
            send(clientSocket , serv_message4, sizeof(serv_message4),0); // send the nodata message to client
        // cout<<"\nnodata";
    }

    close(clientSocket);
     

    cout<< "\n---server shut down--- \n";
    

    return 0;

}