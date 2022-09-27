#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

std::string condition(std::string s){
	int i,j;
	std::size_t found = s.find("(");
  	if (found != std::string::npos)
    	i = found;
    std::size_t found2 = s.find(")");
  	if (found2 != std::string::npos)
    	j = found2;
    std::string condition = s.substr (i+1,j-(i+1));
 	return condition;
}

std::string left_operand(std::string s){
	std::vector<std::string> vect;
    vect.push_back("==");
    vect.push_back("!=");
    vect.push_back(">");
    vect.push_back(">=");
    vect.push_back("<");
    vect.push_back("<=");
    std::string bool_operation;
    for (std::size_t i = 0; i < vect.size(); i++){
        if (s.find(vect[i]) != std::string::npos)
            bool_operation = vect[i];
    }
    int i, j;
    std::size_t found5 = s.find("(");
    if (found5 != std::string::npos)
        i = found5;
    std::size_t found6 = s.find(bool_operation);
    if (found6 != std::string::npos)
        j = found6;
    std::string left = s.substr (i+1,j-(i+1));
    return left;
}

std::string right_operand(std::string s){
	std::vector<std::string> vect;
    vect.push_back("==");
    vect.push_back("!=");
    vect.push_back(">");
    vect.push_back(">=");
    vect.push_back("<");
    vect.push_back("<=");
    std::string bool_operation;
    for (std::size_t i = 0; i < vect.size(); i++){
        if (s.find(vect[i]) != std::string::npos)
            bool_operation = vect[i];
    }
    int i,j;
    std::size_t found3 = s.find(bool_operation);
    if (found3 != std::string::npos)
        i = found3;
    std::size_t found4 = s.find(")");
    if (found4 != std::string::npos)
        j = found4;
    std::string right = s.substr (i+2,j-(i+2));
    return right;
}

std::string body(std::string s){
    int i, j;
    std::size_t found = s.find("{");
    if (found != std::string::npos)
        i = found;
    std::size_t found2 = s.find("}");
    if (found2 != std::string::npos)
        j = found2;
    std::string body = s.substr (i+1,j-(i+1));
    return body;
}

int main(){
	std::ifstream myfile; 
	myfile.open("if_s.txt");
	std::string mystring;
	std::string myline;
	if ( myfile.is_open() ) { 
		while ( myfile.good() ) {
			std::getline (myfile, myline);
			std::cout << myline << '\n';
		} 
	}

	if (!(myline.find("{") != std::string::npos)){
		std::cout << "Expected {" <<std::endl;
		return 0;
	}
	if (!(myline.find("}") != std::string::npos)){
		std::cout << "Expected }" <<std::endl;
		return 0;
	}
	if (!(myline.find("(") != std::string::npos)){
		std::cout << "Expected (" <<std::endl;
		return 0;
	}
	if (!(myline.find(")") != std::string::npos)){
		std::cout << "Expected )" <<std::endl;
		return 0;
	}
	std::vector<std::string> vect;
    vect.push_back("==");
    vect.push_back("!=");
    vect.push_back(">");
    vect.push_back(">=");
    vect.push_back("<");
    vect.push_back("<=");
    std::string bool_operation;
    for (std::size_t i = 0; i < vect.size(); i++){
        if (myline.find(vect[i]) != std::string::npos)
            bool_operation = vect[i];
    }
    std::string left = left_operand(myline);
    std::string right = right_operand(myline);
    // std::cout<<left<<"\n"<<right<<"\n";
    bool a;
    if (bool_operation == "=="){
        if (stoi(left) == stoi(right))
            a = true;
        else 
            a = false;
    }
    if (bool_operation == "!="){
        if (stoi(left) != stoi(right))
            a = true; 
        else 
            a = false;
    }
    if (bool_operation == ">"){
        if (stoi(left) > stoi(right))
            a = true; 
        else 
            a = false;
    }
    if (bool_operation == ">="){
        if (stoi(left) >= stoi(right))
            a = true; 
        else 
            a = false;
    }
    if (bool_operation == "<"){
        if (stoi(left) < stoi(right))
            a = true; 
        else 
            a = false;
    }
    if (bool_operation == "<="){
        if (stoi(left) <= stoi(right))
            a = true; 
        else 
            a = false;
    }
    if (a == true)
    	std::cout << body(myline) << std::endl;
    else
    	std::cout << "Condition is " << std::boolalpha << a << " body not completed" << std::endl;

    return 0;
}