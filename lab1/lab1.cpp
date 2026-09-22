#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void fillArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100 + 1;
    }
}

void reverseArray(int a[], int left, int right)
{
    while (left < right)
    {
        int temp = a[left];
        a[left] = a[right];
        a[right] = temp;

        left++;
        right--;
    }
}

void shiftRight(int a[], int n, int k)
{
    reverseArray(a, 0, n - 1);
    reverseArray(a, 0, k - 1);
    reverseArray(a, k, n - 1);
}

int sumArray(int a[], int n)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + a[i];
    }

    return sum;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int n = 10;
    int k = 8;

    int a[10];

    fillArray(a, n);

    cout << "Исходный массив: ";

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;

    shiftRight(a, n, k);

    cout << "Массив после сдвига: ";

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;


    cout << "Сумма: " << sumArray(a, n) << endl;

    return 0;
}