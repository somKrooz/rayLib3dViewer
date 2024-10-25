#include <engine.h>
#include <loader.h>

int main(void)
{
    struct Loader loader;
    struct Renderer renderer;
    
    InitEngine(&renderer,&loader);
    GameLoop(&renderer , &loader);

    return 0;
}