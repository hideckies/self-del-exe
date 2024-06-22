#include "utils.hpp"

int main(void)
{
    printf("I'll be deleted after 3 seconds.\n");

    Sleep(3000);

    Utils::SelfDelete();
}