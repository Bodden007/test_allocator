#include <iostream>
#include <map>
#include <memory>
#include <memory_resource>

// Создание аллокатора
template <typename T>
struct MyAllocator {
	using value_type = T;

	// Аллокатор дефолтный
	MyAllocator() = default;

	//Конструктор копирования аллокатора
	template <typename U>
	MyAllocator(const MyAllocator<U>&) {}

	//Выделение пула памяти
	void* operator new[](std::size_t n)
	{
		return ::operator new[](10);
	}
	
	// ??? превышение лимита  должнотвыбрасываться bad_alloc. НЕ РАБОТАЕТ!!!!
	T* allocate(std::size_t n)
	{
		if (n > 10)
			throw std::bad_alloc();
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	//Деструктор аллокатора
	void deallocate(T* p, std::size_t) {
		operator delete(p);
	}
};

//объявление функции factorial
template <typename Allocator>
void factorial(std::map <int, int, std::less<int>, Allocator >& factor);


int main()
{	
	std::map <int, int, std::less<int>, MyAllocator<std::pair <const int, int>> > factor_alloc;

	factorial(factor_alloc);

	for (const auto f : factor_alloc)
	{
		std::cout << f.first << " " << f.second << std::endl;
	}
}

//определение функции factorial 
// Надо ли здесь добовлять выделение памяти???
template<typename Allocator>
void factorial(std::map<int, int, std::less<int>, Allocator>& factor)
{
	for (int i = 0; i < 12; i++)
	{
		factor[i] = 1;

		if (i == 0)
		{
			factor[i] = 1;
		}
		else
		{
			for (auto p = 1; p <= i; p++)
			{
				factor[i] = factor[i] * p;
			}
		}
	}
}
