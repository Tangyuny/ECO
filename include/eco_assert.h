#include <exception>
#include <sstream>

class EnsureException:
    public std::exception
{
public:
    EnsureException(const char *exp, const char *file, int line)
    {
        std::ostringstream so;
        so << "ensure failed : " << exp << '\n';
        so << file << '(' << line << ')' << '\n';
        m_what = so.str();
    }
    ~EnsureException() throw (){}

    // template<typename T>
    // EnsureException& operator << (const std::pair<const char *, T>& p)
    // {
    //     std::ostringstream so;
    //     so << '\t' << p.first << " : " << p.second << '\n';
    //     m_what += so.str();
    //     return *this;
    // }
    // EnsureException& operator << (int){ return *this; }

    const char *what() const throw ()
    { 
        return m_what.c_str();
    }
private:
    mutable std::string m_what;
};

// static int A = 0, B = 0;
// #define AB(a, N) std::make_pair(#a, a) << N
// #define A(a) AB(a, B)
// #define B(a) AB(a, A)
#define ENSURE(b) if (b); else throw EnsureException(#b, __FILE__, __LINE__)
