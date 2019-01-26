#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
int cnt=0;

bool calculating(int* nums, int i, int sum, string& s){
    cnt++;
    if (i > 0) {

        if (calculating(nums, i - 1, sum - nums[i - 1], s)) {
            s += '-' + to_string(nums[i - 1]);
            return true;
        }

        else if (calculating(nums, i - 1, sum + nums[i - 1], s)) {
            s += '+' + to_string(nums[i - 1]);
            return true;
        }

        return false;
    }

    return sum == 0;
}

int main()
{
    int n;
    cin >> n;
    int* nums=new int[n];
    int sum=0;
    for (int i = 0; i < n-1; ++i) {
        nums[i] = rand() % 1000;
        if (rand()%2) sum+=nums[i];
        else sum-=nums[i];
    }
    nums[n-1]=sum;
        //cin >> nums[i];

    cout << "_______________________\n";

    string res;

    if(!calculating(nums, n, 0, res))
        cout << "No solution\n";
    else {
        if (res[0] == '+') {
            for (int i = 1; i < res.size(); ++i)
                cout << res[i];
        }

        else {

            for (int i = 1; i < res.size(); ++i) {

                if (res[i] == '-')
                    cout << '+';
                else if(res[i] == '+')
                    cout << '-';
                else
                    cout << res[i];
            }

        }

        cout << "=0\n";
    }
    cout<<cnt<<endl;
    return 0;
}