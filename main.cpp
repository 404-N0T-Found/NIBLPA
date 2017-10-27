#include <iostream>
#include <cmath>
using namespace std;
int soal1()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cout << n * i << "   ";
}
bool perfect(int n)
{
    int s = 1;
    for (int i = 2; i <= int(pow(n, 0.5)); i++)
        if (n % i == 0)
        {
            s += i;
            if (int(n / i) != i)
                s += int (n / i);
        }
    return s == n;
}
int soal2()
{
    int n;
    cin >> n;
    for (int i = 6; i <= n; i++)
        if (perfect(i))
            cout << i << "   ";
}
int main()
{
    soal2();
    return 0;
}
