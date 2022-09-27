#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

// std::string cond(std::string s){
//     int i,j;
//     std::size_t found = s.find("(");
//     if (found!=std::string::npos)
//         i = found;
//     std::size_t found2 = s.find(")");
//     if (found2!=std::string::npos)
//         j = found2;
//     std::string condition = s.substr (i+1,j-(i+1));
//     return condition;
// }

std::string initialization(std::string s){
    int i,j;
    std::size_t found = s.find("(");
    if (found!=std::string::npos)
        i = found;
    std::size_t found2 = s.find("/");
    if (found2!=std::string::npos)
        j = found2;
    std::string initialization = s.substr (i+1,j-(i+1));
    return initialization;
}

std::string condition_for(std::string s){
    int i,j;
    std::size_t found = s.find("/ ");
    if (found!=std::string::npos)
        i = found;
    std::size_t found2 = s.find("/");
    if (found2!=std::string::npos)
        j = found2;
    std::string condition = s.substr (i+2,5);
    return condition;
}

std::string step(std::string s){
    int i,j;
    std::size_t found = s.find("/ ");
    if (found!=std::string::npos)
        i = found;
    std::size_t found2 = s.find(")");
    if (found2!=std::string::npos)
        j = found2;
    std::string step = s.substr (i+9,j-(i+9));
    return step;
}

std::string replacef(std::string s, char ch1, char ch2)
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
    if (found!=std::string::npos)
        i = found;
    std::size_t found2 = s.find(" ;");
    if (found2!=std::string::npos)
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

std::string names_for(std::string a){
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

std::string values_for(std::string a){
    int i,j;
    std::size_t found = a.find("= ");
    if (found!=std::string::npos)
        i = found;
    std::size_t found2 = a.find("/");
    if (found2!=std::string::npos)
        j = found2;
    std::string values = a.substr (i+2,j-(i+2));
    return values;
}

int main()
{
    std::ifstream fin("orinak.txt");
    std::vector<std::string> v;
    std::string line, word, condition, values, types;
    int i;
    int count=0;
    while(!fin.eof())
    {
        getline(fin,line);
        std::cout<<line<<"\n";
        for(i=0;i<line.length();i++)
        {
            if(line[i]==' ')
            {
                break;
            }
            word = word + line[i];
        }
        v.push_back(word);
        word = "";
    }
    for(std::size_t i = 0; i < v.size(); ++i) {
        std::cout<<v[i]<<","<<std::endl;
    }
    for(std::size_t i = 0; i < v.size(); ++i) {
        if(v[i]=="declare" && !(line.find(";") != std::string::npos)){
            std::cout << "Expected ;" << std::endl;
            return 0;
        }
        if(v[i]=="declare"){
            int k,j;
            std::size_t found = line.find("= ");
            if (found!=std::string::npos)
                k = found;
            std::size_t found2 = line.find(" ;");
            if (found2!=std::string::npos)
                j = found2;
            values = line.substr (k+2,j-(k+2));
            for (int i = 0; i < values.length(); ++i){
                if(isdigit(values[i]) && !(values.find(".") != std::string::npos))
                    types = "int";
                else if (isdigit(values[i]) && values.find(".") != std::string::npos)
                    types = "double";
                else
                    types = "string";
            }
            int m,n;
            std::size_t found3 = line.find(" ");
            if (found3!=std::string::npos)
                m = found3;
            std::size_t found4 = line.find(" =");
            if (found4!=std::string::npos)
                n = found4;
            std::string names = line.substr (m+1,n-m);
            if(isdigit(names[0])){
                std::cout<<"Unavailable name of variable"<<std::endl;
                return 0; 
            }
            if (types == "int"){
                std::cout<<types<<" "<<names<<"= "<<stoi(values)<<";"<<std::endl;
            }
            else if (types == "double"){
                std::cout<<types<<" "<<names<<"= "<<stod(values)<<";"<<std::endl;
            }
            else {
                std::cout<<types<<" "<<names<<"= "<<values<<";"<<std::endl;
            }
        }
    }
    for(std::size_t i = 0; i < v.size(); ++i) {
        if(v[i]=="if" && !(line.find(":") != std::string::npos)){
            std::cout << "Expected :" << std::endl;
            return 0;
        }
        if (v[i]=="if" && !(line.find("(") != std::string::npos)){
             std::cout << "Expected (" << std::endl;
             return 0;
        }
        if (v[i]=="if" && !(line.find(")") != std::string::npos)){
             std::cout << "Expected )" << std::endl;
             return 0;
        }
        if(v[i]=="if" && line.find(":") != std::string::npos && line.find("(") != std::string::npos && line.find(")") != std::string::npos){
            int k,j;
            std::size_t found = line.find("(");
            if (found!=std::string::npos)
                k = found;
            std::size_t found2 = line.find(")");
            if (found2!=std::string::npos)
                j = found2;
            condition = line.substr (k+1,j-(k+1));
        }  
    }
    std::cout << condition << std::endl;
    for(std::size_t i = 0; i < v.size(); ++i) {
        if(v[i] == "for" && !(line.find(":") != std::string::npos)){
            std::cout << "Expected :"<<std::endl;
            return 0;
        }
        if (v[i]=="for" && !(line.find("(") != std::string::npos)){
            std::cout << "Expected (" <<std::endl;
            return 0;
        }
        if (v[i]=="for" && !(line.find(")") != std::string::npos)){
            std::cout << "Expected )" <<std::endl;
            return 0;
        }
        if (v[i]=="for" && !(line.find("/") != std::string::npos)){
            std::cout<<"Expected /" <<std::endl;
        }
        if(v[i]=="for" && !(initialization(line).find("declare") != std::string::npos)){
            std::cout<<"Undeclared variable"<<std::endl;
            return 0;
        }
        if (names_for(line) == ""){
            std::cout << "Unavailable name of variable" << std::endl;
            return 0;
        }
        std::string a=replacef(line,'/',';');
        std::string b=replacef(a,':','{');
        std::cout<<b<<std::endl;
        if (type(line) == "int"){
            std::cout<<"for ("<<type(line)<<" "<<names_for(line)<<" = "<<stoi(values_for(line))<<"; "<<condition_for(line)<<"; "<<step(line)<<")"<<std::endl;
        }
        else if (type(line) == "double"){
            std::cout<<"for ("<<type(line)<<" "<<names_for(line)<<" = "<<stod(values_for(line))<<"; "<<condition_for(line)<<"; "<<step(line)<<")"<<std::endl;
        }
    }
    // for(std::size_t i = 0; i < v.size(); ++i) {
    //     if (v[i]=="wloop" && !(line.find("(") != std::string::npos)){
    //         std::cout << "Expected (" <<std::endl;
    //         return 0;
    //     }
    //     if (v[i]=="wloop" && !(line.find(")") != std::string::npos)){
    //         std::cout << "Expected )" <<std::endl;
    //         return 0;
    //     }
    //     if (v[i]=="wloop" && !(line.find(":") != std::string::npos)){
    //         std::cout << "Expected :" <<std::endl;
    //         return 0;
    //     }
    //     // std::cout<<condition(line)<<std::endl;
    //     std::string w = "while";
    //     line.replace(line.find("wloop"), 5, w);
    //     std::cout<<line<<"{\n\n}"<<std::endl;
    // }
    return 0;
}