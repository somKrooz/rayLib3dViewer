#include "engine.h"
#include "stdlib.h"  

int main() {

    struct Enginedata engineData;

    InitEngine(&engineData);
    GameLoop(&engineData);

    CloseWindow();
    return 0;
}
