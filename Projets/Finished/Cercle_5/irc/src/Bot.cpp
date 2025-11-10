#include "Bot.hpp"
#include "Server.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>


std::vector<std::string> createPrime() 
{
	const std::string primeArray[] = {
		"1. Gabriel Attal      | Point fort : jeune                             | Point faible : vieux dans sa tête",
		"2. Rachida Dati       | Point fort : bien sappée                       | Point faible : mauvaise en calcul mental",
		"3. François Bayrou    | Point fort : innofensif                        | Point faible : liquide",
		"4. Elisabeth Borne    | Point fort : balec energy de fou               | point faible : retraite",
		"5. Jean Castex        | Point fort : le foie gras putaing              | Point faible : ???",
		"6. Gérald Darmanin    | Point fort : grosse merde                      | Point faible : grosse merde",
		"7. Olivier Dussopt    | Point fort : corruptible                       | Point faible : corrompu",
		"8. Benjamin Griveaux  | Point fort : star du net                       | Point faible : chibrax",
		"9. Bruno Le Maire     | Point fort : renflement brun                   | Point faible : économie",
		"10. Sébastien Lecornu | Point fort : quantique                         | Point faible : indécis",
		"11. Sébastien Lecornu | Point fort : ENCORE LUI ?!",
		"12. Edouard Philippe  | Point fort : dure plus de 14 heures à Matignon | Point faible : il me fait peur",
		"13. Marlène Schiappa  | Point fort : ose tout                          | Point faible : orteils"
	};
	
	std::vector<std::string> ministre(primeArray, primeArray + sizeof(primeArray) / sizeof(primeArray[0]));
	return ministre;
}

std::vector<std::string> createMinistere() 
{
	const std::string ministereArray[] = {
		"Ministre des Relations avec le Parlement",
		"Ministre porte-parole du Gouvernement",
		"Ministre de l'Égalité entre les femmes et les hommes et de la Lutte contre les discriminations",
		"Ministre de la Transition numérique et des Communications électroniques",
		"Ministre de la Ville et du Logement",
		"Ministre de l'Enseignement supérieur et de la Recherche",
		"Ministre de l'Intérieur",
		"Ministre de la Justice",
		"Ministre de l'Éducation nationale et de la Jeunesse",
		"Ministre des Solidarités et de la Santé",
		"Ministre de l'Économie, des Finances et de la Relance",
		"Ministre des Armées",
		"Ministre de l'Agriculture et de l'Alimentation",
		"Ministre de la Culture",
		"Ministre de la Transition écologique",
		"Ministre du Travail, du Plein emploi et de l'Insertion",
		"Ministre des Outre-mer",
		"Ministre de la Mer"
	};
	
	std::vector<std::string> Ministere(ministereArray, ministereArray + sizeof(ministereArray) / sizeof(ministereArray[0]));
	return Ministere;
}

std::vector<std::string> createMinistre() 
{
	const std::string ministereArray[] = {
		"Sonia Backès", "Jean-Noël Barrot", "François Bayrou", "Clément Beaune", 
		"Olivier Becht", "Christophe Béchu", "Nicole Belloubet", "Justine Benin", 
		"Aurore Bergé", "Hervé Berville", "Jean-Michel Blanquer", "Laurence Boone", 
		"Elisabeth Borne", "Brigitte Bourguignon", "François Braun", "Yaël Braun-Pivet", 
		"Agnès Buzyn", "Jean-François Carenco", "Christophe Castaner", "Jean Castex", 
		"Charlotte Caubel", "Caroline Cayeux", "Thomas Cazenave", "Sophie Cluzel", 
		"Gérard Collomb", "Catherine Colonna", "Jean-Christophe Combe", "Bérangère Couillard", 
		"Gérald Darmanin", "Geneviève Darrieussecq", "Amélie de Montchalin", "François de Rugy", 
		"Marielle de Sarnez", "Jean-Paul Delevoye", "Julien Denormandie", "Jean-Baptiste Djebbari", 
		"Christelle Dubos", "Eric Dupond-Moretti", "Olivier Dussopt", "Sacha El Haïry", 
		"Dominique Faure", "Richard Ferrand", "Marc Fesneau", "Agnès Firmin-Le Bodo", 
		"Laura Flessel", "Delphine Gény-Stephann", "Annick Girardin", "Joël Giraud", 
		"Sylvie Goulard", "Jacqueline Gourrault", "Carole Grandjean", "Olivia Grégoire", 
		"Alain Griset", "Benjamin Griveaux", "Stanislas Guerini", "Didier Guillaume", 
		"Nadia Hai", "Nicolas Hulot", "Fadila Khattabi", "Olivier Klein", 
		"Brigitte Klinkert", "Jean-Yves Le Drian", "Bruno Le Maire", "Sébastien Lecornu", 
		"Jean-Baptiste Lemoyne", "Roland Lescure", "Nathalie Loiseau", "Mounir Mahjoubi", 
		"Roxana Maracineanu", "Jacques Mézard", "Patricia Mirallès", "Elisabeth Moreno", 
		"Sibeth NDiaye", "Pap Ndiaye", "Laurent Nunez", "Françoise Nyssen", 
		"Cédric O", "Amélie Oudéa-Castéra", "Agnès Pannier-Runacher", "Florence Parly", 
		"Muriel Pénicaud", "Edouard Philippe", "Laurent Pietraszewski", "Brune Poirson", 
		"Barbara Pompili", "Sylvie Retailleau", "Franck Riester", "Isabelle Rome", 
		"Aurélien Rousseau", "Marlène Schiappa", "Adrien Taquet", "Prisca Thevenot", 
		"Stéphane Travert", "Olivier Véran", "Patrice Vergriete", "Frédérique Vidal", 
		"Philippe Vigier", "Emmanuelle Wargon", "Chrysoula Zacharopoulou"
	};
	
	std::vector<std::string> ministre(ministereArray, ministereArray + sizeof(ministereArray) / sizeof(ministereArray[0]));
	return ministre;
}

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

Bot::Bot() : Client(-1, "localhost") {_name = "PascalBot";}

Bot::~Bot() {}

#pragma endregion constructors
//================================================================================================//


//=============================================================================== METHODS ========//
#pragma region methods

bool	Bot::isBot() const { return (true); }

void	Bot::autoRegister()
{
	setNick(_name);
	setUser(_name + "User");
	setReal(_name + " Bot IRC");
	setPassOk(true);
	setState(REGISTERED);
}

void	Bot::processMsg(Server *serv, Client *cli, std::string & msg)
{
	std::vector<std::string>	prime = createPrime();
	std::vector<std::string>	ministere = createMinistere();
	std::vector<std::string>	politikar = createMinistre();
	std::map<std::string, std::string>	gouv;
	std::string					ircMsg = ":" + _name + " PRIVMSG " + cli->getNick() + " :";
	std::stringstream			os(msg);
	size_t						num;
	
	if ((os >> num) && num < prime.size() && num > 0)
	{
		for(std::vector<std::string>::iterator it = ministere.begin(); it != ministere.end(); it++)
			gouv[*it] = politikar[rand() % politikar.size()];
		serv->append_client_sBuff(cli, ircMsg + "Voici ton gouvernement :\r\n");
		serv->append_client_sBuff(cli, ircMsg + "Premier ministre: " + prime[num - 1].substr(3, prime[num - 1].find_first_of('|') - 3) + "\r\n");
		for(std::map<std::string, std::string>::iterator it = gouv.begin(); it != gouv.end(); it++)
			serv->append_client_sBuff(cli, ircMsg + "- " + it->first + ": " + it->second + "\r\n");
	}
	else
	{
		serv->append_client_sBuff(cli, ircMsg + "!!====== Crée ton propre gouvernement français pour sauver la nation ======!!\r\n");
		serv->append_client_sBuff(cli, ircMsg + "En tant que monarque suprème de la nation, tu dois choisir un.e premier.e ministre parmis cette liste:\r\n");
		for (std::vector<std::string>::iterator it = prime.begin(); it != prime.end(); it++)
			serv->append_client_sBuff(cli, ircMsg + "- " + *it + "\r\n");
		serv->append_client_sBuff(cli, ircMsg + "Choisis un numero:\r\n");
		return ;
	}
	
}
