// TUPLE.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include "tuple.hpp"


using namespace std;

//template<typename ... Ts>
//constexpr auto make_array(Ts&&... params) 
//	-> std::array< common_type_t<Ts...>, sizeof...(Ts)>
//{
//	return { forward<Ts>(params)... };
//}


int main()
{
	//string s = "pqwkeqwe";
	//Tuple<int, double, string> tup1 (3, 3.13, s);

	//auto tup2 = make_tuple(3, 3.13, string("pqwkeqwe"));

	//if (tup1 == tup2)
	//	cout << tup1 << endl;

	//cout << get<2>(tup1) << endl;



	system("pause");
	return 0;
}
