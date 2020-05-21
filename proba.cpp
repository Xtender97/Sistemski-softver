#include <iostream>
#include <iomanip>
#include <cstddef>

using namespace std;

int main(int argc, char *argv[])
{

    unsigned char a = 3;

    cout << hex << setfill('0') <<setw(2)<< (int)a << " " << endl;
}