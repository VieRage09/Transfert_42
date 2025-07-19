
2 moyens d'identification:
	- adresse IP = Internet protocol
	- adresse MAC = Media acces control

## I. Adresse IP

-> Moyen d'identifier une machine sur un reseau **A UN MOMENT DONNE**	
![[IP_adress.png.png]]
Impossible d'avoir deux fois la meme IP active sur le meme reseau en meme temps

IP privee et IP public
	-> Public: Donnee par le fournisseur internet, utilise donc par tout le reseau de la box pour naviguer sur internet
	-> Privee: Utilise pour identifier la machine a l'interieur d'un reseau
	![[IPv4_vs_IPv6.png.png]]
-> IPv4 = 4 bytes IPv6 = 16 bytes

## II. Adresse MAC

Interface reseau: Puce branchee sur la carte mere 
	-> Une adresse MAC lui est assigne lors de sa fabrication
![[MAC.png.png]]
Spoofing: Une machine pretend etre une autre en changeant son adresse MAC par une autre

## III. PING

=> Uses ICMP's (Internet Control Message Protocol) echo/reply packets pour evaluer la performance d'une connection
[[TryHackMe/Course/2.What is networking/Commands|Commands]]

