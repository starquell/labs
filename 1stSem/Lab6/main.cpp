#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(){

    string text, input;
    int kLeft, kRight, norepeat;

    cout << "Enter text " << endl;


    ifstream T;
    T.open("../text.txt");

    while (!T.eof()) {

        getline(T, input);
        cout << input << endl;
        text += ' ' + input;
    }

       cout  << "_________________________" << '\n';


        for (int i = 0; i < text.size(); i++) {

            if (text[i] == ' ' || i == 0) {

                if (text[i]==' ')
                    i++;
                if (i == norepeat)      continue;

                for (int j = text.size() - 1; j >= 0; j--) {
                    if (text[j] == ' ' || j == text.size() - 1) {
                        if (text[j] == ' ')
                            j--;

                        kLeft = i;
                        kRight = j;

                        for (kLeft, kRight; text[kLeft] != ' '; kLeft++, kRight--) {
                            if (text[kLeft] != text[kRight])
                                break;

                            if (text[kLeft + 1] ==' ' && text[kRight - 1] == ' ') {
                                if(kRight == i && kLeft == j)
                                    break;
                                //cout << i << ' ' << j << endl;

                                 kLeft =i;

                                 while(text[kLeft] != ' ' && kLeft != 0)
                                    cout << text[kLeft++];
                                 cout <<" -- ";

                                 norepeat = kRight;
                                  while(text[kRight] != ' ' && kRight != text.size()) {
                                    cout<<text[kRight++];
                                  }
                                    cout << endl;
                                    break;
                            }
                        }
                    }
                }
            }
        }
    return 0;
}