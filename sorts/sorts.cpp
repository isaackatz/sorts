// sorts.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <clocale>
#include <vector>
#include <time.h>
using namespace std;

typedef int elem;
typedef vector<elem> numbers;

// получение случайного элемента
elem getRandomNumber(elem min, elem max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<elem>(rand() * fraction * (max - min + 1) + min);
}
// ввод данных в массив
numbers inputMas(int n, elem max)
{
    numbers mas;
    elem el;

    for (int i = 0; i < n; i++)
    {
        el = getRandomNumber(0, max);
        mas.push_back(el);
    }

    return mas;
}
// чтение элементов массива
void readMas(numbers mas)
{
    int i = 0;
    for (elem el : mas)
    {   
        //i++;
        //cout << "["<< i << "]: " << el << endl;
        cout << el << " ";
    }

    cout << endl;
}
// сортировка Гномов
numbers GnomeSort(int n, numbers mas)
{

    int i = 0;
    while (i < n)
    {
        if (i == 0 || mas[i - 1] <= mas[i])
            i++;
        else
        {
            elem t; 
            t = mas[i];
            mas[i] = mas[i-1]; 
            mas[i - 1] = t;
            i--;
        }
    }
    
    return mas;
}

// сортировка Шелла
numbers ShellSort(int n, numbers mas)
{
    int i, j, step;
    elem tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {
            tmp = mas[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < mas[j - step])
                    mas[j] = mas[j - step];
                else
                    break;
            }
            mas[j] = tmp;
        }

    return mas;
}

// сортировка Коктейль
numbers CocktailSort(int n, numbers mas)
{

    bool flag = true;
    int start = 0, end = n - 1;
    while (flag) {

        flag = false;
        for (int i = start; i < end; i++) { // проход по элементам слева направо
            if (mas[i] > mas[i + 1]) {
                swap(mas[i], mas[i + 1]);
                flag = true;
            }
        }

        if (!flag) { // если ничего не изменилось, сортировка заканчивается
            break;
        }

        flag = false;
        end--; // уменьшаем указатель с правого конца

        for (int i = end - 1; i >= start; i--) { // проход справа налево
            if (mas[i] > mas[i + 1]) {
                swap(mas[i], mas[i + 1]);
                flag = true;
            }
        }
        start++;
    }

    return mas;
}
// среднее время сортировки
clock_t averageTime(numbers (sortFunc(int, numbers)), int n, elem max)
{
    clock_t t;
    clock_t T = 0;

    int i = 0;
    numbers setStart = inputMas(n, max); // начальный массив
    numbers setFinal;

    for (i = 0; i < 1000; i++)
    {
        t = clock(); // начало отсчета

        setFinal = sortFunc(n, setStart);

        t = clock() - t; // конец отсчета

        T += t; // суммирование времени

        cout << "[" << i + 1 << "] из [" << 1000 << "]"<< endl;
    }

    cout << "Сортировки завершены." << endl;

    //readMas(setFinal); // проверка сортировки массива

    clock_t avT = T / i; // среднее время

    return avT;
}

int main()
{
    setlocale(0, "");
    clock_t tGnome, tShell, tCock; // среднее время сортировки
    int n = 0; // количество количество элементов массива для сортировки

    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите максимальное число диапазона: ";
    elem max = 0; // максимальное число диапазона
    cin >> max;

    /*
    numbers setStart, setFinal;
    setStart = inputMas(n, max);

    cout << "Неотсортированный массив: " << endl;
    readMas(setStart);

    setFinal = CocktailSort(n, setStart);

    cout << "Отсортированный массив: " << endl;
    readMas(setFinal);
    */
    
    
    tGnome = averageTime(GnomeSort, n, max);
    tShell = averageTime(ShellSort, n, max);
    tCock = averageTime(CocktailSort, n, max);
    
    cout << "Среднее время гномьей сортировки : " << tGnome << endl;
    cout << "Среднее время сортировки перемешиванием: " << tCock << endl;
    cout << "Среднее время сортировки Шелла: " << tShell << endl;
    

    return 0;
}


