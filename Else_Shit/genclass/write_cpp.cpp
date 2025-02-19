#include "genclass.hpp"

void	write_getters_and_setters(char **tab)
{
	std::string	attr;
	attr = get_attributes(tab);
	std::cout << "Attributes: " << attr << std::endl;
}

bool	write_cpp_file(std::ofstream& file, std::string& name, t_options opt, char **tab)
{
	std::string	header = name + ".hpp";

	file	<< "#include \"" << header << "\"\n\n"
			<< "// CONSTRUCTORS & DESTRUCTORS //\n\n"
			<< name << "::" << name << "() {}\n\n"
			<< name << "::" << name << "( ) {}\n\n"
			<< name << "::" << name << "(const " << name << "& copy) {}\n\n"
			<< name << "::~" << name << "() {}\n\n"
			<< "// METHODS //\n\n\n// OPERATORS //\n\n"
			<< name << "& " << name << "::operator = (const " << name << "& copy)\n{\n"
			<< "\tif (this != &copy)\n\t{\n\n\t}\n\treturn (*this);\n}\n";
			if (opt == ALL)
				write_getters_and_setters(tab);
			file.close();
	return (true);
}