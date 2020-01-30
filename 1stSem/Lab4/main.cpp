#include <iostream>
#include <cstring>

using namespace std;

void BinToGray();
void GrayToBin();

int main() {

    int answer;

    char yes;

    do {
        cout << '\n' << "Bin to Gray(1) or Gray to Bin(2) ?" << endl;
        cin>>answer;

        if (answer == 1)
            BinToGray();
        if (answer == 2)
            GrayToBin();

        cout << "Press 'y' to continue" <<endl;
        cin >> yes;

    } while (yes == 'y');

    return 0;
}
void BinToGray() {
    string binary;

    cin>>binary;
    string graycode = binary;

    cout<<"____________________"<<endl;

   for (int i = 0; i < binary.size(); i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            cout << "Only 0 and 1!" << endl;
            return;
        }
    }
    string movebinary = binary;

    for (int i = 0; i < movebinary.size() - 1; i++)
        movebinary[movebinary.size() - i - 1] = movebinary[movebinary.size() - i - 2];

    movebinary[0] = '0';

    for (int i = 0; i < binary.size(); i++) {
        if (binary[i] == movebinary[i])
            graycode[i] = '0';
        else
            graycode[i] = '1';
    }

    cout << graycode << "\n\n";
}


    void GrayToBin() {

        string graycode;
        int check = 0;


        cin >> graycode;
        for (int i = 0; i < graycode.size(); i++) {
            if (graycode[i] != '0' && graycode[i] != '1') {
                cout << "Only 0 and 1!" << endl;
                return;
            }
        }

        string movegray = graycode;
        string binary = graycode;
        string checkmove = movegray;

        for (int i = 1; i < graycode.size(); i++)
        {
            for (int i = 0; i < movegray.size() - 1; i++)
                movegray[movegray.size() - i - 1] = movegray[movegray.size() - i - 2];

            movegray[0] = '0';

            for (int i = 0; i < movegray.size(); i++)
                checkmove[i] += movegray[i];
        }

        for (int i = 0; i < checkmove.size(); i++) {
            if (checkmove[i] % 2 == 0)
                binary[i] = '0';
            else
                binary[i] = '1';
        }

        cout << "_____________________" << endl;
        cout << binary << "\n\n";
}
