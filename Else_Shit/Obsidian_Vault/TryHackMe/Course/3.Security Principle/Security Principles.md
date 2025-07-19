-> Connaitre contre qui on se protege
## I. CIA
![[CIA_triforce.png.png]]
Its the security triad: 
	- Confidentiality: S'assurer qu'uniquement les bonnes personnes ont acces aux datas
	- Integrity: S'asssurer que les datas ne peuvent etre alterees, et pouvoir le remarquer
	- Availability: S'assurer que les systeme/service et dispo quand on en a besoin

De plus:
	- Authenticite: S'assurer que la data est bien issue de la source dite
	- Non repudiation: La source originale ne peux pas nier etre la source de cette data

Parkerian Hexad (By Donn Parker 1998)
	1.Availability
	2.Utility
	3.Integrity
	4.Authenticity
	5.Confidentiality
	6.Possession
		
- Utility: Usefulness of the information
- Possession: Protection des information du vol/copie/control(ransomware)

## II.DAD
![[DAD_Triad.png]]
Triad des moyens d'attaque d'un systeme
	- Disclosure: Attaque sur la confidentialite
	- Alteration: Attaque sur l'integrite
	- Destruction / Denial: Attaque sur la disponibilite

Augmenter la securite sur la confidentialite et l'integrite peut diminuer la disponibilite
=> L'implementation de bons principes de securite demande un equilibre entre les 3 CIA

## III. Concepts de modeles de securite fondamentaux

### 1/Bell-LaPadula Model

Son but est d'atteindre la confidentialite grace a 3 regles:
	- Simple Security Property / "No read up": Niveaux d'autorisation pour l'acces aux donnes
	- Star Security Property / "No write down": un niveau superieur ne peux ecrire un un niveau inferieur
	- Discretionary-Security Property: Tableau qui renseigne les droits (read / write) en plus des 2 regles precedents
==> You can share confidential information with people of higher security clearance (write up), and you can receive confidential information from people with lower security clearance (read down)

### 2/ Biba Model

Son but est d'atteindre l'integrite grace a 2 regles:
	- Simple Integrity Property / "No read down"
	- Star Integrity Property / "No write up"

Oui c'est globalement l'inverse de 1/

### 3/ Clark-Wilson Model

Son but est aussi d'atteindre l'integrite en utilisant les concepts suivants:
	- CDI (Constrained Data Items): type de data qu'on veut preserver
	- UDI (Unconstrained Data Items): autres data (ex: users, inputs)
	- TPs (Transformation Procedures): Operations programmees  (ex read/write), doivent preserver CDI
	- IVPs (Integrity Verification Procedures): Procedures de validation des l'integritee des CDI

## IV. ISO IEC norms

5 Principes d'architecture:
	- Domain separation: chaque entite a son propre domaine et ses regles de secu (rings of privileges in OS = kernel ring 0, user app ring 3)
	- Layering: Permet d'imposer des regles de secu a chaque couche (ex OSI: Open systems interconnection)
	- Encapsulation: En POO, donner a l'utilisateur uniquement ce dont il a besoin et cacher le reste
	- Redundancy: Avoir plusieurs alim / regulierement save les datas ...
	- Virtualization: Sandbox

5 Principes de design
	- Least privilege: Donner le minimum de permissions requises
	- Attack surface minimisation: Reduire les angles d'attaque au max
	- Centralized parameters validation: Validation des inputs gerer par une seule librairie par exemple
	- Centralized general security service: ex: creation d'un serveur d'autentification central
	- Preparing for error and exception handling: Les systemes doivent echouer proprement

## V. Zero trust VS trust but verify

### 1/ Zero trust
-> Tolerance zero
Chaque acces necessite autentification et autorisation
Permet de mieux contenir les potentiels leaks
ex: whitelists

### 2/ Trust but verify
-> Toujours verifier : 
ex: login, check les logs
-> Demande des mecanismes de secu automatises: Proxy, detection d'intrusion ...

## Conclusion

Vulnerability: faiblesse / Susceptibilite a une attaque 
Threat: Danger potentiel associe a cette faiblesse
Risk: Probabilite d'exploitation de la menace