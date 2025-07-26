Most used web server around the world
Open source

---
# What is it ?

open source program of web server (or HTTP) and a reverse proxy.
Use asynchronous circuits. 
#### Synchronous circuit
-> Type of electronic circuit (ex: used for personal computers)
-> Operations (calculus, instructions ... ) are coordinated by one or multiple clock signals
Its means that each component of this circuit can access an thus process the input electrical impulses when the clock ticks, synchronizing them properly.
-> For a CPU: 4 GHz represents the frequency of the clock.

#### Asynchronous circuit
-> The other type
-> No global clock(s)
-> Coordinated via events like: network packet arrival, handshake protocol ...
communication used to transmit data AND to synchronises operations
-> Generally uses less power because components are activated only when needed
-> Different style of design

---
# 1. Web server

software and underlying hardware that accepts requests via HTTP(or HTTPS).
User initiates communication by making an HTTP request for a ressource (ex: web page) and the server responds with the content requested or and error message

---
# 2. Reverse proxy

#### Proxy server
-> Server application
-> An intermediary between a client requesting a ressource and the server providing it
May reside inside the user's computer or between user's computer and destination server
-> Improves privacy security and performance
-> Can mask the true origin of the request

##### Tunneling proxy or gateway
-> Passes unmodified requests and responses 
##### Forward proxy
-> Internet-facing proxy
##### Reverse proxy
-> Internal-faced proxy
-> Used to control and protect access to a server on a private network
-> Can mask the true origin of the response from the server