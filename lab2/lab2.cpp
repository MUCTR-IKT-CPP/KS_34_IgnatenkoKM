#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int** createMap(int n)
{
    int** map = new int* [n];

    for (int i = 0; i < n; i++)
    {
        map[i] = new int[n];
    }

    return map;
}


void deleteMap(int** map, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] map[i];
    }

    delete[] map;
}


void fillMap(int** map, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            map[i][j] = rand() % 2;
        }
    }
}


void printMap(int** map, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";
        }

        cout << endl;
    }
}


void countShips(int** map, int n)
{

    int** used = createMap(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            used[i][j] = 0;
        }
    }

    int count = 0;

    cout << "Размеры кораблей: ";

    //горизонтальные корабли
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == 1 && used[i][j] == 0)
            {
                if (j == 0 || map[i][j - 1] == 0)
                {
                    int size = 0;
                    int k = j;

                    while (k < n && map[i][k] == 1)
                    {
                        size++;
                        k++;
                    }

                    if (size >= 2)
                    {
                        cout << size << " ";
                        count++;

                        for (int x = j; x < j + size; x++)
                        {
                            used[i][x] = 1;
                        }
                    }
                }
            }
        }
    }

    //вертикальные корабли
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == 1 && used[i][j] == 0)
            {
                if (i == 0 || map[i - 1][j] == 0)
                {
                    int size = 0;
                    int k = i;

                    while (k < n &&
                        map[k][j] == 1 &&
                        used[k][j] == 0)
                    {
                        size++;
                        k++;
                    }

                    if (size >= 2)
                    {
                        cout << size << " ";
                        count++;

                        for (int x = i; x < i + size; x++)
                        {
                            used[x][j] = 1;
                        }
                    }
                }
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == 1 && used[i][j] == 0)
            {
                cout << "1 ";
                count++;

                used[i][j] = 1;
            }
        }
    }


    cout << endl;
    cout << "Количество кораблей = " << count << endl;

    deleteMap(used, n);
}


void mirrorMap(int** map, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            int temp = map[i][j];

            map[i][j] = map[i][n - 1 - j];

            map[i][n - 1 - j] = temp;
        }
    }
}


void deleteShip(int** map, int n, int row, int col)
{
    if (row < 0 || row >= n || col < 0 || col >= n)
    {
        cout << "Неверные координаты." << endl;
        return;
    }

    if (map[row][col] == 0)
    {
        cout << "В этой клетке нет корабля." << endl;
        return;
    }


    int start = col;

    while (start > 0 && map[row][start - 1] == 1)
    {
        start--;
    }

    int end = col;

    while (end < n - 1 && map[row][end + 1] == 1)
    {
        end++;
    }

    if (end - start + 1 >= 2)
    {
        for (int j = start; j <= end; j++)
        {
            map[row][j] = 0;
        }

        cout << "Корабль удалён." << endl;
        return;
    }


    start = row;

    while (start > 0 && map[start - 1][col] == 1)
    {
        start--;
    }

    end = row;

    while (end < n - 1 && map[end + 1][col] == 1)
    {
        end++;
    }

    if (end - start + 1 >= 2)
    {
        for (int i = start; i <= end; i++)
        {
            map[i][col] = 0;
        }

        cout << "Корабль удалён." << endl;
        return;
    }


    map[row][col] = 0;

    cout << "Корабль удалён." << endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    srand(time(0));

    int n;

    cout << "Введите размер карты N: ";
    cin >> n;


    if (n <= 0)
    {
        cout << "Размер должен быть больше 0." << endl;
        return 0;
    }


    int** map = createMap(n);


    fillMap(map, n);


    cout << endl;
    cout << "Карта бухты:" << endl;

    printMap(map, n);


    while (true)
    {
        cout << endl;
        cout << "Выберите действие:" << endl;
        cout << "1 - Посчитать корабли и их размеры" << endl;
        cout << "2 - Отразить карту зеркально" << endl;
        cout << "3 - Удалить корабль по координатам" << endl;
        cout << "0 - Завершить программу" << endl;

        int choice;

        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1)
        {
            countShips(map, n);
        }
        else if (choice == 2)
        {
            mirrorMap(map, n);

            cout << endl;
            cout << "Карта после отражения:" << endl;

            printMap(map, n);
        }
        else if (choice == 3)
        {
            int row;
            int col;

            cout << "Введите строку: ";
            cin >> row;

            cout << "Введите столбец: ";
            cin >> col;

            deleteShip(map, n, row, col);

            cout << endl;
            cout << "Карта после удаления:" << endl;

            printMap(map, n);
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            cout << "Неверный выбор." << endl;
        }
    }


    deleteMap(map, n);

    return 0;
}