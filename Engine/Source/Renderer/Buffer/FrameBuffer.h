#pragma once

#include "Base.h"
#include <vector>

namespace Core
{
    class FrameBuffer
    {
    public:
        enum ClearingMode
        {
            Rgba8,
            Depth
        };

        struct PassConfiguration
        {
            ClearingMode ClearingMode;
            CeU32 Index;
            CeU32 Id;

            PassConfiguration() { ClearingMode = Rgba8; };
            PassConfiguration(FrameBuffer::ClearingMode mode) { ClearingMode = mode; };
            PassConfiguration(const PassConfiguration &other);
        };

        struct Configuration
        {
            std::vector<PassConfiguration> PassConfiguration;

            int Width = 1024;
            int Height = 576;

            Configuration(){};
            Configuration(const Configuration &other);

            void From(Configuration* other);
        };

    private:
        CeU32 id;
        Configuration state;

        void Destroy();

    public:
        FrameBuffer( Configuration *config);
        ~FrameBuffer();

        void Create();
        void Resize(int Width, int Height);
        void Bind();
        void Unbind();

        PassConfiguration *GetRenderPass(int index);

        inline CeU32 GetID() { return id; };
    };
}