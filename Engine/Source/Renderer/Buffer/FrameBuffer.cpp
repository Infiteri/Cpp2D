#include "FrameBuffer.h"
#include "Core/Logger.h"
#include <glad/glad.h>

namespace Core
{

    FrameBuffer::Configuration::Configuration(const FrameBuffer::Configuration &other)
    {
        for (int i = 0; i < other.PassConfiguration.size(); i++)
            this->PassConfiguration.push_back(other.PassConfiguration[i]);

        Width = other.Width;
        Height = other.Height;
    }

    FrameBuffer::Configuration::~Configuration()
    {
        PassConfiguration.clear();
    }

    void FrameBuffer::Configuration::From(Configuration *other)
    {
        for (int i = 0; i < other->PassConfiguration.size(); i++)
            this->PassConfiguration.push_back(other->PassConfiguration[i]);

        Width = other->Width;
        Height = other->Height;
    }

    FrameBuffer::PassConfiguration::PassConfiguration(const PassConfiguration &other)
    {
        this->Id = other.Id;
        this->Index = other.Index;
        this->ClearingMode = other.ClearingMode;
    }

    FrameBuffer::FrameBuffer(FrameBuffer::Configuration *config)
    {
        state.From(config);

        Create();
    }

    FrameBuffer::~FrameBuffer()
    {
        Destroy();
        state.PassConfiguration.clear();
    }

    void FrameBuffer::Create()
    {
        if (id != 0)
        {
            glDeleteFramebuffers(1, &id);
            id = 0;
        }

        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        for (int i = 0; i < state.PassConfiguration.size(); i++)
        {
            auto pass = &state.PassConfiguration[i];

            if (pass->ClearingMode == Depth)
            {
                glGenRenderbuffers(1, &pass->Id);
                glBindRenderbuffer(GL_RENDERBUFFER, pass->Id);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, state.Width, state.Height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pass->Id);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pass->Id);

                pass->Index = i;
            }
            else
            {
                glGenTextures(1, &pass->Id);
                glBindTexture(GL_TEXTURE_2D, pass->Id);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, state.Width, state.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glBindTexture(GL_TEXTURE_2D, 0);

                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, pass->Id, 0);
                pass->Index = i;
            }
        }
    }

    void FrameBuffer::Destroy()
    {
        for (int i = 0; i < state.PassConfiguration.size(); i++)
        {
            auto pass = &state.PassConfiguration[i];

            if (pass->ClearingMode == Depth)
                glDeleteRenderbuffers(1, &pass->Id);
            else
                glDeleteTextures(1, &pass->Id);
        }
    }

    void FrameBuffer::Resize(int Width, int Height)
    {
        Destroy();

        state.Width = Width;
        state.Height = Height;

        Create();
    }

    void FrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void FrameBuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    FrameBuffer::PassConfiguration *FrameBuffer::GetRenderPass(int index)
    {
        if (state.PassConfiguration.size() < index)
        {

            CE_LOG("CE_RENDER", Error, "FrameBuffer::GetRenderPass: Index %i outside of bounds.", index);
            return nullptr;
        }
        else
            return &state.PassConfiguration[index];
    }
}