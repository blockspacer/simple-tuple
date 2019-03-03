#pragma once

#ifndef TUPLE_CLASS_DECLARATION_
#define TUPLE_CLASS_DECLARATION_

// declaration
template<typename ... Types>  
class Tuple;


// recursive
template<typename Head, typename ... Tail>
class Tuple <Head, Tail...>
{
private:
	Head head;
	Tuple<Tail...> tail;
public:
	Tuple() {}

	Tuple(Head const& head, Tuple<Tail...> const& tail)
		: head(head), tail(tail) {}

	Tuple(Head const& head, Tail const& ... tail)
		: head(head), tail(tail...) {}

	template<typename VHead, typename ... VTail,   // for arguments list
		typename = typename std::enable_if<sizeof...(VTail) == sizeof...(Tail)>::type>
	Tuple(VHead&& vhead, VTail&&... vtail)
		: head(std::forward<VHead>(vhead)), tail(std::forward<VTail>(vtail)...) {}


	template<typename VHead, typename ... VTail,     // copy
		typename = typename std::enable_if<sizeof...(VTail) == sizeof...(Tail)>::type>
	Tuple(Tuple<VHead, VTail...> const& other)
		: head(other.getHead()), tail(other.getTail()) {}



	const Head& getHead() const
	{
		return head;
	}

	const Tuple<Tail...>& getTail() const
	{
		return tail;
	}

	Head& getHead()
	{
		return head;
	}

	Tuple<Tail...>& getTail()
	{
		return tail;
	}

};

// base case
template<>  
class Tuple<>
{ };


#endif

// ---------------------------- get function -------------------------------

template<unsigned N>
struct TupleGet       // recursive utility
{
	template<typename Head, typename ... Tail>
	static auto apply(Tuple<Head, Tail...> const& t)
	{
		static_assert(sizeof...(Tail) != 0, "Incorrect index for get function");
		return TupleGet<N - 1>::apply(t.getTail());
	}

};

template<>
struct TupleGet<0>   // base case
{
	template<typename Head, typename ... Tail>
	static Head const& apply(Tuple<Head, Tail...> const& t)
	{
		return t.getHead();
	}
};

template<unsigned N, typename ... Types>
auto get(Tuple<Types...> const& t)       // get tuple
{ 
	return TupleGet<N>::apply(t);
}

// ---------------------------- make tuple ------------------------------

template<typename ... Types>
auto make_tuple(Types&& ... elems)
{
	return Tuple<std::decay_t<Types>...>(std::forward<Types>(elems)...);
}

// ---------------------------- operator == ------------------------------
bool operator == (Tuple<> const&, Tuple<> const&)  // base case of operator ==
{
	return true;
}

template<typename Head1, typename ... Tail1, typename Head2, typename ... Tail2,
	typename = typename std::enable_if<sizeof...(Tail1) == sizeof...(Tail2)>::type>
bool operator == (Tuple<Head1, Tail1...> const& lhs, Tuple<Head2, Tail2...> const& rhs)
{
	return ((lhs.getHead() == rhs.getHead()) &&
		(lhs.getTail() == rhs.getTail()));
}

// ----------------------------- print tuple --------------------------------

void printTuple(std::ostream& strm, Tuple<> const&, bool isFirst = true)  // empty tuple
{
	strm << ")";
}

template<typename Head, typename ... Tail>
void printTuple(std::ostream& strm, Tuple<Head, Tail...> const& t, bool isFirst = true)   // utility recursive function
{
	strm << (isFirst ? "(" : ", ");
	strm << t.getHead();
	printTuple(strm, t.getTail(), false);
}

template<typename Head, typename ... Tail>
std::ostream& operator << (std::ostream& strm, Tuple<Head, Tail...> const& t)    // operator <<
{
	printTuple(strm, t);
	return strm;
}

// -------------------------------------------------------------------------------