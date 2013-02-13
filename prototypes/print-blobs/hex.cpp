#include <atom/blob.h>
#include <iostream>
#include <sstream>
#include <stdio.h>

std::string getHexadecimalString(atom::Blob &blob, size_t max_length=1000, bool use_space=true, size_t columns=24, bool use_columns=true)
{
    unsigned char *value = (unsigned char *) blob.get();
    std::ostringstream os;
    //os << "0x";
    for (size_t i = 0; i < blob.getSize(); i++)
    {
        if (i >= max_length)
        {
            os << "...";
            break;
        }
        if (value[i] <= 0xf)
        {
            os << "0";
            char buf[2] = "0";
            snprintf(buf, 2, "%x", value[i]);
            os << buf;
        }
        else
        {
            char buf[3] = "00";
            snprintf(buf, 3, "%x", value[i]);
            os << buf;
        }
        if (use_space)
            os << " ";
        if (use_columns)
        {
            if ((i % columns) == 0 && i != 0)
                os << std::endl;
        }
    }
    return os.str();
}

std::string getString(atom::Blob &blob, size_t max_length=1000)
{
    char *value = blob.get();
    std::ostringstream os;
    for (size_t i = 0; i < blob.getSize(); i++)
    {
        if (i >= max_length)
        {
            os << "...";
            break;
        }
        if (value[i] == 0)
            break;
        os << value[i];
    }
    return os.str();
}

int main(int argc, char *argv[])
{
    atom::Blob blob;
    blob.append(0xdb);
    blob.append(' ');
    blob.append("hello", 6);
    std::cout << "string: " << getString(blob, 100) << std::endl;
    std::cout << "hex   : " << getHexadecimalString(blob, 100) << std::endl;
    static const char * const more = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi mollis eros nec nunc tincidunt rutrum. Aliquam sed mauris turpis, sed consequat dolor. Nulla tincidunt odio a enim aliquet tristique. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eros est, hendrerit et sodales non, egestas in ligula. Pellentesque eleifend auctor purus at euismod. Fusce eu mi velit, at tincidunt nibh.";
    blob.clear();
    std::string moreString = std::string(more);
    blob.append(moreString.c_str(), moreString.size() + 1);
    std::cout << "string: " << getString(blob, 100) << std::endl;
    std::cout << "hex   : " << getHexadecimalString(blob, 100) << std::endl;
    return 0;
}

