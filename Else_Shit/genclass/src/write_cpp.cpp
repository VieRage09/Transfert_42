#include "../genclass.hpp"

static bool write_getters_and_setters(std::ofstream &file, char **tab, std::string className)
{
	std::string attr;
	std::string	str;
	std::string	name;
	std::string	type;

	attr = get_attributes(tab);
	if (attr.empty())
	{
		std::cerr << "no attributes found\n";
		return (false);
	}
	file << "\n// GETTERS //\n\n";
	while (!attr.empty())
	{
		str = attr.substr(attr.find_first_not_of(' '), attr.find_first_of(','));
		if (attr.find_first_of(',') == std::string::npos)
			attr.clear();
		else
			attr = attr.substr(attr.find_first_of(',') + 1);
		type = get_type(str);
		name = get_name(str);
		if (is_pointer(type))
			str = "const " + type + "\t" + className + "::get" + name + "() const { return ( " + name + " );}";
		else
			str = "const " + type + "&\t" + className + "::get" + name + "() const { return ( " + name + " );}";
		
		file << str << "\n";
	}
	file << "\n// GETTERS //\n\n";
	attr = get_attributes(tab);
	while (!attr.empty())
	{
		str = attr.substr(attr.find_first_not_of(' '), attr.find_first_of(','));
		if (attr.find_first_of(',') == std::string::npos)
			attr.clear();
		else
			attr = attr.substr(attr.find_first_of(',') + 1);
		type = get_type(str);
		name = get_name(str);
		if (is_pointer(type))
			str = "void\t" + className + "::set" + name + "(" + type + " value) { this->" + name + " = value; }"; // const pointer ???
		else
			str = "void\t" + className + "::set" + name + "(" + type + "& value) { this->" + name + " = value; }";
		
		file << str << "\n";
	}
	return (true);
}

bool write_cpp_file(std::ofstream &file, std::string &name, t_options opt, char **tab)
{
	std::string header = name + ".hpp";

	file << "#include \"" << header << "\"\n\n"
		 << "// CONSTRUCTORS & DESTRUCTORS //\n\n"
		 << name << "::" << name << "() {}\n\n"
		 << name << "::" << name << "( ) {}\n\n"
		 << name << "::" << name << "(const " << name << "& copy) {}\n\n"
		 << name << "::~" << name << "() {}\n\n"
		 << "// METHODS //\n\n\n// OPERATORS //\n\n"
		 << name << "& " << name << "::operator = (const " << name << "& copy)\n{\n"
		 << "\tif (this != &copy)\n\t{\n\n\t}\n\treturn (*this);\n}\n";
	if (!write_getters_and_setters(file, tab, name))
		return (false);
	file.close();
	return (true);
}