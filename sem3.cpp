#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <list>
#include <fstream>

int main()
{
    
    // Для работы с файловым потоком создаем связанный с ним объект типа std::ifstream
    // Для открытия передаем в качестве аргументов путь до файла и режим открытия
    std::ifstream ifile("some_file.txt", std::ios::in);

    //Считать же информацию можно несколькими способами:
    if(ifile.is_open()) // Проверяем, что файл открыт
    {
        //1. До первого разделителя:
        std::string str_ff1;
        ifile >> str_ff1;

        //2. Посимвольно:
        char c;
        ifile.get(c);

        //3. И до перевода строки
        std::string line;
        getline(ifile, line);
    }
    

    //Запись в файл устроена схожим образом:
    std::cout << "Введите что-нибудь для записи" << std::endl;
    
    std::string line; //Вопрос: зачем создавать line, она же уже создавалась?
    std::cin >> line;
    std::ofstream ofile("new_file.txt", std::ios::out);
    if (ofile.is_open())
    {
        ofile << line << "\n";
    }
    ofile.close();
    //А так происходит дозапись:
    std::fstream file("some_file.txt", std::ios::app);
    file << "\nAnd we dream of grass, grass at home\nOf green, green grass";
    file.close();


    // Сегодня обсудим различные контейнеры из стандартной библиотеки
    // Считаем, что с std::vector вы уже знакомы
    
    // list - реализация двусвязного списка
    // В двухсвязном списке каждый элемент имеет знает (имеет указатели) на предыдущий и следующий за ним элемент
    std::list<std::string> lst{"one", "two", "three"};
    lst.push_back("last_element");
    lst.push_front("first_element");
    for(const auto& str: lst)
        std::cout << str << std::endl;

    lst.pop_back();
    lst.pop_front();

    // Множество -- set -- набор уникальных однотипных элементов
    // Вставка, удаление и поиск имеет сложность O(log(N)), т.к. значения упорядочены
    // Для сравнения, у вектора поиск имеет сложность O(N), а обращение по индексу O(1)  
    std::set<int> our_set{5, 5, 4, 3, 2, 1};
    // Значения элементов НЕЛЬЗЯ менять, только удалять/добавлять новые элементы 

    our_set.insert(6);
    our_set.insert(1);
    our_set.erase(4);
    // также можно перебрать все элементы в цикле
    std::cout << "Все элементы set: ";
    for(int el: our_set)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    // нельзя обратиться по индексу к конкретному элементу
    // т.е. our_set[1] не скомилируется

    // std::map -- принцип работы, как у питоновского словаря
    std::map<std::string, int> our_map{{"one", 1}, {"two", 2}, {"three", 3}};

    // Хранит набор пар: ключ-значение, ключи должны быть уникальные
    // каждая пара хранится в объекте типа типе pair<type, type>
    // pair -- это структура c двумя полями: 
    // first -- для ключа, second -- для значения

    our_map["one"] = 2; // изменит значение на 2
    our_map["four"] = 0; // если ключа нет -- создает его
    our_map["four"] += 4; // добавит к four 4
    our_map["five"] += 5; // создаст "five" и инициализирует 5, а если бы ключ был, то прибавил бы 5
    // our_map.at("+100500"); -- ошибка!
    // т.е. метод .at работает только с существующими ключами
    
    // Можно перебрать в цикле:
    std::cout << "Все элементы map: ";
    for(std::pair<std::string, int> pair: our_map)
        std::cout << pair.first<< " and " << pair.second<< std::endl;
    std::cout << std::endl;

    // Для map, как и для остальных контейнеров, реализованы операции сравнения (==, >, <  и т.д.)

    // Проверим: скопируем наш словарь (это еще одно название для map)
    std::map another_map = our_map;
    std::cout << "Результат our_map == another_map: " << (our_map == another_map) << std::endl;
    // Давайте добавим в another_map еще одно значение
    another_map["six"] = 6;
    std::cout << "Результат our_map < another_map: " << (our_map < another_map) << std::endl;
    
    // Одинаковые map
    std::map<std::string, int> left_map {{"1",1}, {"2", 2}, {"3",3}};
    auto right_map = left_map;

    std::cout << "Левая больше правой: " << (left_map > right_map) << std::endl;

    // меняем: увеличим значение у левой:
    left_map["2"] = 3;
    std::cout << "Левая больше правой: " << (left_map > right_map) << std::endl;

    // сделаем тоже самое для правой и добавим новое значение:
    right_map["2"] = 3;
    right_map["4"] = 4;
    std::cout << "Левая больше правой: " << (left_map > right_map) << std::endl;

    // добавим ключ, который будет больше
    left_map["5"] = -4;
    std::cout << "Левая больше правой: " << (left_map > right_map) << std::endl;

    // на практике чаще приходится сравнивать на равенство,
    // или писать свое кастомное сравнение.

    // Оказывается, что при создании set (и map, к слову, тоже)
    // Данные хранятся в отсортированном виде
    std::set<int> new_set={1, 100, -1, 23, 12, 0, 100, 1};
    // Это связано с внутрянним устройством set (про внутряннюю структуру контейнеров поговорим подробно на сл. паре)
    
    // Если хочется этого избежать, то можно воспользоваться unordered_set
    std::unordered_set <int> un_set = {1, 100, -1, 23, 12, 0, 100, 1};
    
    // точно также отличаются map и unordered map
    // но главное отличие в сложности поиска и доступа по ключу!

    return 0;
}