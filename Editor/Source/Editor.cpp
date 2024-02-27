#include "Core.h"
#include "Core/EntryPoint.h"

namespace Core
{
    class Editor : public Application
    {
    public:
        Editor(){};
        ~Editor(){};

        void OnUpdate()
        {
            if (Input::GetKey(Keys::A))
            {
                CE_INFO("AAA");
            }

            if (Input::GetButton(Buttons::Left))
            {
                CE_INFO("Bu");
            }
        };
    };

    Application *CreateApplication()
    {
        return new Editor();
    };
}
