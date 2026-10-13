#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int main()
{
    // Алгоритмы
    // Стандартная библиотека предлагает нам множество алгоритмов 
    // для работы с контейнерами
    std::vector<int> sorted_vec{0, -9, 1, -8, 2, 7, -3, 6, 4, 5};

    // Алгоритмы сортировки: первые два аргумента -- итераторы на начало и конец сортируемой последовательност (т.е. можно сортировать не весь вектор)
    std::sort(sorted_vec.begin(), sorted_vec.end()); // по умолчанию сортировка идет по возрастанию

    // Для изменения принципа сортировки передаем в sort lambda функцию
    std::sort(sorted_vec.begin(), sorted_vec.end(), 
        [](int left, int right){return left > right;});

    // Краткое лирическое отступление о лямбда-выражениях в С++
    // Можно сказать, что лямбда - выражение -- это такая безымянная(анонимная) функция 
    // Синтаксис [захваченные параметры](аргументы){тело}
    int x = 5;
    auto our_lambda = [](int a){return a*a;};
    x = our_lambda(x);

    // Теперь поговорим о захвате значений
    // Лямбда выражение может иметь возможность обратиться к внешним переменным
    // (из области видимости, где она создавалась) 
    // Т.е. к локальным переменные функции, из которой она вызывается. 
    // Для этого нужно вписать переменную в [] 
    x = 0;
    auto adder = [&x](int element){x += element;};
    for(int element: sorted_vec)
    {
        adder(element);
    }

    auto increaser = [x](int& element){element += x;};
    for(int& element: sorted_vec)
    {
        increaser(element);
    }
    // Есть возможность захватить все перменные по ссылке или значению: [&] или [=], а также все кроме каких-то:
    // [&, x] -- тут все захватывается по ссылке, а х -- по значению

    // А это что за покемон?
    std::sort(sorted_vec.begin(), sorted_vec.end(), 
        [](int left, int right){return left*left < right*right;});

    // НАПОМИНАЮ! Можно применять алгоритмы к ЛЮБОЙ подпоследовательности с помощью итераторов
    std::sort(sorted_vec.begin() + 3, sorted_vec.end() - 3, 
        [](int left, int right){return left > right;});

    std::vector<int> test_vec(10);
    // Алгоритм for_each() -- в некоторых случаях удобная замена циклу for
    // Первые два аргумента -- итераторы, ограничивающие последовательность, 
    // последний элемент -- функция от одного аргумента, которая принимает в себя элемент последовательности
    // и проводит с ним некоторые преобразования

    std::for_each(test_vec.begin(), test_vec.end(), 
        [](int& element){std::cin >> element;});

    // Если хотим менять --- значение передается по ссылке
    std::for_each(test_vec.begin(), test_vec.end(), 
        [](int& element){element *= element;});

    // Если не хотим  --- по значению/константной ссылке
    std::for_each(test_vec.begin(), test_vec.end(), 
        [](int element){std::cout << element << " ";});
    
    std::cout << std::endl;

    // Если хотим не менять наш исходный вектор, 
    // а записывать результат в другой, то используем transform()

    std::vector<int> destination;
    std::transform(test_vec.begin(), test_vec.end(), back_inserter(destination), 
        [](int element){return element*element;}); 

                                                                            // Также можно, например, поменять регистр у строки
    std::string str("Hello, stranger!");
    std::transform(str.begin(), str.end(), str.begin(), 
        [](char c){return toupper(c);}); 


    // Для удаления элементов из контейнера 
    // нужно воспользоваться идиомой erase-remove
    // т.е. ВНЕЗАПНО для удаления недостаточно одной функции
    std::vector to_remove = {1, 2, 3, -1, 23, 15, 1, -21};
    auto remove_output = std::remove(to_remove.begin(), to_remove.end(), 1);
    to_remove.erase(remove_output, to_remove.end());
    // Обычно это все пишут в одну строку, поэтому и идиома
    to_remove.erase(
        std::remove_if(to_remove.begin(), to_remove.end(),
                                 [](int el){return el < 0;}), 
        to_remove.end());


    // Алгоритмы поиска:
    // Алгоритм find -- возращает итератор на первый элемент равный значению, 
    // переденному функции в качестве аргумента
    // Всего три аргумента итераторы на начало и конец подпоследовательности 
    // (искать можно и не во всем контейнере (а можно и во всем))
    // и искомое значение
    auto it = std::find(test_vec.begin(), test_vec.end(), 16);

    // Алгоритм find_if -- возращает первый элемент, 
    // для которого переданное выражение вернет true 
    // (вместо искомого значение передается функциональный объект)
    // т.о. find_if(begin, end, [some_value](int element){return element == some_value}) 
    // --- это тоже самое что и find(begin, end, some_value)
    int a = 10;
    it = std::find_if(test_vec.begin(), test_vec.end(), 
        [](int element, int a){return element <= a;});
    
    //А как сделать так, чтобы найти первое число,
    // которое больше некоторой переменной 'a'????
}