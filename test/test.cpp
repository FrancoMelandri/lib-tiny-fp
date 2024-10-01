
#include "Option.h"
#include <iostream>

using namespace TinyFp;

int main(int argc, char* argv[])
{
    auto option = TinyFp::Option<int>::None();
    cout << "sample: " << option->IsSome() << endl;
}