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
#include "calc.hpp"

bool check_input(std::string input);
inline bool check_exist_file(const std::string &file_name);
double add(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double div(double a, double b);
void operators(char opert, double a, double b, double *const &ans, std::stack<std::string> &st_container);

int main()
{
    std::string num1 = "0", num2 = "0";
    char opert[] = "";
    // std::string ans = "0";
    double res = 0;
    double *ans = &res;
    std::string file_name = "log.txt";
    std::string choice;

    int line = 0;

    std::stack<std::string> st_container;
    std::stack<std::string> st_result = st_container;
    do
    {
        num2.clear();
        std::cout << ">> ";
        std::getline(std::cin, choice);
        std::istringstream iss(choice);

        iss >> num1 >> opert >> num2;

        if ((num1.length() == 0) && (std::cin.get() == '\n'))
        {
            std::cout << "SYNTAX ERROR" << std::endl;
        }
        else
        {
            if (check_input(num1))
            {
                if (strlen(opert) == 0) // && std::cin.get() == '\n'))
                {
                    std::cout << "SYNTAX ERROR" << std::endl;
                }
                else
                {
                    operators(opert[0], std::stod(num1), std::stod(num2), ans, st_container);
                    while (!st_result.empty())
                    {
                        std::cout << st_result.top() << std::endl;
                        st_result.pop();
                    }
                }
            }
            else
            {
                if (num1 == "ans")
                {
                    if (strlen(opert) == 0) // && std::cin.get() == '\n'))
                    {
                        std::cout << "SYNTAX ERROR" << std::endl;
                    }
                    else
                    {
                        // if (num2.compare("") == 0 && strlen(opert) != NULL)
                        if ((num2.length() == 0) && (num2.compare("") == 0))
                        {
                            std::cout << "SYNTAX ERROR" << std::endl;
                        }
                        else
                        {
                            std::ostringstream temp;
                            temp << *ans;
                            num1 = temp.str();
                            operators(opert[0], std::stod(num1), std::stod(num2), ans, st_container);
                        }
                    }
                }
                else if (num1 == "HIST")
                {
                    std::stack<std::string> st_history = st_container;
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
    } while (num1 != "EXIT");
    return 0;
}
