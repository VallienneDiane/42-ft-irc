### IRC : Internet Relay Chat

IRC is a text-based chat protocol. It is well-suited to running on many machines in a distributed fashion. A typical setup involves multiple servers connected in a distributed network. Messages are delivered through this network and state is maintained across it for the connected clients and active channels.

## Steps
1. Download client (Weechat pe)
2. Create socket to make the connection between server and client
3. Add commands
4. type of channel : regular or local
5. handle the channel operator (moderate, keep control of channel) and basic users
6. topics in channel

## User

- Nickname
- Username
- Join channel
- Send and Receive private messages


## Channel Management

- Topic
- User limit
- Key (key to enter)
- Access control (set max modes)
- Ban and exception
- Invitation
- Tracking recently used (channel unavailable if everyone leave)
- Safe channel (name)
- Identifier (function of time, periodicity 700days)

## Channel operator
Identified with @ for standard channel operator and % for halfops next to nickname

- Kick : eject user from channel
- Mode : change channel's modes
- Invite : invite user to channel (+i)
- Topic : change channel topic (+t)

## Commands to install Weechat and access to the client

In term :

	brew install weechat

	/server add cornichon 127.0.0.1/6000

	/connect cornichon

	/disconnect

## Sources

Articles :

	Les Sockets C++ : https://c.developpez.com/cours/sockets-c-cpp-demystifies/

	Internet Relay Chat: Channel Management : https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.6

	Modern IRC Client protocol : https://modern.ircdocs.horse/\

	Programmation sockets : http://tvaira.free.fr/bts-sn/reseaux/cours/cours-programmation-sockets.pdf

	Logging into an irc server : http://chi.cs.uchicago.edu/chirc/irc_examples.html

Videos :

	Weechat : adding a server and connection : https://www.youtube.com/watch?v=v0HoaQIz39w

	Creating a TCP server in C++ : https://www.youtube.com/watch?v=WDn-htpBlnU

	How one thread listens to many sockets with select : https://www.youtube.com/watch?v=Y6pFtgRdUts

