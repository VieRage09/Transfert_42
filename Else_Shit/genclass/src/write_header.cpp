#include "../genclass.hpp"

static void	write_each(std::ofstream& file, std::string& attr)
{
	std::string str;
	std::string name;
	std::string type;

	while (!attr.empty())
	{
		str = attr.substr(attr.find_first_not_of(' '), attr.find_first_of(','));
		if (attr.find_first_of(',') == std::string::npos)
			attr.clear();
		else
			attr = attr.substr(attr.find_first_of(',') + 1);
		name = get_name(str);
		type = get_type(str);
		str = type + "\t";
		if (type.size() < 4)
			str += "\t";
		if (type.size() < 8)
			str += "\t";
		if (type.size() < 12)
			str += "\t";
		if (type.size() < 16)
			str += "\t";
		str += name;
		file << "\t\t" << str << ";\n";
	}
}

static bool	write_attributes(std::ofstream& file, t_options opt, char **tab)
{
	std::string	attr;

	if (opt == ASSIGN_ATTRIBUTES || opt == ALL)
	{
		attr = get_attributes(tab);
		if (attr.empty())
		{
			std::cerr << "no attributes found\n";
			return (false);
		}
		write_each(file, attr); 
	}
	file << "\n\t";
	return (true);
}

// option 0 for getters option 1 for setters
static void	write_each_getSet(std::ofstream& file, std::string& attr, int option)
{
	std::string str;
	std::string	type;
	std::string	name;

	while (!attr.empty())
	{
		str = attr.substr(attr.find_first_not_of(' '), attr.find_first_of(','));
		if (attr.find_first_of(',') == std::string::npos)
			attr.clear();
		else
			attr = attr.substr(attr.find_first_of(',') + 1);
		type = get_type(str);
		name = get_name(str);
		if (option == 0) // getters
		{
			if (is_pointer(type))
				str = "const " + type + "\t";
			else
				str = "const " + type + "&\t";
			if (str.size() < 13)
				str += "\t";	
			if (type.size() < 21)
				str += "\t";	
			str+= "get" + name + "() const";
		}
		else			// setters
		{
			if (is_pointer(type))
				str = "void\t\t\t\tset" + name + "(" + type + " value)"; // const pointer ???
			else
				str = "void\t\t\t\tset" + name + "(" + type + "& value)";
		}
		file << "\t\t" << str << ";\n";
	}
}

static bool	write_getSet(std::ofstream& file, t_options opt, char **tab)
{
	std::string	attr;

	if (opt == ALL)
	{
		attr = get_attributes(tab);
		if (attr.empty())
		{
			std::cerr << "no attributes found\n";
			return (false);
		}
		file << "\n\t\t// Getters //\n";
		write_each_getSet(file, attr, 0);
		attr = get_attributes(tab);
		file << "\n\t\t// Setters //\n";
		write_each_getSet(file, attr, 1);
	}
	file << "\n";
	return (true);
}

bool	write_header_file(std::ofstream& file, std::string& name, t_options opt, char **tab)
{
	std::string	headName = name + "_HPP";
	headName = capitalize(headName);
	file 	<< "#ifndef\t" << headName << "\n#define\t" << headName << "\n\n"
			<< "// includes //\n\n"
			<< "class " << name << "\n{\n\tprivate:\n\n\t\t// attributes //\n";
	if (!write_attributes(file, opt, tab))
		return (false);
	file	<< "public:\n\t\t" << "// Default constructor\n\t\t"
			<< name << "();\n\t\t"
			<< "// Personnalized constructor\n\t\t"
			<< name << "( );\n\t\t"
			<< "// Copy constructor\n\t\t"
			<< name << "(const " << name << "& copy);\n\t\t"
			<< "// Destructor\n\t\t"
			<< "~" << name << "();\n\n\t\t"
			<< "// Methods //\n\n\n\t\t"
			<< "// Operators //\n\t\t"
			<< name << "&\t";
	if (name.size() < 4)
		file	<< "\t";
	if (name.size() < 8)
		file	<< "\t";
	if (name.size() < 12)
		file	<< "\t";
	// if (name.size() < 16)
	// 	file	<< "\t";
	file	<< "operator = (const " << name << "& copy);\n";
	if (!write_getSet(file, opt, tab))
		return (false);
	file	<< "};\n\n#endif // " << headName << std::endl;
			file.close();
	return (true);
}