#include <fstream>
#include <iostream>
#include <utility>
#include <queue>
#include <string>

void check_exits_and_create_file_if_not()
{

    std::fstream my_file;
    std::string file_name = "log.txt";
    my_file.open(file_name, std::ios::out);
    if (!my_file)
    {
        std::cout << "File is not created!" << std::endl;
    }
    else
    {
        std::cout << "File is created successfully!" << std::endl;
    }
}

void read_file()
{
}

int main()
{
    std::string file_name = "log.txt";
    std::string num1, num2, num3;
    std::string opera, equal;

    std::ifstream file_(file_name);
    if (file_.is_open())
    {
        while (file_ >> num1)
        {
            while (file_ >> num1 >> opera >> num2 >> equal >> num3)
            {
                std::cout << num1 << " " << opera << " " << num2 << " " << equal << " " << num3 << std::endl;
            }
            std::cout << num1 << std::endl;
        }
        file_.close();
    }
    else
    {
        std::cout << "File is not open" << '\n';
    }
    std::cin.get();

    // std::queue <std::pair<int, std::string>> q;
    // int num;
    // std::string content;
    // while (in_file >> num >> content){
    //     q.emplace(num, content);
    // }
    // while (!q.empty())
    // {
    //     const auto& pair = q.front();
    //     std::cout << pair.first << ' ' << pair.second << '\n';
    //     q.pop();
    // }

    // ######
    // int num1, num2, num3;
    // char opert[2], balc[2];
    // std::ifstream fin("log.txt");
    // fin >> num1 >> opert >> num2 >> balc >> num3;
    // fin.close();
    // std::cout << std::endl
    //           << num1 << " " << opert << " " << num2 << " " << balc << " " << num3;

    // std::fstream my_file;
    // my_file.open(file_name, std::ios::in);
    // if (!my_file){
    //     std::cout << "No such file";
    // }
    // else {
    //     char ch;
    //     while (5){
    //         my_file >> ch;
    //         if (my_file.eof()){
    //             break;
    //         }
    //         std::cout << ch;
    //     }
    // }
    // my_file.close();

    // for (unsigned int i = 0U, i < 5U; ++i)
    // {
    //     std::getline(text_file_stream, file_name);
    // }

    return 0;
}