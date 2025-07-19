Transport Layer Security
SSL (Secure Sockets Layer) successor

------------------------------------------------------------------------
# What is it ?

-> Cryptographic protocol 
-> Composed itself of 2 layers: TLS records and TLS handshake protocols
-> Provides security (including privacy, integrity and authenticity)
Uses certificates: electronic document used to prove the validity of a public key
-> Runs in the presentation layer / transport layer on OSI model (layer 5/6) : https://en.wikipedia.org/wiki/OSI_model
	Usually used as if it was a transport layer but encryption is the function of the presentation layer
-> Secures HTTPS

------------------------------------------------------------------------
# How does it work ?

Client must request that the server sets up a TLS connexion (usually using a different port):
	-> port 80: typically for unencrypted HTTP trafic
	-> port 443: common for encrypted HTTPS trafic
Once they agreed to use TLS, they use handshake procedures to establish a stateful connection (connection that remembers what happened).
	
### The handshake
1. The client also provide to the server a list of supported cipher suites (ciphers + hash functions)
2. Computers selects a cipher and hash that it supports from the list and response to client with:
		-> digital certificate: it contained server name, the trusted certificate authority and the server's public encryption key 
3. Clients confirms the validity of the certificate
4. The client generate the session keys by
	-> Encrypting a random number with the server's public key and sends it to server (the server only can decrypt it with its private key) => **assymetric cipher** 
	Servers and client both use the random number to generate a unique session key
	-> Used Diffie-Hellman key exchange: https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange
If one of the steps fails -> no handshake -> connection is not established.
The connection is then encrypted and decrypted with the session key. => **symmetric cipher** 