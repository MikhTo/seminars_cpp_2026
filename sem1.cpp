#include <iostream>
#include <string>
#include <vector>

#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    // Язык С++ во многом наследует синтаксис С
    // Почти любая Сишная программа может быть скомпилирована плюсовым компилятором
    // Однако С++ позволяет писать и более высокоуровневые программы
    // В декларативной, объекто-ориентированной и функциональной парадигмах
    // В нашем курсе мы будем давать С++, как язык высокого уровня

    // Для начала изучим (вспомним) основные операции
    // Переменные объявляются также как в Си
    int some_int = 1; // Теперь типизация опять статическая и есть ;
    double some_double = 1.5;
    char some_char = 'x';
    // Есть также float, complex и указатели на все это счастье

    // Ввод/вывод осуществляется при помощи cin/cout из <iostream>
    std::cout << some_int << " " << some_double << " " << some_char << std::endl;

    std::cout << "Введите int и double" <<std::endl;
    std::cin >> some_int >> some_double;

    std::cout << some_int << " " << some_double << " " << some_char << std::endl;
    // Строки в языке С представляли собой нуль-терминированный массив типа char
    // Их тоже можно использовать в С++ они называются С стайл строками
    char str_c [] = "It's C style string\n";
    const char* str = "It's literal string\n";
    std::cout << str_c << str;

    // Можно вывести в цикле:
    for(int i = 0; str_c[i] != '\0'; i++)
        std::cout << str_c[i] << std::endl;

    //Однако в стандартной библиотеке С++ есть более удобное решение для работы со строками: std::string

    std::string first, second, third(6, 't'), fourth("fourth"); // создание строки

    std::cout << "Введите 2 строки:\n";
    std::cin >> first >> second; // Можно считывать строки из стандартного потока
    
    //Можно отправлять в стандартный поток
    std::cout << "Содержание первых двух строк, полученное из консоли: " << 
        first << '\t' << second << std::endl; 

    std::cout << "Содержимое третьей и четвертой строк, инициализированных при создании: " << 
        third << '\t' << fourth << std::endl;


    // Но тут есть ньюансы:
    std::string some_text;
    std::cin >> some_text;
    std::cout << "Вот, что считалось: " << some_text << std::endl;


    // Если хотим ввод до перевода на новую строку
    std::getline(std::cin, some_text);
    std::cout << "Результат getline" << some_text << std::endl;


    //обращаться к элементам строки можно через [] или через .at()
    std::cout << "Обращаемся к элементам по индексу: " << 
        third[3] << " " << fourth.at(4) << std::endl;
    
    fourth += fourth;  // +. +=, .append() - операция конкатенации -- сложения строк
    std::cout << "Конкатенация: " << 
        fourth << " " << first + second << " " << fourth.append("the end!") << std::endl;

    //Строки можно сравнивать лексикографически
    std::cout << "Результат third > fourth: " << (third > fourth) << std::endl; 
    //доступны <, >, <=, >=, ==, !=

    third = "cat";
    fourth = "car";
    std::cout << "Результат third > fourth: " << (third > fourth) << std::endl; 

    fourth = "catapult";
    std::cout << "Результат third > fourth: " << (third > fourth) << std::endl; 

    std::string a("abcd");
    std::cout << "Новая строка, с которой будем работать: " << a << std::endl;
    std::cout << "Узнать размер можно с помощью .size() или .length(): " << a.size() << std::endl;

    std::cout <<"Однако места в памяти требуется больше, чем на строку: "<< 
        a.capacity() << std::endl; 
    //  Почему так? Чтобы можно было добавлять символ в конец без перезаписи

    a.push_back('e');
    std::cout << "Добавили \'e\' с помощью .push_back(): " << a << std::endl;
    //А убрать можно с помощью pop_back();
    a.pop_back();
    std::cout<< "А теперь убрали при помощи pop_back(): " << a << std::endl;

    //Полезный метод find() -- ищет первое вхождение
    std::string phrase("NSU is the novosibirsk State University");
    std::cout << "Новая строка для работы: " << phrase << std::endl;

    std::cout << "Позиция \"si\", найденная с помощью метода find: " << 
        phrase.find("si") << std::endl;
        
    std::cout << "Позиция второго вхождения \"si\" при передаче методу find в качестве второго аргумента индекс"
    " первого вхождения: " << phrase.find("si", phrase.find("si") + 1) << std::endl; // Второй параметр -- точка старта поиска

    // А вот так можно менять регистр (для понижения функция tolower) []
    phrase.at(phrase.find("novo")) = std::toupper(phrase[phrase.find("novo")]); 

    std::cout << "Повышаем регистр у буквы n в слове \'novosibirsk\': " << phrase << std::endl;

    /* Идет в следующий семинар
    // Также есть массивы
    int mas[] = {1, 2, 3, 4, 5}; // статический
    int* pMas = new int [5]; // Динамический. new -- вместо malloc
    for(int i = 0; i < 5; i++)
        pMas[i] = mas[i];
    
    delete [] pMas; // аналог free

    // С какими проблемами вы сталкивались при работе с массивами (особенно динамическими)?
    
    // Стандартная библиотека C++ предоставляет большой набор контейнеров, 
    // которые позволяют удобно хранить и работать с наборами однотипных данных

    // Для работы с контейнерами надо включить одноименный заголовочный файл (см. #include)

    // Познакомисмся с vector - вероятно самым популярным контейнер
    // vector - динамический массив, который сам заботиться о выделении/перевыделении/освобождении памяти

    std::vector<int> vect_i; // Пустой вектор с элементами типа int
    std::vector<std::vector<double>> vect_vect(10); // Вектор векторов с элементами типа double размером 10 

    std::vector<std::string> vect_str(10, "element"); // Вектор c элементами типа string, размером 10, каждая строка = "element"
    std::vector<float> vector_f = {1., 1.1, 1.2, 1.3, 1.4, 1.5}; // С помощью списка инициализации
    
    //Обращение к элементу также как в string: [] или .at():

    vect_str.at(9) = "last_one_element";

    //Полезные методы контейнера vector
    //Можно добавлять элементы  в конец с помощью метода pushed_back:
    vect_str.push_back("pushed_back_one");
    //Память выделяется также как в string -- с запасом

    std::cout << "Размер: " << vect_str.size() << ", емкость: " << vect_str.capacity() << std::endl;
    //можно узнать, какой максимальный размер может быть у вектора (работает с любым контейнером)
    std::cout << "Максимальный размер vector<float>: " << vector_f.max_size() << std::endl;
    //Можно изменять размер:
    vect_vect.resize(20);
    //Или удалить лишнюю память (сделать буфер равным размеру)
    vect_vect.shrink_to_fit();

    */
    return 0;
}