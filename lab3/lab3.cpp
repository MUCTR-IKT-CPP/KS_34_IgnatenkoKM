#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h>

using namespace std;

enum class CharacterClass
{
    Warrior,
    Mage,
    Rogue,
    Cleric
};

struct GameCharacter
{
    string name;
    CharacterClass character_class;
    int level;
    int health;
    int mana;
    vector<string> inventory;
};

vector<string> items =
{
    "Меч",
    "Щит",
    "Зелье",
    "Лук",
    "Посох",
    "Шлем",
    "Броня",
    "Кольцо",
    "Золото",
    "Сапоги",
    "Амулет"
};


ostream& operator<<(ostream& output, CharacterClass character_class)
{
    switch (character_class)
    {
    case CharacterClass::Warrior:
        return output << "Воин";

    case CharacterClass::Mage:
        return output << "Маг";

    case CharacterClass::Rogue:
        return output << "Разбойник";

    case CharacterClass::Cleric:
        return output << "Жрец";
    }

    return output << "Неизвестный класс";
}

/**
 * Генерирует случайное имя персонажа
 */
string generate_name(int number)
{
    vector<string> names =
    {
        "Александр",
        "Иван",
        "Дмитрий",
        "Максим",
        "Артём",
        "Михаил",
        "Анна",
        "Мария",
        "Елена",
        "София"
    };

    string name = names[rand() % names.size()];

    return name;
}

/**
 * Создает одного персонажа со случайными характеристиками
 */
GameCharacter generate_character(int number)
{
    GameCharacter character;

    character.name = generate_name(number);

    character.character_class = static_cast<CharacterClass>(rand() % 4);

    character.level = rand() % 60 + 1;

    character.health = rand() % 151 + 50;

    character.mana = rand() % 131 + 20;

    int item_count = rand() % 6;

    for (int i = 0; i < item_count; i++)
    {
        int item_number = rand() % items.size();

        character.inventory.push_back(items[item_number]);
    }

    return character;
}

/**
 * Выводит информацию об одном персонаже
 */
void print_character(const GameCharacter& character)
{
    cout << "Имя: " << character.name << endl;

    cout << "Класс: " << character.character_class << endl;

    cout << "Уровень: " << character.level << endl;

    cout << "Здоровье: " << character.health << endl;

    cout << "Мана: " << character.mana << endl;

    cout << "Инвентарь: ";

    if (character.inventory.empty())
    {
        cout << "пуст";
    }
    else
    {
        for (const string& item : character.inventory)
        {
            cout << item << " ";
        }
    }

    cout << endl;
}

/**
 * Выводит всех персонажей
 */
void print_all_characters(const vector<GameCharacter>& characters)
{
    cout << "\n========== ВСЕ ПЕРСОНАЖИ ==========\n";

    for (const GameCharacter& character : characters)
    {
        print_character(character);
        cout << "-----------------------------------\n";
    }
}

/**
 * Находит всех персонажей, у которых в инвентаре есть указанный предмет
 */
void find_item(const vector<GameCharacter>& characters)
{
    string wanted_item;

    cout << "\nВведите название предмета: ";
    cin >> wanted_item;

    bool found = false;

    cout << "\nПерсонажи с предметом \"" << wanted_item << "\":\n";

    for (const GameCharacter& character : characters)
    {
        for (const string& item : character.inventory)
        {
            if (item == wanted_item)
            {
                cout << "- " << character.name << endl;

                found = true;

                break;
            }
        }
    }

    if (!found)
    {
        cout << "Такой предмет не найден.\n";
    }
}

/**
 * Находит персонажа с максимальным и минимальным уровнем среди персонажей указанного класса
 */
void compare_levels(const vector<GameCharacter>& characters)
{
    int class_number;

    cout << "\nВыберите класс:\n";
    cout << "0 - Воин\n";
    cout << "1 - Маг\n";
    cout << "2 - Разбойник\n";
    cout << "3 - Жрец\n";
    cout << "Ваш выбор: ";
    cin >> class_number;

    if (class_number < 0 || class_number > 3)
    {
        cout << "Неверный номер класса.\n";
        return;
    }

    CharacterClass selected_class = static_cast<CharacterClass>(class_number);

    bool found = false;

    GameCharacter max_character;
    GameCharacter min_character;

    for (const GameCharacter& character : characters)
    {
        if (character.character_class == selected_class)
        {
            if (!found)
            {
                max_character = character;
                min_character = character;

                found = true;
            }
            else
            {
                if (character.level > max_character.level)
                {
                    max_character = character;
                }

                if (character.level < min_character.level)
                {
                    min_character = character;
                }
            }
        }
    }

    if (!found)
    {
        cout << "Персонажей такого класса нет.\n";
        return;
    }

    cout << "\n===== МАКСИМАЛЬНЫЙ УРОВЕНЬ =====\n";
    print_character(max_character);

    cout << "\n===== МИНИМАЛЬНЫЙ УРОВЕНЬ =====\n";
    print_character(min_character);
}

/**
 * Подсчитывает количество уникальных предметов и находит самый часто встречающийся предмет
 */
void analyze_inventory(const vector<GameCharacter>& characters)
{
    vector<string> unique_items;
    vector<int> item_counts;

    for (const GameCharacter& character : characters)
    {
        for (const string& item : character.inventory)
        {
            bool found = false;

            for (int i = 0; i < unique_items.size(); i++)
            {
                if (unique_items[i] == item)
                {
                    item_counts[i]++;
                    found = true;

                    break;
                }
            }

            if (!found)
            {
                unique_items.push_back(item);
                item_counts.push_back(1);
            }
        }
    }

    cout << "\n========== АНАЛИЗ ИНВЕНТАРЯ ==========\n";

    cout << "Количество уникальных предметов: "
        << unique_items.size() << endl;

    if (unique_items.empty())
    {
        cout << "Предметов нет.\n";
        return;
    }

    int max_index = 0;

    for (int i = 1; i < item_counts.size(); i++)
    {
        if (item_counts[i] > item_counts[max_index])
        {
            max_index = i;
        }
    }

    cout << "Самый часто встречающийся предмет: "
        << unique_items[max_index] << endl;

    cout << "Количество: "
        << item_counts[max_index] << endl;
}

/**
 * Сортирует персонажей по уровню по убыванию, при одинаковом уровне сортирует по количеству
 * предметов в инвентаре по убыванию
 */
void sort_characters(vector<GameCharacter>& characters)
{
    sort(characters.begin(), characters.end(), [](const GameCharacter& first, const GameCharacter& second)
        {

            if (first.level != second.level)
            {
                return first.level > second.level;
            }

            return first.inventory.size() > second.inventory.size();
        }
    );

    cout << "\nПерсонажи отсортированы.\n";
}

/**
 * Добавляет случайный предмет в инвентарь всем персонажам указанного класса
 */
void equip_item(vector<GameCharacter>& characters)
{
    int class_number;

    cout << "\nВыберите класс для экипировки:\n";
    cout << "0 - Воин\n";
    cout << "1 - Маг\n";
    cout << "2 - Разбойник\n";
    cout << "3 - Жрец\n";
    cout << "Ваш выбор: ";
    cin >> class_number;

    if (class_number < 0 || class_number > 3)
    {
        cout << "Неверный номер класса.\n";
        return;
    }

    CharacterClass selected_class = static_cast<CharacterClass>(class_number);

    string random_item = items[rand() % items.size()];

    bool found = false;

    for (GameCharacter& character : characters)
    {
        if (character.character_class == selected_class)
        {
            character.inventory.push_back(random_item);

            found = true;
        }
    }

    if (found)
    {
        cout << "\nПредмет \"" << random_item << "\" добавлен всем персонажам класса " << selected_class << endl;
    }
    else
    {
        cout << "\nПерсонажей такого класса нет.\n";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    srand(time(0));

    int N;

    cout << "Введите количество персонажей: ";
    cin >> N;

    if (N <= 0)
    {
        cout << "Количество персонажей должно быть больше 0.\n";
        return 0;
    }

    vector<GameCharacter> characters;

    for (int i = 0; i < N; i++)
    {
        characters.push_back(generate_character(i + 1));
    }

    print_all_characters(characters);

    int choice;

    do
    {
        cout << "\n========== МЕНЮ ==========\n";
        cout << "1 - Поиск предмета\n";
        cout << "2 - Сравнение уровней\n";
        cout << "3 - Анализ инвентаря\n";
        cout << "4 - Сортировка персонажей\n";
        cout << "5 - Экипировка предмета\n";
        cout << "6 - Показать всех персонажей\n";
        cout << "0 - Выход\n";
        cout << "Ваш выбор: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            find_item(characters);
            break;

        case 2:
            compare_levels(characters);
            break;

        case 3:
            analyze_inventory(characters);
            break;

        case 4:
            sort_characters(characters);
            print_all_characters(characters);
            break;

        case 5:
            equip_item(characters);
            break;

        case 6:
            print_all_characters(characters);
            break;

        case 0:
            cout << "\nПрограмма завершена.\n";
            break;

        default:
            cout << "\nНеверный пункт меню.\n";
        }

    } while (choice != 0);

    return 0;
}
