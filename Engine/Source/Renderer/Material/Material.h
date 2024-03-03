#pragma once

#include "Base.h"
#include "Renderer/Color.h"
#include <string>

namespace Core
{
    class Material
    {
    public:
        /// @brief LoadMode is how the material is loaded.
        enum LoadMode
        {
            Default,
            Config,
            File
        };

        struct Configuration
        {
            std::string Name;
            std::string FileName;
            Color Color;
        };

    private:
        std::string name;
        std::string filename;
        Color color;
        LoadMode mode;

    public:
        Material();
        ~Material();

        void Load(Configuration *config);
        void Use();

        inline void SetColor(const Color &_color) { color = _color; }
        inline Color *GetColor() { return &color; };

        inline void SetName(const std::string &_name) { name = _name; }
        inline std::string GetName() { return name; };

        inline std::string GetFileName() { return filename; };

        // Do not call
        inline void SetLoadMode(LoadMode _mode) { mode = _mode; }

        // Do not call
        inline LoadMode GetLoadMode() { return mode; };
    };

}