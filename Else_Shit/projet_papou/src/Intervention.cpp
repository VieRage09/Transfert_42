#include "../headers/Intervention.hpp"

void	init_tm_struct(std::string str, struct tm & date);
// CONSTRUCTORS & DESTRUCTORS //

Intervention::Intervention()
{
	std::cout << "Initialization de l'intervention\n";
	init_tm_struct("Date de demande de devis(jours/mois/annee --> XX/XX/XXXX): ", _ask_date);
	init_tm_struct("Date du devis(jours/mois/annee --> XX/XX/XXXX): ", _estimate_date);
	init_tm_struct("Date de validation du devis(jours/mois/annee --> XX/XX/XXXX): ", _estimate_validation_date);
	init_tm_struct("Date des travaux(jours/mois/annee --> XX/XX/XXXX): ", _works_date);
	init_tm_struct("Date de facturation(jours/mois/annee --> XX/XX/XXXX): ", _billing_date);
	init_tm_struct("Date de paiement(jours/mois/annee --> XX/XX/XXXX): ", _payment_date);
	std::cout << "Numero d'intervention: ";
	std::cin >> _intervention_number;
	std::cout << "Enseigne: ";
	std::cin >> _brand;
	std::cout << "Adresse des travaux: ";
	std::cin >> _works_adress;
	std::cout << "Prestataire: ";
	std::cin >> _worker;
	std::cout << "Details des travaux: ";
	std::cin >> _works_details;
}

Intervention::Intervention(const Intervention& copy) {}

Intervention::~Intervention() {}

// METHODS //


// OPERATORS //

Intervention& Intervention::operator = (const Intervention& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}

// GETTERS //

const struct tm&	Intervention::get_ask_date() const { return ( _ask_date );}
const struct tm&	Intervention::get_estimate_date() const { return ( _estimate_date );}
const struct tm&	Intervention::get_estimate_validation_date() const { return ( _estimate_validation_date );}
const struct tm&	Intervention::get_works_date() const { return ( _works_date );}
const struct tm&	Intervention::get_billing_date() const { return ( _billing_date );}
const struct tm&	Intervention::get_payment_date() const { return ( _payment_date );}
const long&			Intervention::get_intervention_number() const { return ( _intervention_number );}
const std::string&	Intervention::get_brand() const { return ( _brand );}
const std::string&	Intervention::get_works_adress() const { return ( _works_adress );}
const std::string&	Intervention::get_worker() const { return ( _worker );}
const std::string&	Intervention::get_works_details() const { return ( _works_details );}

// GETTERS //

void	Intervention::set_ask_date(struct tm& value) { this->_ask_date = value; }
void	Intervention::set_estimate_date(struct tm& value) { this->_estimate_date = value; }
void	Intervention::set_estimate_validation_date(struct tm& value) { this->_estimate_validation_date = value; }
void	Intervention::set_works_date(struct tm& value) { this->_works_date = value; }
void	Intervention::set_billing_date(struct tm& value) { this->_billing_date = value; }
void	Intervention::set_payment_date(struct tm& value) { this->_payment_date = value; }
void	Intervention::set_intervention_number(long& value) { this->_intervention_number = value; }
void	Intervention::set_brand(std::string& value) { this->_brand = value; }
void	Intervention::set_works_adress(std::string& value) { this->_works_adress = value; }
void	Intervention::set_worker(std::string& value) { this->_worker = value; }
void	Intervention::set_works_details(std::string& value) { this->_works_details = value; }

// OTHERS //

std::ostream&	operator << (std::ostream & os, const Intervention & inter)
{
	os	<< "Intervention " << inter.get_intervention_number() << ":\n"
		<< "\t- Enseigne: " << inter.get_brand() << std::endl
		<< "\t- Adresse: " << inter.get_works_adress() << std::endl
		<< "\t- Prestataire: " << inter.get_worker() << std::endl
		<< "\t- Details des travaux: " << inter.get_works_details() << std::endl
		<< "\t- Date de demande de devis: " << asctime(&inter.get_ask_date()) << std::endl
		<< "\t- Date du devis: " << asctime(&inter.get_estimate_date()) << std::endl
		<< "\t- Date de validation du devis: " << asctime(&inter.get_estimate_validation_date()) << std::endl
		<< "\t- Date des travaux: " << asctime(&inter.get_works_date()) << std::endl
		<< "\t- Date de facturation: " << asctime(&inter.get_billing_date()) << std::endl
		<< "\t- Date de paiement: " << asctime(&inter.get_payment_date()) << std::endl;
	return (os);
}

// UTILS //

// Initialise une struct temps 
// Check a faire restant !!!
void	init_tm_struct(std::string str, struct tm & date)
{
	std::string	s;

	std::cout << str;
	std::cin >> s;
	date.tm_mday = std::atoi((s.substr(0, 2)).c_str());
	date.tm_mon = std::atoi((s.substr(3, 2)).c_str()) - 1;
	date.tm_year = std::atoi((s.substr(6, 4)).c_str()) - 1900;
}