В STL немає реалізації потокобезпечних  контейнерів. нам потрібно реалізувати самостиіційно.

Реалізуйте потокобезпечний контейнер на основі стандартного контейнера(обрати будь-який)

Контейнер повинен забезпечувати безпечний доступ до даних з кількох потоків одночасно. 
Використайте механізми синхронізації з бібліотеки стандартних шаблонів C++ (STL), такі як std::mutex або std::shared_mutex.
Приклад для вектора

Вимоги до реалізації:

    Реалізуйте наступні методи:

    void push_back(const T& value) – додає елемент до вектора.
    T get(size_t index) const – повертає елемент за заданим індексом.
    size_t size() const – повертає кількість елементів у векторі.
    void erase(size_t index) – видаляє елемент за заданим індексом.

Використайте механізми синхронізації для забезпечення потокобезпеки (наприклад, std::mutex або `std::shared_mutex`)