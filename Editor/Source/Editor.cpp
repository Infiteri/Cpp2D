#include "Core.h"
#include "Core/EntryPoint.h"

namespace Core
{
    class Editor : public Application
    {
    public:
        Editor(){};
        ~Editor(){};

        void OnUpdate(){};
    };

    Application *CreateApplication()
    {
        return new Editor();
    };
}
