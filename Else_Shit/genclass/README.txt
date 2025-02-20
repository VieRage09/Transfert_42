// Programme pour creer automatiquement un fichier .hpp et un fichier .cpp correspondants a une classe de votre choix

1. Usage

./genclass <Nom de la classe> <options> <si option -> attributs de la classe>

options:
	-a: Option attributs --> Permet de definir directement les attributs private de la class.
	-g: Options getters & setters --> Permet d'ajouter un getter et un setter a chaque attribut.
	    Uniquement utilisable en combinaison avec -a.

2. Attention

	a. pas de type de variable en deux mots type unsigned int --> Faudra faire des modifs vous meme
	b. Si l'option attributs (-a / -ag / -ga / -g -a bref t'as compris) est utilisee, seul l'argument d'apres est pris
	   en compte en tant que definition des attributs (donc mets des ""). Il faut separer les attributs par des virgules.