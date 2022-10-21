### IRC : Internet Relay Chat

IRC is a text-based chat protocol. It is well-suited to running on many machines in a distributed fashion. A typical setup involves multiple servers connected in a distributed network. Messages are delivered through this network and state is maintained across it for the connected clients and active channels.

The aim here is to create a server which communicate with an irc client, doing different actions via commands.

Start program:

	./ircserv <port> <password>


## Steps to do the project
1. Download client (Weechat pe)
2. Create socket to make the connection between server and client
3. Add commands (connection msg, channel operations, sending msg, operator msg etc)
4. Handle the channel operator and basic users


## Commands to install Weechat and access to the client

In term :

	brew install weechat

	/server add cornichon 127.0.0.1/6000

	/connect cornichon -password=

	/disconnect

## Send files using DCC

The Direct Client-to-Client Protocol (DCC) has been the primary method of establishing connections directly between IRC clients for a long time now. Once established, DCC connections bypass the IRC network and servers, allowing for all sorts of data to be transferred between clients including files and direct chat sessions.

In irc client :
	
	for example send file "/home/foo/bar.txt" to nick "nickname":
		/dcc send nickname /home/foo/bar.txt
		/dcc send nickname /path/image.jpeg

## Sources

- Articles :

Les Sockets C++ : 
https://c.developpez.com/cours/sockets-c-cpp-demystifies/

Internet Relay Chat: Channel Management : 
https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.6

Modern IRC Client protocol : 
https://modern.ircdocs.horse/\

Programmation sockets : 
http://tvaira.free.fr/bts-sn/reseaux/cours/cours-programmation-sockets.pdf

Logging into an irc server : 
http://chi.cs.uchicago.edu/chirc/irc_examples.html

DCC : 
https://modern.ircdocs.horse/dcc.html


- Videos :

Weechat : adding a server and connection : 
https://www.youtube.com/watch?v=v0HoaQIz39w

Creating a TCP server in C++ : 
https://www.youtube.com/watch?v=WDn-htpBlnU

How one thread listens to many sockets with select : 
https://www.youtube.com/watch?v=Y6pFtgRdUts

