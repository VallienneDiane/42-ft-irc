## IRC : Internet Relay Chat

IRC is a text-based chat protocol. It is well-suited to running on many machines in a distributed fashion. A typical setup involves multiple servers connected in a distributed network. Messages are delivered through this network and state is maintained across it for the connected clients and active channels.

The aim here is to create a server which communicate with an irc client, doing different actions via commands.

### Commands to install Weechat and access to the client

In term :

	brew install weechat

	/server add cornichon 127.0.0.1/6000

	/connect cornichon -password=

	/disconnect

### Start irc server:

	./ircserv <port> <password>

### Start irc client:

	Weechat : /connect <server_name> -password=
	or
	in Term : nc -c <host> <port> (nc -c 127.0.0.1 <port>)
				PASS password
				NICK nickname
				USER username 0 * realName

The Netcat (nc) command is a command-line utility for reading and writing data between two computer networks. 

### Handle strange situations in networking :

Suspend a client :

	Suspended a client with ^Z
	Others client wrote messages
	Do fg to continued client who was suspended
	When client is live again, he should receive all messages send during his suspension

Send a partial command :

	Send partial command and ^D and continue the command
	Server should understand
	Quit properly if ^C

## Bonus 

### Bots
Join all channels without a password and has to be invite in others channels.

-> Fumier is a spam bot.

-> CoolBot answer a word or sentence if receive one specific word or sentence.

Start Bot(s) :

		make bot
		./bots/bin/coolBot <IP> <port> <password> <sentence to awake the bot> <sentence answered by the bot> 
		./bots/bin/fumierBot <IP> <port> <password> 

### Send files using DCC

The Direct Client-to-Client Protocol (DCC) has been the primary method of establishing connections directly between IRC clients for a long time now. Once established, DCC connections bypass the IRC network and servers, allowing for all sorts of data to be transferred between clients including files and direct chat sessions.

In irc client :
	
	for example send file "/home/foo/bar.txt" to nick "nickname":
		/dcc send nickname /home/foo/bar.txt
		/dcc send nickname /path/image.jpeg

### Steps to do the project
1. Download client (Weechat pe)
2. Create sockets to make the connection between server and client
3. Handle users and channels with maps, vector, set.
4. Add commands (connection msg, channel operations, sending msg, operator msg etc)
5. Handle the channel operator and basic users

## Sources

### Articles

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

Nc cmds :
https://phoenixnap.com/kb/nc-command


### Videos

Weechat : adding a server and connection : 
https://www.youtube.com/watch?v=v0HoaQIz39w

Creating a TCP server in C++ : 
https://www.youtube.com/watch?v=WDn-htpBlnU

How one thread listens to many sockets with select : 
https://www.youtube.com/watch?v=Y6pFtgRdUts

