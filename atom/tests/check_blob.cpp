#include "atom/blob.h"
#include <iostream>
#include <string>

static const bool VERBOSE = false;

void debugText(const atom::Byte *text, size_t size)
{
    std::cout << "appending : ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << ( (int) text[i] ) << " ";
    }
    std::cout << std::endl;
}

bool check_blob()
{
    atom::Blob *blob = new atom::Blob;

    atom::Byte foo[] = { 'f', 'o', 'o' };
    atom::Byte bar[] = { 'b', 'a', 'r' };
    atom::Byte egg[] = { 'e', 'g', 'g' };
    atom::Byte spam[] = { 's', 'p', 'a', 'm' };

    if (VERBOSE)
    {
        blob->debugPrint();
        debugText(foo, sizeof(foo));
    }

    blob->append(foo, sizeof(foo));
    if (VERBOSE)
    {
        blob->debugPrint();
        debugText(bar, sizeof(bar));
    }

    blob->append(bar, sizeof(bar));
    if (VERBOSE)
    {
        blob->debugPrint();
        debugText(egg, sizeof(egg));
    }

    blob->append(egg, sizeof(egg));
    blob->append('x');
    if (VERBOSE)
    {
        blob->debugPrint();
        debugText(spam, sizeof(spam));
    }

    blob->append(spam, sizeof(spam));
    if (VERBOSE)
    {
        blob->debugPrint();
        std::cout << "text: " << blob->get() << std::endl;
    }
    delete blob;
    return true;
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    if (! check_blob())
        return 1;
    return 0;
}

