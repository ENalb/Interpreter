#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

std::string initialization(std::string s){
    int i,j;
    std::size_t found = s.find("(");
    if (found != std::string::npos)
        i = found;
    std::size_t found2 = s.find("/");
    if (found2 != std::string::npos)
        j = found2;
    std::string initialization = s.substr (i+1,j-(i+1));
    return initialization;
}

std::string condition(std::string s){
    int i,j;
    std::size_t found = s.find("/ ");
    if (found != std::string::npos)
        i = found;
    std::size_t found2 = s.find("/");
    if (found2 != std::string::npos)
        j = found2;
    std::string condition = s.substr (i+2,5);
    return condition;
}

std::string step(std::string s){
    int i,j;
    std::size_t found = s.find("/ ");
    if (found != std::string::npos)
        i = found;
    std::size_t found2 = s.find(")");
    if (found2 != std::string::npos)
        j = found2;
    std::string step = s.substr (i+9,j-(i+9));
    return step;
}

std::string replace(std::string s, char ch1, char ch2)
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ch1)
            s[i] = ch2;
        else if (s[i] == ch2)
            s[i] = ch1;
    }
    return s;
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
    }
    return types;
}

std::string names(std::string a){
    int i,j;
    std::size_t found = a.find("declare ");
    if (found!=std::string::npos)
        i = found;
    std::size_t found2 = a.find(" =");
    if (found2!=std::string::npos)
        j = found2;
    std::string names = a.substr (i+8,j-(i+8));
    if(isdigit(names[0])){
        return ""; 
    }
    return names;
}

std::string values(std::string a){
    int i,j;
    std::size_t found = a.find("= ");
    if (found != std::string::npos)
        i = found;
    std::size_t found2 = a.find("/");
    if (found2 != std::string::npos)
        j = found2;
    std::string values = a.substr (i+2,j-(i+2));
    return values;
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
    myfile.open("for.txt");
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
    if (!(myline.find("/") != std::string::npos)){
        std::cout<<"Expected /" <<std::endl;
    }
    if(!(initialization(myline).find("declare") != std::string::npos)){
        std::cout<<"Undeclared variable"<<std::endl;
        return 0;
    }
    if (names(myline) == ""){
        std::cout << "Unavailable name of variable" << std::endl;
        return 0;
    }
    std::string a=replace(myline,'/',';');
    std::cout<<a<<std::endl;
    if (type(myline) == "int"){
        std::cout<<"for ("<<type(myline)<<" "<<names(myline)<<" = "<<stoi(values(myline))<<"; "<<condition(myline)<<"; "<<step(myline)<<"){"<<body(myline)<<"}"<<std::endl;
    }
    else if (type(myline) == "double"){
        std::cout<<"for ("<<type(myline)<<" "<<names(myline)<<" = "<<stod(values(myline))<<"; "<<condition(myline)<<"; "<<step(myline)<<"){"<<body(myline)<<"}"<<std::endl;
    }

    return 0;
}