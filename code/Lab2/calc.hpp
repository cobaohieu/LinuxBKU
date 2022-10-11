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

// void create_file(const std::string &file_name)
// {
//     std::string value = "0";
//     std::ofstream out_file(file_name);

//     out_file << value << std::endl;
//     out_file.close();
// }

// void write_file()
// {
//     std::cout << "Write the stack to file" << std::endl;
// }

// void display_five_lines(const std::string &file_name)
// {
//     std::string num1, num2, num3;
//     std::string opera, equal;

//     std::ifstream file_(file_name);

//     while (file_ >> num1 >> opera >> num2 >> equal >> num3)
//     {
//         if (num2 != "")
//         {
//             std::cout << num1 << " " << opera << " " << num2 << " " << equal << " " << num3 << std::endl;
//         }
//         else
//         {
//             std::cout << num1 << std::endl;
//         }
//     }
//     file_.close();
//     std::cin.get();
// }

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

void operators(char opert, double a, double b, double *const &ans, std::stack<std::string> &st_container)
{
    switch (opert)
    {
    case '+':
        *ans = add(a, b);
        std::cout << *ans << std::endl;
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(add(a, b)));
        break;

    case '-':
        *ans = sub(a, b);
        std::cout << *ans << std::endl;
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(add(a, b)));
        break;

    case 'x':
        *ans = mul(a, b);
        std::cout << *ans << std::endl;
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(mul(a, b)));
        break;

    case '*':
        *ans = mul(a, b);
        std::cout << *ans << std::endl;
        st_container.push(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(mul(a, b)));
        break;

    case '/':
        if (a != 0)
        {
            *ans = div(a, b);
            std::cout << *ans << std::endl;
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
            *ans = div(a, b);
            std::cout << *ans << std::endl;
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
