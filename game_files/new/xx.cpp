#include <boost/regex.hpp>
#include <iostream>
using namespace std;

int main(){
	string data = "#avs#afas#asda#asd";
	boost::regex re("#");
	boost::sregex_token_iterator i(data.begin(), data.end(), re, -1);
	boost::sregex_token_iterator j;
	vector<string> vec;
	while (i != j) {
		vec.push_back(*(i++));
	}
	cout<< vec[1];
	return 0;
}
