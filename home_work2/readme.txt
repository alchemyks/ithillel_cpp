Реалізувати власний спрощений варіант std::unique_ptr
Потрібно реалізуват методи:

    конструктор, який приймає сирий вказівник T*
    деструктор
    T& operator=( const T& r )
    T& operator*() const
    T* operator->() const
    T* get() const noexcept
    explicit operator bool() const noexcept
