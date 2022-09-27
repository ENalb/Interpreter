#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int sum(int a,int b){
    return a + b;
}
int sub(int a, int b){
    return a - b;
}
int mul(int a, int b){
    return a * b;
}
int division(int a, int b){
    return a / b;
}
int mod(int a, int b){
    return a % b;
}
double sum(double a,double b){
    return a + b;
}
double sub(double a, double b){
    return a - b;
}
double mul(double a, double b){
    return a * b;
}
double division(double a, double b){
    return a / b;
}

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

std::string left_operand(std::string s){
    char operation;
    for(int i = 0; i < s.length(); ++i){
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%')
            operation = s[i];
    }
    int i,j;
    std::size_t found = s.find("= ");
    if (found != std::string::npos)
        i = found;
    std::size_t found2 = s.find(operation);
    if (found2 != std::string::npos)
        j = found2;
    std::string left = s.substr (i+2,j-12);
    return left;
}

std::string right_operand(std::string s){
    char operation;
    for(int i = 0; i < s.length(); ++i){
        if (s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='%')
            operation = s[i];
    }
    int i,j;
    std::size_t found = s.find(operation);
    if (found != std::string::npos)
        i = found;
    std::size_t found2 = s.find(";");
    if (found2 != std::string::npos)
        j = found2;
    std::string right = s.substr (i+2,j-(i+2));
    return right;
}

int main(){
    std::ifstream myfile; 
    myfile.open("math.txt");
    std::string mystring;
    std::string myline;
    if ( myfile.is_open() ) { 
        while ( myfile.good() ) {
            std::getline (myfile, myline);
            std::cout << myline << '\n';
        } 
    }
    if (delimiter(myline) == false){
        std::cout << "Expected ;" << std::endl;
        return 0;
    }
    if (declare(myline) == false){
        std::cout << "Undefined variable" << std::endl;
        return 0;
    }
    if (names(myline) == ""){
        std::cout << "Unavailable name of variable" << std::endl;
        return 0;
    }
    std::string type_left, type_right;
    char operation;
    for(int i = 0; i < myline.length(); ++i){
        if (myline[i] == '+' || myline[i] == '-' || myline[i] == '*' || myline[i] == '/' || myline[i] == '%')
            operation = myline[i];
    }
    std::string left = left_operand(myline);
    std::string right = right_operand(myline);
    for(int i = 0; i < left.length(); ++i){
        if(isdigit(left[i]) && !(left.find(".") != std::string::npos))
            type_left = "int";
        else if (isdigit(left[i]) && left.find(".") != std::string::npos)
            type_left = "double";
    }
    for(int i = 0; i < right.length(); ++i){
        if(isdigit(right[i]) && !(right.find(".") != std::string::npos))
            type_right = "int";
        else if (isdigit(right[i]) && right.find(".") != std::string::npos)
            type_right = "double";
    }
    if (type_left == "int" && type_right == "int"){
        if(operation == '+'){
            std::cout << type_left << " "<< names(myline) << " = " << sum(stoi(left),stoi(right)) << ";" << std::endl;
        }
        else if(operation == '-'){
            std::cout << type_left << " "<< names(myline) << " = " << sub(stoi(left),stoi(right)) << ";" << std::endl;
        }
        else if(operation == '*'){
            std::cout << type_left << " "<< names(myline) << " = " << mul(stoi(left),stoi(right)) << ";" << std::endl;
        }
        else if(operation == '/'){
            if(stoi(right)==0){
                std::cout << "Zero division error" << std::endl;
                return 0;
            }
            std::cout << type_left << " "<< names(myline) << " = " << division(stoi(left),stoi(right)) << ";" << std::endl;
        }
        else if(operation == '%'){
            std::cout << type_left << " "<< names(myline) << " = " << mod(stoi(left),stoi(right)) << ";" << std::endl;
        }
    }
    else if (type_left == "double" && type_right == "double"){
        if(operation == '+'){
            std::cout << type_left << " "<< names(myline) << " = " << sum(stod(left),stod(right)) << ";" << std::endl;
        }
        else if(operation == '-'){
            std::cout << type_left << " "<< names(myline) << " = " << sub(stod(left),stod(right)) << ";" << std::endl;
        }
        else if(operation == '*'){
            std::cout << type_left << " "<< names(myline) << " = " << mul(stod(left),stod(right)) << ";" << std::endl;
        }
        else if(operation == '/'){
            if(stod(right)==0){
                std::cout << "Zero division error" << std::endl;
                return 0;
            }
            std::cout << type_left << " "<< names(myline) << " = " << division(stod(left),stod(right)) << ";" << std::endl;
        }
        if (operation == '%'){
            std::cout << "% operation does not working with this type"<<std::endl;
            return 0;
        }
    }
    else{
        std::cout<<"Type conflict" << std::endl;
        return 0;
    }    

    return 0;
}