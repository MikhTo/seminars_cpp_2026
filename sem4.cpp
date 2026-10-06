#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <iterator>

int main()
{
    // Итераторы
    // Итераторы -- это объекты, 
    // которые используются для доступа к элементам контейнера
    // Давайте создадим итератор для вектора:
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // Создать итератор -- тип_контейнера::iterator имя_переменной
    std::vector<int>::iterator it = vec.begin(); //метод begin возвращает итератор первого элемента контейнера

    // Получить значение:
    std::cout << *it << std::endl;
    it++; // или std::next
    std::cout << *it << std::endl;

    it = vec.begin();
    // Можно перебрать вектор (и любой другой контейнер) с помощью итераторов:
    // vector.end возращает итератор на конец массива
    // формально на элемент следующий за последним
    while(it != vec.end())
    {
        //Для получения значения элемента, который соответсвует итератору,
        //используется оператор *
        std::cout << *it << std::endl;
        //Для итератора определена операция ++
        //после нее it указывает на следующий элемент
        it++;
    }
    // На что похож итератор?

    // У большинства контейнеров есть конструктор от двух итераторов
    std::vector<int> bad_vec{1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,5,6,6,6};
    std::set<int> good_set(bad_vec.begin(), bad_vec.end());
    
    // также итератор можно использовать для вставки элемента(ов)
    it -= 2; // или std::advance(it, -2)
    std::vector<int> tail {10, 11, 12};
    vec.insert(it--, tail.begin(), tail.end());
    
    // у списка есть удобный метод splice, который позволяет перемещать "сшить" несколько списков
    std::list l1 = {1, 2, 3};
    std::list l2 = {4, 5, 6};
    std::list l3 = {7, 8, 9};

    l1.splice(l1.end(), l2);
    l1.splice(l1.begin(), l3);

    // итераторы используются для эффективного поиска в ассоциативных контейнерах
    // сделаем map для того, чтобы это продемонстрировать
    const std::map<std::string, long long int> phone_book {
        {"Saul", 88002253535},
        {"Mr.Shelby", 89997775656},
        {"Mr. Smith", 89097651234 },
        {"Mrs. Smith", 89094321567}
    };

    // .find() производит эффективный поиск
    auto smth = phone_book.find("Mr. Smith");

    // Инвалидация итераторов
    // ВАЖНО:
    // После некоторых действий итератор может начать указывать на несуществующий элемент
    
    std::vector<int> nice_vec {1,2,3,6,7};
    std::cout << "size: "<< nice_vec.size() <<", capacity: "<< nice_vec.capacity() << std::endl;
    
    
    nice_vec.push_back(4);
    std::cout << "size: "<< nice_vec.size() <<", capacity: "<< nice_vec.capacity() << std::endl;
    
    // Что же произойдет?
    auto strange_it = nice_vec.begin();
    //nice_vec.shrink_to_fit();


    for(int i = 0; i < 10; i++)
        nice_vec.push_back(5);

    //*strange_it = 5;

    // Итераторы ввода: читаем числа из stdin, пока не кончатся.
    // eof — default-constructed итератор = "конец потока".
    // default-constructed == сделан без аргументов
    std::istream_iterator<int> in(std::cin);
    std::istream_iterator<int> eof;

    // Конструктор вектора от диапазона [in, eof) —
    // ему достаточно Input-итераторов.
    std::vector<int> v(in, eof);

    std::set<int> s(v.begin(), v.end());



    return 0;
}
