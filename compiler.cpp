#include <iostream>
#include <sstream> 
#include <string>
#include <fstream>
#include <vector>

std::string parse(std::string text);
std::string lexer(std::vector<int> commands);

int main(int argc, char *argv[])
{
    std::ifstream infile(argv[1]);
    std::ofstream outfile;
    std::string line;

    if(argv[2])
        outfile.open(argv[2]);
    else
        outfile.open("a.txt");    

    while(std::getline(infile, line))
    {
        std::istringstream iss(line);
        outfile << parse(line);
    }

    return 0;
}

std::string parse(std::string text)
{
    enum commands {add, subtract, go, right, left, input, display, STARTLOOP, ENDLOOP};

    std::vector<int> commands;

    std::istringstream iss (text);
    std::string val;
    std::vector<std::string> words;
    
    iss >> val;
    words.push_back(val);
    iss >> val;
    words.push_back(val);

        if(words[0] == "add")
        {
            commands.push_back(add);
            commands.push_back(std::stoi(words[1]));
        }else if(words[0] == "subtract")
        {
            commands.push_back(subtract);
            commands.push_back(std::stoi(words[1]));
        }else if(words[0] == "go")
        {
            commands.push_back(go);
            if(words[1] == "right")
                commands.push_back(right);
            else if(words[1] == "left")
               commands.push_back(left); 
        }else if(words[0] == "input")
        {
            commands.push_back(input);
        }else if(words[0] == "display")
        {
            commands.push_back(display);
        }else if(words[0] == "<")
        {
            commands.push_back(STARTLOOP);
        }else if(words[0] == ">")
        {
            commands.push_back(ENDLOOP);
        }
    
    return lexer(commands);
}

std::string lexer(std::vector<int> command)
{
    enum {add, subtract, go, right, left, input, display, STARTLOOP, ENDLOOP};
    std::string output = "";

    if(command.size() == 0)
    {
        std::cout << "error command not found" << std::endl;
        return "";
    }

    switch(command[0])
    {
        case add:
            for(int i = 0; i < command[1]; i++)
            {
                output += "+";
            }
            break;
        case subtract:
            for(int i = 0; i < command[1]; i++)
            {
                 output += "-";
            }
            break;
        case go:
            if(command[1] == right)
                output += ">";
            else if(command[1] == left)
                output += "<";
            break;
        case input:
            output += ",";
            break;
        case display:
            output += ".";
            break;
        case STARTLOOP:
            output += "[";
            break;
        case ENDLOOP:
            output += "]";
            break;
        default:
            std::cout << "COMMAND NOT FOUND" << std::endl;
            return "";
    }

    return output;
}