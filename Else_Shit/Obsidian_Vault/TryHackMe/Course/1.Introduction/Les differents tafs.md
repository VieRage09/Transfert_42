## I.Offensive security 
	--> Trouver les failles de secu d'un systeme pour pouvoir les fixer

=> Red team --> Se font passer pour un attaquant	//
=> Pentester --> Cherche les failles 				// Diff ??
[[TryHackMe/Course/1.Introduction/Commands]]


## II.Defensive security 
	--> Inverse: Detecter et se prevenir des intrusions

=> Blue team : Les defenseurs

### SOC 	
	--> Security operations center: Monitor the network/system to detect bad cybersec events 
	Need threat intelligence => Data collecting/processing then analysis
			  
### DFIR	
	--> Digital Forensics and Incident Response: 
		
==**==Forensics==**==: Application de la science pour investiguer/enqueter sur des crimes 
=> Recherche de preuves 
**Digital Forensics:** Recherche de preuve d'intrusion, de qui s'est introduit, de ce qu'il a fait etc...
=> On regarde les logs systeme/resea, images de la memoire etc...

**Incident response**: Developpement d'un plan de reponse a une attaque pour reduire les degats et se relever vite
![[Incident_Response.png.png]]
**Malware Analysis**: 
	=>Analyse statique: Sans run le malware
		->Reverse ingeneering donc asm etc..
	=>Analyse dynamique: Run le malware dans un environnement safe

Les 3 classiques malware: Cheval de troie, randsomware, virus

## III.Practical exemple of defense security##
	--> SOC analyst at a bank, SIEM simulation

SIEM = Security Information and Event Management
	=> Collecte diverses infos et les reuinis dans un dashboard
Sites web pour check la reputation d'une IP (AbuseIPDB ...)


## IV. Jobs

Security analyst: Maintient la securite informatique d'une organisation / consultant
Security engineer: Developpe des outiles pour la securite 
Incident responder: Agit pendant et apres les attaques 
Forensic: cf Digital Forensics
Malware analyst: cf malware analysis
Pentester: Hack des organisations pour trouver des failles et les documenter
Red teamer: cf red team --> Pentester oriente detection et reponse a l'attaque
