#include <stdio.h>
#include <iostream>
// #include <string.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <utility>
#include <unistd.h>
#include <sys/stat.h>
// #include <functional>
#include <stack>
#include <queue>

#define INPUT_FILE "hist.txt"

bool check_input(std::string input)
{
    for (int i = 0; i < input.length(); ++i)
        if (isdigit(input[i]) == false)
            return false;
    return true;
}

inline bool check_exist_file(const std::string &file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

void create_file(const std::string &file_name)
{
    std::string value = "0";
    std::ofstream out_file(file_name);

    out_file << value << std::endl;
    out_file.close();
}

void write_file()
{
    std::cout << "Write the stack to file" << std::endl;
}

void display_five_lines(const std::string &file_name)
{
    std::string num1, num2, num3;
    std::string opera, equal;

    std::ifstream file_(file_name);

    while (file_ >> num1 >> opera >> num2 >> equal >> num3)
    {
        if (num2 != "")
        {
            std::cout << num1 << " " << opera << " " << num2 << " " << equal << " " << num3 << std::endl;
        }
        else
        {
            std::cout << num1 << std::endl;
        }
    }
    file_.close();
    std::cin.get();
}

double add(double a, double b)
{
    return a + b;
}

double sub(double a, double b)
{
    return a - b;
}

double mul(double a, double b)
{
    return a * b;
}

double div(double a, double b)
{
    return a / b;
}

void operators(char opert, double a, double b, double &ans, std::stack<std::string> &st_container)
{
    switch (opert)
    {
    case '+':
        // std::cout << "ans: " << ans << std::endl;
        ans = add(a, b);
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(add(a, b)));
        break;

    case '-':
        ans = sub(a, b);
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(add(a, b)));
        break;

    case 'x':
        ans = mul(a, b);
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(mul(a, b)));
        break;

    case '*':
        ans = mul(a, b);
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(mul(a, b)));
        break;

    case '/':
        if (a != 0)
        {
            ans = div(a, b);
            st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(div(a, b)));
        }
        else
        {
            std::cout << "MATH ERROR" << std::endl;
        }
        break;

    case '%':
        if (a != 0)
        {
            ans = div(a, b);
            st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(div(a, b)));
        }
        else
        {
            std::cout << "MATH ERROR" << std::endl;
        }
        break;

    default:
        std::cout << "SYNTAX ERROR" << std::endl;
        break;
    }
}

int main()
{
    std::string num1 = "0", num2;
    char opert[] = "";
    std::string ans = "0";
    std::string file_name = "log.txt";
    std::string choice;
    
    int line = 0;

    std::stack<std::string> st_container;
    std::stack<std::string> st_history = st_container;
    std::stack<std::string> st_result = st_container;

    std::cout << ">> ";
    std::getline(std::cin, choice);
    std::istringstream iss(choice);

    iss >> num1 >> opert >> num2;
    while (num1 != "EXIT")
    {
        if (num1.compare("EXIT") == 0)
        {
            exit(0);
        }
        if (num1.length() == 0)
        {
            std::cout << "SYNTAX ERROR" << std::endl;
        }
        else
        {
            if (check_input(num1))
            {
                if (strlen(opert) == 0)
                {
                    std::cout << "SYNTAX ERROR" << std::endl;
                    if (num2.length() == 0)
                    {
                        std::cout << "SYNTAX ERROR" << std::endl;
                    }
                }
                else
                {
                    // std::cout << num1 << "is a integer" << std::endl;
                    operators(opert[0], std::stod(num1), std::stod(num2), std::to_string(ans), st_container);
                    while (!st_result.empty())
                    {
                        std::cout << st_result.top() << std::endl;
                        st_result.pop();
                    }
                }
            }
            else
            {
                if (num1 == "ANS")
                {
                    num1 = ans;
                }
                else if (num1 == "HIST")
                {
                    // if (check_exist_file(file_name) == true)
                    // {
                    //     display_five_lines(file_name);
                    // }
                    // else
                    // {
                    //     create_file(file_name);
                    // }
                    if (st_history.empty())
                    {
                        std::cout << "History is empty" << std::endl;
                    }
                    else
                    {
                        while (!st_history.empty())
                        {
                            if (line == 5)
                            {
                                break;
                            }
                            std::cout << st_history.top() << std::endl;
                            st_history.pop();
                            ++line;
                        }
                    }
                }
                else
                {
                    std::cout << "SYNTAX ERROR" << std::endl;
                }
            }
        }
        std::cout << ">> ";
        std::getline(std::cin, choice);
        std::istringstream iss(choice);

        iss >> num1 >> opert >> num2;
    }
    return 0;
}