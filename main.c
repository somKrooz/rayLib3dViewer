#include "engine.h"
#include "stdlib.h"  

int main() {

    struct Enginedata engineData;
    struct LoadedData loadedData;

    InitEngine(&engineData);
    GameLoop(&engineData,&loadedData);

    CloseWindow();
    return 0;
}
