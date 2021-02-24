#include <iostream>
#include <iomanip>      // std::setw
#include "str_utils.h"
#ifdef __cplusplus
extern "C"
{
#endif
    //----------begin---------
    using namespace std;

    int compare_str(unsigned char *unsigned_str, char *str)
    {
        return strncmp(reinterpret_cast<const char *>(unsigned_str), str, strlen(str));
    }

    /**
     * Why this function so weird?
     * If I use "cout << data << endl;" to print string, it printing empty beacause decrypted data does not set end char.
    */
    void print_str(unsigned char *data, size_t len)
    {
        for (auto i(0U); i < len; i++)
        {
            cout << data[i];
        }
        cout << endl;
    }

    void print_chars_in_hex(unsigned char *data, size_t len)
    {
        if (len == 0)
            throw std::exception(); //throw dependencies "-fexceptions"

        for (auto i(0U); i < len; ++i)
        {
            cout << (i == 0 ? "0x" : ",0x") << setw(2) << setfill('0') << hex << (unsigned int)data[i];
        }
        cout << endl;
    }

//----------end---------
#ifdef __cplusplus
}
#endif