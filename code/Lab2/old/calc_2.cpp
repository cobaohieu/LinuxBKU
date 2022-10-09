#include <iostream>
#include <iomanip>
#include <stack>
using namespace std;
#include <fstream>
void check(string &a, string &b, string c, int &flag)
{
    if (a == "ANS")
    {
        a = c;
        flag = 1;
    }
    if (b == "ANS")
    {
        b = c;
        flag = 2;
    }
}
void save(int &flag, stack<string> &q, string &a, string ch, string &b, string ans)
{
    if (flag == 0)
    {
        q.push(a + " " + ch + " " + b + " = " + ans);
    }
    else if (flag == 1)
    {
        q.push("ANS " + ch + " " + b + " = " + ans);
    }
    else if (flag == 2)
    {
        q.push(a + " " + ch + " ANS= " + ans);
    }
}
int main()
{
    string a, ch, b;
    string ans = "0";
    a = "0";
    string res = "0";
    int flag = 0;
    std::stack<string> q;

    while (a != "EXIT")
    {
        cout << ">> ";
        cin >> a;
        if (a == "HIST")
        {
            stack<string> q1 = q;
            int i = 0;
            if (q1.empty())
                cout << "No history";
            else
            {
                while (!q1.empty())
                {
                    if (i == 5)
                        break;
                    cout << q1.top() << endl;
                    q1.pop();
                    i++;
                }
            }
        }
        else
        {
            cin >> ch;
            cin >> b;

            if (ch == "+")
            {
                check(a, b, ans, flag);
                cout << stoi(a) + stoi(b) << endl;

                ans = to_string(stoi(a) + stoi(b));
                save(flag, q, a, ch, b, ans);
            }
            else if (ch == "-")
            {
                check(a, b, ans, flag);
                cout << stof(a) - stof(b) << endl;

                ans = to_string(stoi(a) - stoi(b));
                save(flag, q, a, ch, b, ans);
            }
            else if (ch == "%")
            {
                check(a, b, ans, flag);
                if (stoi(b) == 0)
                    cout << "MATH ERROR" << endl;
                else
                {

                    cout << stoi(a) / stoi(b) << endl;

                    ans = to_string(stoi(a) / stoi(b));
                    save(flag, q, a, ch, b, ans);
                }
            }
            else if (ch == "x")
            {
                check(a, b, ans, flag);
                cout << stoi(a) * stoi(b) << endl;

                ans = to_string(stoi(a) * stoi(b));
                save(flag, q, a, ch, b, ans);
            }
            else if (ch == "/")
            {
                check(a, b, ans, flag);
                if (stoi(b) == 0)
                    cout << "MATH ERROR" << endl;
                else
                {
                    int a1 = stoi(a);
                    int b1 = stoi(b);
                    double t = (double)a1 / b1;
                    cout << fixed << setprecision(2) << t << endl;
                    ans = to_string(t);

                    save(flag, q, a, ch, b, ans);
                }
            }
            else
            {
                cout << "SYNTAX ERROR" << endl;
            }
        }
    }

    return 0;
}