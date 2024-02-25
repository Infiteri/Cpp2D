#include "Core.h"

int main(int argc, char const *argv[])
{
    Core::Logger::Init();

    CE_INFO("A: %s", "b");
    CE_WARN("A: %s", "b");
    CE_WARN("A: %s", "b");
    CE_TRACE("A: %s", "b");
    CE_DEBUG("A: %s", "b");

    CE_CORE_INFO("A: %s", "b");
    CE_CORE_WARN("A: %s", "b");
    CE_CORE_WARN("A: %s", "b");
    CE_CORE_TRACE("A: %s", "b");
    CE_CORE_DEBUG("A: %s", "b");

    while (true)
    {
    }

    Core::Logger::Shutdown();

    return 0;
}
