#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct S {

private:
    T val;
    
    public:
    explicit S(T vv = 0) : val{vv} { }   // feltöltjük

    S& operator=(const T&);

    T& get();
    
    const T& get() const;    // structúrán kívül
    

};

template<typename T>
T& S<T>::get()
{
    return val;		// privát vektorban tárolt érték előhív
}

template<typename T>
const T& S<T>::get() const
{
    return val;		// konstansal ugyanez
}

template<typename T> 
void read_val(T& v)
{
    std::cin >> v;		//beolvasunk a vektorunkba
}

template<typename T>
S<T>& S<T>::operator=(const T& s)
{
    val = s;
    return *this; 	// self-reference
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& v)		// adatok kiírása 
{
    os << "{ ";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << (i < v.size() - 1 ? ", " : " ");
    }
    os << "}\n";

    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v)  		// adatok beírása
{
    char ch = 0;
    is >> ch;
    if (ch != '{') {
        is.unget();
        return is;
    }

    for (T val; is >> val; ) {
        v.push_back(val);
        is >> ch;
        if (ch != ',') break;
    }

    return is;
}


int main()
{
    S<int> si {987654321};
    S<char> sc {'W'};
    S<double> sd {420.69};
    S<std::string> s {"Vezendi"};
    S<std::vector<int>> svi { std::vector<int>{1, 2, 3, 4, 4747, 8989}};

    std::cout << "S<int> : " << si.get() << '\n'
              << "S<char> : " << sc.get() << '\n'
              << "S<double> : " << sd.get() << '\n'
              << "S<string> : " << s.get() << '\n'
              << "S<vector<int>> : " << svi.get() << '\n';

   

    sd = 69.20;
    std::cout << "S<double> : " << sd.get() << '\n';

    std::cout << "Reads:\n";

    
    std::cout << "Vector<int>: (format: { val1, val2, val3 }) ";
    std::vector<int> vi2;
    read_val(vi2);
    S<std::vector<int>> svi2 {vi2};

    std::cout << "S<vector<int>> read: " << svi2.get() << '\n';
}
