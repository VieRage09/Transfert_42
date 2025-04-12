#ifndef	INTERVENTION_HPP
#define	INTERVENTION_HPP

// includes //
#include <iostream>

class Intervention
{
	private:

		// attributes //
		long				_intervention_number;
		std::string			_brand;
		std::string			_works_adress;
		std::string			_worker;
		std::string			_works_details;
		struct tm			_ask_date;
		struct tm			_estimate_date;
		struct tm			_estimate_validation_date;
		struct tm			_works_date;
		struct tm			_billing_date;
		struct tm			_payment_date;

	public:
		// Default constructor
		Intervention();
		// Copy constructor
		Intervention(const Intervention& copy);
		// Destructor
		~Intervention();

		// Methods //


		// Operators //
		Intervention&	operator = (const Intervention& copy);

		// Getters //
		const long&				get_intervention_number() const;
		const std::string&		get_brand() const;
		const std::string&		get_works_adress() const;
		const std::string&		get_worker() const;
		const std::string&		get_works_details() const;
		const struct tm&		get_ask_date() const;
		const struct tm&		get_estimate_date() const;
		const struct tm&		get_estimate_validation_date() const;
		const struct tm&		get_works_date() const;
		const struct tm&		get_billing_date() const;
		const struct tm&		get_payment_date() const;

		// Setters //
		void				set_ask_date(struct tm& value);
		void				set_estimate_date(struct tm& value);
		void				set_estimate_validation_date(struct tm& value);
		void				set_works_date(struct tm& value);
		void				set_billing_date(struct tm& value);
		void				set_payment_date(struct tm& value);
		void				set_intervention_number(long& value);
		void				set_brand(std::string& value);
		void				set_works_adress(std::string& value);
		void				set_worker(std::string& value);
		void				set_works_details(std::string& value);

};

std::ostream&	operator << (std::ostream & os, const Intervention & inter);

#endif // INTERVENTION_HPP
