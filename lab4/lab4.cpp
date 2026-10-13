
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <windows.h>
#include <clocale>

using namespace std;

struct RectangleData
{
    double width;
    double height;
};

struct EllipseData
{
    double radius_x;
    double radius_y;
};

struct TextObject
{
    string text;
};

enum class ObjectType
{
    RECTANGLE,
    ELLIPSE,
    TEXT
};

class GraphicObject
{
public:
    void* object_data;
    ObjectType type;
    int z_index;

    // Создание копии данных
    static void* copyData(ObjectType object_type, const void* data)
    {
        if (data == nullptr)
        {
            return nullptr;
        }

        if (object_type == ObjectType::RECTANGLE)
        {
            const RectangleData* rectangle = static_cast<const RectangleData*>(data);

            return new RectangleData(*rectangle);
        }
        else if (object_type == ObjectType::ELLIPSE)
        {
            const EllipseData* ellipse = static_cast<const EllipseData*>(data);

            return new EllipseData(*ellipse);
        }
        else if (object_type == ObjectType::TEXT)
        {
            const TextObject* text = static_cast<const TextObject*>(data);

            return new TextObject(*text);
        }

        return nullptr;
    }

    
    void deleteData()
    {
        if (object_data == nullptr)
        {
            return;
        }

        if (type == ObjectType::RECTANGLE)
        {
            delete static_cast<RectangleData*>(object_data);
        }
        else if (type == ObjectType::ELLIPSE)
        {
            delete static_cast<EllipseData*>(object_data);
        }
        else if (type == ObjectType::TEXT)
        {
            delete static_cast<TextObject*>(object_data);
        }

        object_data = nullptr;
    }

    // Конструктор по умолчанию
    GraphicObject()
    {
        object_data = new TextObject{ "Пустой текст" };
        type = ObjectType::TEXT;
        z_index = 0;
    }

    // Конструктор с параметрами
    GraphicObject(ObjectType object_type, const void* data, int z)
    {
        type = object_type;
        object_data = copyData(object_type, data);
        z_index = z;
    }

    // Конструктор копирования
    GraphicObject(const GraphicObject& other)
    {
        type = other.type;
        object_data = copyData(other.type, other.object_data);
        z_index = other.z_index;
    }

    // Оператор копирующего присваивания
    GraphicObject& operator=(const GraphicObject& other)
    {
        if (this != &other)
        {
            void* new_data = copyData(other.type, other.object_data);

            deleteData();

            type = other.type;
            object_data = new_data;
            z_index = other.z_index;
        }

        return *this;
    }

    // Конструктор перемещения
    GraphicObject(GraphicObject&& other) noexcept
    {
        object_data = other.object_data;
        type = other.type;
        z_index = other.z_index;

        other.object_data = nullptr;
    }

    // Оператор перемещающего присваивания
    GraphicObject& operator=(GraphicObject&& other) noexcept
    {
        if (this != &other)
        {
            deleteData();

            object_data = other.object_data;
            type = other.type;
            z_index = other.z_index;

            other.object_data = nullptr;
        }

        return *this;
    }

    ~GraphicObject()
    {
        deleteData();
    }

    // Вывод информации об объекте
    void print() const
    {
        cout << "Z-index: " << z_index << " | ";

        if (object_data == nullptr)
        {
            cout << "Данные отсутствуют" << endl;
            return;
        }

        if (type == ObjectType::RECTANGLE)
        {
            const RectangleData* rectangle = static_cast<const RectangleData*>(object_data);

            cout << "Прямоугольник" << ", ширина: " << rectangle->width << ", высота: " << rectangle->height;
        }
        else if (type == ObjectType::ELLIPSE)
        {
            const EllipseData* ellipse = static_cast<const EllipseData*>(object_data);

            cout << "Эллипс" << ", радиус X: " << ellipse->radius_x << ", радиус Y: " << ellipse->radius_y;
        }
        else if (type == ObjectType::TEXT)
        {
            const TextObject* text = static_cast<const TextObject*>(object_data);

            cout << "Текст: " << text->text;
        }

        cout << endl;
    }
};

class Canvas
{
private:
    vector<GraphicObject> objects;

    bool hasZIndex(int z) const
    {
        for (int i = 0; i < static_cast<int>(objects.size()); i++)
        {
            if (objects[i].z_index == z)
            {
                return true;
            }
        }

        return false;
    }

public:
    // Конструктор по умолчанию
    Canvas() = default;

    // Конструктор с параметрами
    Canvas(const vector<GraphicObject>& initial_objects)
        : objects(initial_objects)
    {
    }

    // Конструктор копирования
    Canvas(const Canvas& other)
        : objects(other.objects)
    {
    }

    // Оператор копирующего присваивания
    Canvas& operator=(const Canvas& other)
    {
        if (this != &other)
        {
            objects = other.objects;
        }

        return *this;
    }

    // Конструктор перемещения
    Canvas(Canvas&& other) noexcept
        : objects(move(other.objects))
    {
    }

    // Оператор перемещающего присваивания
    Canvas& operator=(Canvas&& other) noexcept
    {
        if (this != &other)
        {
            objects = move(other.objects);
        }

        return *this;
    }

    ~Canvas() = default;

    void addRectangle(double width, double height, int z)
    {
        if (hasZIndex(z))
        {
            cout << "Такой z_index уже существует!" << endl;
            return;
        }

        RectangleData rectangle{ width, height };

        GraphicObject object(ObjectType::RECTANGLE, &rectangle, z);

        objects.push_back(move(object));

        cout << "Прямоугольник добавлен." << endl;
    }

    void addEllipse(double radius_x, double radius_y, int z)
    {
        if (hasZIndex(z))
        {
            cout << "Такой z_index уже существует!" << endl;
            return;
        }

        EllipseData ellipse{ radius_x, radius_y };

        GraphicObject object(
            ObjectType::ELLIPSE, &ellipse, z);

        objects.push_back(move(object));

        cout << "Эллипс добавлен." << endl;
    }

    void addText(const string& text, int z)
    {
        if (hasZIndex(z))
        {
            cout << "Такой z_index уже существует!" << endl;
            return;
        }

        TextObject text_object{ text };

        GraphicObject object(
            ObjectType::TEXT, &text_object, z);

        objects.push_back(move(object));

        cout << "Текстовый объект добавлен." << endl;
    }

    void changeZIndex(int old_z, int new_z)
    {
        for (int i = 0; i < static_cast<int>(objects.size()); i++)
        {
            if (objects[i].z_index == old_z)
            {
                if (old_z != new_z && hasZIndex(new_z))
                {
                    cout << "Новый z_index уже занят!" << endl;
                    return;
                }

                objects[i].z_index = new_z;

                cout << "z_index успешно изменен." << endl;
                return;
            }
        }

        cout << "Объект с таким z_index не найден." << endl;
    }

    void sortObjects()
    {
        sort(objects.begin(), objects.end(), [](const GraphicObject& a, const GraphicObject& b)
            {
                return a.z_index < b.z_index;
            });

        cout << "Объекты отсортированы по z_index." << endl;
    }

    void removeObject(int z)
    {
        for (int i = 0; i < static_cast<int>(objects.size()); i++)
        {
            if (objects[i].z_index == z)
            {
                objects.erase(objects.begin() + i);

                cout << "Объект удален." << endl;
                return;
            }
        }

        cout << "Объект с таким z_index не найден." << endl;
    }

    void printObjects() const
    {
        if (objects.empty())
        {
            cout << "Холст пуст." << endl;
            return;
        }

        cout << "\n===== Список объектов =====" << endl;

        for (int i = 0; i < static_cast<int>(objects.size()); i++)
        {
            objects[i].print();
        }

        cout << "===========================" << endl;
    }
};

// Главная функция
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "");



    Canvas canvas;

    int choice = -1;

    do
    {
        cout << "\n===== ГРАФИЧЕСКИЙ ХОЛСТ =====" << endl;
        cout << "1. Добавить прямоугольник" << endl;
        cout << "2. Добавить эллипс" << endl;
        cout << "3. Добавить текст" << endl;
        cout << "4. Показать все объекты" << endl;
        cout << "5. Изменить z_index" << endl;
        cout << "6. Сортировать по z_index" << endl;
        cout << "7. Удалить объект по z_index" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        if (!(cin >> choice))
        {
            cout << "Ошибка ввода. Программа завершена." << endl;
            break;
        }

        if (choice == 1)
        {
            double width, height;
            int z;

            cout << "Введите ширину: ";
            cin >> width;

            cout << "Введите высоту: ";
            cin >> height;

            cout << "Введите z_index: ";
            cin >> z;

            canvas.addRectangle(width, height, z);
        }
        else if (choice == 2)
        {
            double radius_x, radius_y;
            int z;

            cout << "Введите радиус X: ";
            cin >> radius_x;

            cout << "Введите радиус Y: ";
            cin >> radius_y;

            cout << "Введите z_index: ";
            cin >> z;

            canvas.addEllipse(radius_x, radius_y, z);
        }
        else if (choice == 3)
        {
            string text;
            int z;

            cout << "Введите текст: ";
            getline(cin >> ws, text);

            cout << "Введите z_index: ";
            cin >> z;

            canvas.addText(text, z);
        }
        else if (choice == 4)
        {
            canvas.printObjects();
        }
        else if (choice == 5)
        {
            int old_z, new_z;

            cout << "Введите текущий z_index: ";
            cin >> old_z;

            cout << "Введите новый z_index: ";
            cin >> new_z;

            canvas.changeZIndex(old_z, new_z);
        }
        else if (choice == 6)
        {
            canvas.sortObjects();
            canvas.printObjects();
        }
        else if (choice == 7)
        {
            int z;

            cout << "Введите z_index объекта для удаления: ";
            cin >> z;

            canvas.removeObject(z);
        }
        else if (choice != 0)
        {
            cout << "Неизвестная команда!" << endl;
        }

    } while (choice != 0);

    cout << "Программа завершена." << endl;

    return 0;
}
