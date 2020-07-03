#define BOOST_TEST_MODULE test_carray

#include <boost/test/included/unit_test.hpp>

#include "CArray.h"
#include "util.h"

namespace utf = boost::unit_test;
namespace testtools = boost::test_tools;

using namespace std;


// INT TESTS
void form_rnd_nums(
	CArray<int>& _A
)
{
	int i, number;

	cout << "Test 1.1. Form the array with 20 random numbers." << endl;

	srand(time(NULL));
	for (i = 0; i < 20; i++)
	{
		number = rand() % 100;

		_A.push_back(number);
	}
}

void sort_arr(
	CArray<int>& _A
)
{
	int i, j;
	int t;

	cout << "Test 1.2. Sorting the array." << endl;

	selection_sort(_A);
}

void delete_every_sec_nums(
	CArray<int>& _A
)
{
	CArray<int> B; 

	cout << "Test 1.3. Deleting every secont item." << endl;

	B.clear();
	for (int i = 0; i < _A.size(); i++)
	{
		if (i % 2 == 1)
			B.push_back(_A[i]);
	}
	_A = B;
}

void insert_rnd_nums(
	CArray<int>& _A
)
{
	int number, pos;
	int t;

	cout << "Test 1.4. Inserting 10 random numbers to random positions" << endl;

	srand(time(NULL));

	t = 0; 
	for (size_t i = 0; i < 10; i++)
	{
		number = rand() % 100;
		pos = rand() % (10 + t); 
		_A.insert(pos, number);
		t++; 
	}
}

void clear_arr(
	CArray<int>& _A
)
{
	cout << "Test 1.5. Clear the array." << endl;
	_A.clear();

	if (_A.is_empty())
	{
		cout << "Array is empty" << endl;
	}
}



// STRING TESTS
void adding_new_words(
	CArray<string>& _A
)
{
	int len;
	string word;
	char symbol;

	cout << "Test 2.1. Adding 15 new words." << endl;
	srand(time(NULL));

	for (size_t i = 0; i < 15; i++)
	{
		len = rand() % 6 + 1;

		word = "";
		for (size_t j = 0; j < len; j++)
		{
			symbol = 'a' + rand() % ((int)'z' - (int)'a' + 1);
			word += symbol;
		}
		_A.push_back(word);
	}
}

void sorting_words(
	CArray<string>& _A
)
{
	cout << "Test 2.2. Sorting words." << endl;

	for (int i = 0; i < _A.size() - 1; i++)
	{
		for (int j = i + 1; j < _A.size(); j++)
		{
			if (strcmp(_A[i].c_str(), _A[j].c_str()) > 0)
			{
				swap(_A[i], _A[j]);
			}
		}
	}
}

void delete_word_with_smth_chars(
	CArray<string>& _A
)
{
	string word;
	CArray<string> B;
	bool is_delete;

	cout << "Test 2.3. Deleting words with characters a to e " << endl;

	for (size_t i = 0; i < _A.size(); i++)
	{
		word = _A[i];
		is_delete = false;
		for (size_t j = 0; j < word.length(); j++)
			if (('a' <= word[j]) && (word[j] <= 'e'))
			{
				is_delete = true;
				break;
			}

		
		if (!is_delete)
			B.push_back(word);
	}
	_A = B;
}

void insert_rnd_words(
	CArray<string>& _A
)
{
	int len;
	string word;
	char symbol;
	int position;

	cout << "Test 2.4. Inserting 3 new random words to random positions" << endl;

	srand(time(NULL));

	for (size_t i = 0, t = 0; i < 3; i++, t++)
	{
		position = rand() % (_A.size() + t);

		len = rand() % 6 + 1;

		word = "";

		for (size_t j = 0; j < len; j++)
		{
			symbol = 'a' + rand() % ((int)'z' - (int)'a' + 1);
			word += symbol;
		}

		_A.insert(position, word);
	}
}



// BOOST TESTS
////////////////////////////////////

BOOST_AUTO_TEST_SUITE(test_carray_int_suite)

testtools::predicate_result compare_arrays(
	CArray<int> const& arr1,
	CArray<int> const& arr2
)
{
	if (arr1.size() != arr2.size())
	{
		boost::test_tools::predicate_result res(false);

		res.message() << "Different sizes [" << arr1.size() << "!=" << arr2.size() << "]";

		return res;
	}
	return true;
}


BOOST_AUTO_TEST_CASE(test_arrays_comparison)
{
	CArray<int> arr1, arr2;
	arr1.push_back(1);
	arr2.push_back(2);

}


BOOST_AUTO_TEST_CASE(
	full_methods_int_test,
	*utf::label("Full methods Int"),
	*utf::description("This case testing all methods with int type")
)
{
	CArray<int> arr_int;
	form_rnd_nums(arr_int);
	arr_int.print();

	sort_arr(arr_int);
	arr_int.print();

	delete_every_sec_nums(arr_int);
	arr_int.print();

	insert_rnd_nums(arr_int);
	arr_int.print();

	clear_arr(arr_int);
	arr_int.print();

	cout << endl;
}

BOOST_AUTO_TEST_SUITE_END()




// STRING SUITE
BOOST_AUTO_TEST_SUITE(test_carray_str_suite)

BOOST_AUTO_TEST_CASE(
	full_methods_str_test,
	*utf::label("Full methods String"),
	*utf::description("This case testing all methods with string type")
)
{
	CArray<string> arr_str;

	adding_new_words(arr_str);
	arr_str.print();

	sorting_words(arr_str);
	arr_str.print();

	delete_word_with_smth_chars(arr_str);
	arr_str.print();

	insert_rnd_words(arr_str);
	arr_str.print();
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////