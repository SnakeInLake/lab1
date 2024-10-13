
Этот проект представляет собой реализацию различных абстрактных структур данных с базовым набором операций и удобным интерфейсом командной строки для взаимодействия с ними.


Реализованные структуры данных

Массив (Array): Реализация динамического массива с операциями добавления, получения, удаления, замены элементов и определения размера.

Список (List): Односвязный и двусвязный списки с операциями добавления, удаления, поиска и получения элементов.

Очередь (Queue): Реализация очереди (FIFO) с операциями добавления (enqueue), удаления (dequeue) и чтения (read).

Стек (Stack): Реализация стека (LIFO) с операциями добавления (push), удаления (pop) и чтения (read).

Хеш-таблица (Hash Table): Хеш-таблица с обработкой коллизий методом цепочек, операциями добавления, получения и удаления элементов.

АВЛ-дерево (AVL Tree): Сбалансированное двоичное дерево поиска с операциями добавления, поиска, удаления и обхода.


Использование
Для взаимодействия со структурами данных используется интерфейс командной строки.

./program.exe <вид_структуры> --file <имя_файла> --query <запрос>


Аргументы:
--file <имя_файла>: Путь к файлу для хранения данных (опционально. Если не указан, данные хранятся в памяти).

--query <запрос>:  Запрос к структуре данных, состоящий из команды и параметров.


#Примеры запросов:

./program.exe array --file data.txt --query 'MPUSH array item'   Добавляет "item" в массив "array"

./program.exe queue --file data.txt --query 'QPOP myqueue'        Удаляет элемент из очереди "myqueue"

./program.exe hash --file data.txt --query 'HSET myhash key value'  Добавляет пару "key: value" в хеш-таблицу "myhash"
