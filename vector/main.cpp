#include <iostream>
#include "vector.h"
#include <string>
#include <vector>

using namespace std;

int main()
{
    // try
    {
        vector<string> a(1);
        a.resize(-2);
        // a = Vector<string>(1);
        a.push_back("1");

        for (int i = 0; i < a.size(); ++i)
        {
            cout << a[i] << endl;
        }

        cout << endl;

        Vector<string> b{"h", "e", "l", "l", "o"};
        // a = b;
        for (int i = 0; i < a.size(); ++i)
        {
            // a[i] = i * 1.1;
            cout << a[i] << " " << endl;
        }
    }
    // catch (const exception& e) {
    //     cerr << "Error: " << e.what() << endl;
    // }
    
    return 0;
}