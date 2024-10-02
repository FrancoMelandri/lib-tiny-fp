
#include "Option.h"
#include <iostream>

using namespace TinyFp;

int main(int argc, char* argv[])
{
    auto noneOption = Option<int>::None();
    cout << "sample: " << noneOption->IsSome() << endl;
    int value = 10;
    delete noneOption;

    auto someOption = Option<int>::Some(&value);
    cout << "sample: " << someOption->IsSome() << endl;
    delete someOption;
}