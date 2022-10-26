# include <iostream>
# include <cmath>
# include <string.h>
# include <fstream>
# include <stack>
# include "logic.h"

using namespace std;

int main() {

    string num1, num2, result, ANS;
    char op;
    bool flag1 = false, flag2 = false;
    stack<string> HIST;

    // Check if Save data is available
    ifstream savefile;
    savefile.open("calc_data.txt");
    if (savefile) {
        cout << "Saved data exists" << endl;
        // Save ANS from save file
        savefile >> ANS;
    } else {
        cout << "Saved data doesn't exist" << endl;
        // Create the file
        ofstream savefile("calc_data.txt");
        // Write to the file
        savefile << "0";
        // Save ANS
        ANS = "0";
    }
    // Close the file
    savefile.close();
    
    while (1){
        // Reset op

        cout << ">> ";
        cin >> num1;
        
        if (num1 == "ANS" && cin.get()=='\n'){
            result = ANS;
            cout << result << endl;
        }
        else if (check_number(num1) && cin.get() == '\n'){
            cout << "SYNTAX ERROR" << endl;
        }
        else if (num1 == "ANS" || check_number(num1)){
            cin >> op;
            if (op != NULL && cin.get() == '\n'){
                cout << "SYNTAX ERROR" << endl;
            } 
            else {
                cin >> num2;

                if (num1 == "ANS"){
                    num1 = ANS;
                    // Trigger flag to replace text
                    flag1 = true;

                }

                if (num2 == "ANS"){
                    num2 = ANS;
                    // Trigger flag to replace text
                    flag2 = true;

                }

                result = calculation(num1, op, num2);

                if (!(result == "SYNTAX ERROR" || result == "MATH ERROR")){
                    ANS = result;

                    HIST.push("\n");
                    HIST.push(result);
                    HIST.push(" ");
                    HIST.push("=");
                    HIST.push(" ");
                    if (flag2){
                        HIST.push("ANS");
                        /// Reset flag2
                        flag2 = false;
                    } else {
                        HIST.push(num2);
                    }
                    HIST.push(" ");
                    HIST.push(string(1, op));
                    HIST.push(" ");
                    if (flag1){
                        HIST.push("ANS");
                        /// Reset flag1
                        flag1 = false;
                    } else {
                        HIST.push(num1);
                    }
                }
                cout << result << endl;
            } 
        }
        else {
            if (num1 == "HIST"){
                showq(HIST);
            } else if (num1 == "EXIT"){
                break;
            } else {
                cout << "SYNTAX ERROR" << endl;
            }
        }

    }

    // EXIT to save the ANS
    ofstream savefile1("calc_data.txt");
    savefile1 << ANS <<"\n";
    savefile1.close();
    return 0;
}
