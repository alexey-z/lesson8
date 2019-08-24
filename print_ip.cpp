#include <iostream>
#include <vector>
#include <list>

template<typename T>
struct is_vector {
	using type = T;
	constexpr static bool value = false;
};
template<typename T>
struct is_vector<std::vector<T>> {
	using type = std::vector<T>;
	constexpr static bool value = true;
};

template<typename T>
struct is_list {
	using type = T;
	constexpr static bool value = false;
};
template<typename T>
struct is_list<std::list<T>> {
	using type = std::list<T>;
	constexpr static bool value = true;
};

template<typename T,
	std::enable_if_t<std::is_same_v<std::string,T>, bool> = 0>
void print_ip(T v)
{ 
	std::cout << v << std::endl;
};

template<typename T,
	std::enable_if_t<(is_vector<T>::value || is_list<T>::value), bool> = 0>
void print_ip(T v)
{ 
	for (auto i = v.begin(); i != v.end(); i++) {
		std::cout << *i;
		if (std::next(i) != v.end()) {
			std::cout << ".";
		}
	}
	std::cout << std::endl;
};

template<typename T,
	std::enable_if_t<std::is_integral_v<T>, bool> = 0>
void print_ip(T v)
{
	uint8_t* bytes = reinterpret_cast<uint8_t*>(&v);
	for (int i=sizeof(T)-1; i>=0; i--)
	{
		std::cout << unsigned(bytes[i]);
		if (i!=0)
			std::cout << ".";
	}
	std::cout << std::endl;
}

int main()
{
	print_ip(char(-1));
	print_ip(short(0));
	print_ip(int(2130706433));
	print_ip(long(8875824491850138409));
	print_ip(std::string("123123"));
	std::vector<int> vec_ips;
	for (int i=0; i<4; i++)
	{
		vec_ips.push_back(i);
	}
	print_ip(vec_ips);
	std::list<int> list_ips;
	for (int i=0; i<4; i++)
	{
		list_ips.push_back(i);
	}
	print_ip(list_ips);
}
