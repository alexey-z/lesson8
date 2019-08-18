#include <iostream>
#include <vector>

template<typename T>
struct type_is {
	using type = T;
};

template<typename T>
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
};

//template<typename T>
//typename std::enable_if_t<std::is_integral_v<T>>::type
//print_ip(T v)
//{
//	std::cout << v << std::endl;
//};

template<>
void print_ip(std::string v)
{ 
	std::cout << v << std::endl;
};


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
}
