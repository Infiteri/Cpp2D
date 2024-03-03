#include "Core.h"
#include "Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Core
{
    class Editor : public Application
    {
    public:
        Editor(){};
        ~Editor(){};

        void OnInit()
        {
            LayerStack::PushLayer(new EditorLayer());
        };
    };

    Application *CreateApplication(Engine::Configuration *config)
    {
        config->WindowConfig.Mode = Window::Windowed;

        return new Editor();
    };
}
