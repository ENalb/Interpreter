#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

bool delimiter(std::string s){
	if (s.find(";") != std::string::npos)
		return true;
	else 
		return false;
}

bool declare(std::string s){
	if (s.find("declare") != std::string::npos) 
		return true;
	else
		return false;
}

std::string values(std::string a){
	int i,j;
	std::size_t found = a.find("= ");
  	if (found != std::string::npos)
    	i = found;
    std::size_t found2 = a.find(" ;");
  	if (found2 != std::string::npos)
    	j = found2;
    std::string values = a.substr (i+2,j-(i+2));
 	return values;
}

std::string type(std::string s){
	std::string types;
	int i,j;
	std::size_t found = s.find("= ");
  	if (found != std::string::npos)
    	i = found;
    std::size_t found2 = s.find(" ;");
  	if (found2 != std::string::npos)
    	j = found2;
    std::string values = s.substr (i+2,j-(i+2));
    for (int i = 0; i < values.length(); ++i){
		if(isdigit(values[i]) && !(values.find(".") != std::string::npos))
			types = "int";
		else if (isdigit(values[i]) && values.find(".") != std::string::npos)
			types = "double";
		else
			types = "string";
	}
	return types;
}

std::string names(std::string a){
	int i,j;
	std::size_t found = a.find(" ");
  	if (found != std::string::npos)
    	i = found;
    std::size_t found2 = a.find(" =");
  	if (found2 != std::string::npos)
    	j = found2;
    std::string names = a.substr (i+1,j-i);
    if(isdigit(names[0])){
    	return ""; 
    }
 	return names;
}

int main(){
	std::ifstream myfile; 
	myfile.open("declaration.txt");
	std::string mystring;
	std::string myline;
	if ( myfile.is_open() ) { 
		while ( myfile.good() ) {
			std::getline (myfile, myline);
			std::cout << myline << '\n';
		} 
	}
	if (delimiter(myline)==false){
		std::cout << "Expected ;" << std::endl;
		return 0;
	}
	if (declare(myline)==false){
		std::cout << "Undefined variable" << std::endl;
		return 0;
	}
	if (names(myline) == ""){
		std::cout << "Unavailable name of variable" << std::endl;
		return 0;
	}
	if (type(myline) == "int"){
		std::cout << type(myline) << " " << names(myline) << "= " << stoi(values(myline)) << ";" << std::endl;
	}
	else if (type(myline) == "double"){
		std::cout << type(myline) << " " << names(myline) << "= " << stod(values(myline)) << ";" << std::endl;
	}
	else {
		std::cout << type(myline) << " " << names(myline) << "= " << values(myline) << " ;" << std::endl;
	}
	
	return 0;
}

