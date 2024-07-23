Реалізувати власний спрощений варіант std::shared_ptr.

Потрібно реалізуват методи:

    конструктор, який приймає сирий вказівник T*
    деструктор
    копіюючий конструктор
    T& operator=( const T& r )
    T& operator*() const
    T* operator->() const
    long use_count() const
    T* get() const noexcept
    explicit operator bool() const noexcept
