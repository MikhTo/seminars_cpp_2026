#include <iostream>
#include <string>
#include <vector>


void print_vec(const std::vector<std::string>& to_print)
{
    for(const std::string& str: to_print)
        std::cout << str << " ";
    std::cout << '\n';
}


// Оказывается можно объявлять функции с одинаковыми именами,
// но разными сигнатурами. Это назвается перегрузкой функции
void print_vec(const std::vector <int>& to_print)
{
    for(int el: to_print)
        std::cout << el << " ";
    std::cout << '\n';
}


//Настоящая сила -- это перегрузка операторов
std::ostream& operator<<(std::ostream& os, const std::vector<int>& to_print)
{
    for(const auto& el: to_print)
        os << el << " ";
    os << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& to_print)
{
    for(const auto& el: to_print)
        os << el << " ";
    os << '\n';
    return os;
}

std::vector<int> operator+(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    
    std::vector<int> res;
    res.resize(lhs.size());
    for(int i = 0; i < lhs.size(); i++)
        res[i] = lhs[i] + rhs[i];
    return res;
}

int main()
{
    // На прошлом занятии познакомились с со строками std::string
    // Вспомним былое

    std::string some_text = std::string("Press ") + std::string(3, 'f') 
    + " to pay respect";
    
    std::cout << "Получившаяся строка: " << some_text << std::endl;
    std::cout << "Где respect? А вот: " << some_text.find("respect") << std::endl;

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

    vect_str.at(9) = "last_one_element"; // []

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

    std::vector<std::string> vect_str_2(3, "not printed");
    //В С++ цикл for может перебрать все элементы контейнера без использования индексов    
    for(std::string str: vect_str_2)
    {
        std::cout << str << ' ';
        str = "already printed"; // А внесутся ли изменения?
    }
    std::cout << '\n';

    // Не особо
    // Для этого можно воспользоваться ссылками
    // Можно сказать, что ссылка -- это создание перменной с памятью, которая уже принадлежит другой переменной
    // Таки образом, меняя данные в ссылке изменяется и исходная перменная (обратное утверждение тоже верно)
    // Ссылки были введены, как замена указателей (для некотрых целей), которая не страдает их "проблемами":
    // обращение к неинициализированной памяти, ошибки при работе с арфиметикой указателей и т.д. 
    // Давайте создадим ссылку:
    int a = 10;
    int& b = a; //тип_& имя_переменной

    // Нельзя сделать так: int&b; или int&b = 1;
    // Ссылка при создании обязательно инициализируется каким-то объектом, хранящимся для в памяти
    // т.н. lvalue


    // Назрел вопрос
    b *= 2;
    std::cout << "Адрес а: " << &a << ", адрес b: " << &b << std::endl;

    
    // Возвращаемся к нашему циклу:

    for(std::string& str : vect_str_2)
    {
        str = "already printed";
    }

    // Ссылки также используются для передачи больших объектов в функцию,
    // чтобы избежать копирования
    // При этом если передаваемый объект менять не планируется, 
    // то он передается в функцию с модификатором const 
    print_vec(vect_str_2);


    // Теперь хочу распечатать вектор int'ов
    std::vector<int> vect_int {1,2,4,5,5,6,6};

    print_vec(vect_int);

    // Можно перегрузить оператор вывода (и, на самом деле, все остальные)
    std::cout << vect_str;

    //можно перегрузить оператор +
    std::vector<int> v {1,1,1};
    std::vector<int> l {1,1,1};
    std::vector<int> n = v + l;
    std::cout << n;

    
    return 0;
}