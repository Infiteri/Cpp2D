#pragma once

#include "Base.h"
#include "Math/Matrix4.h"

namespace Core
{
    class Camera
    {
    public:
        enum OriginPoint
        {
            Left,
            Middle,
        };

        enum Type
        {
            Orthographic
        };

    protected:
        Matrix4 projection;
        Matrix4 view;
        OriginPoint originPoint;
        Type type;

    public:
        Camera(){};
        ~Camera(){};

        virtual void CalculateProjection();
        void CalculateView();

        inline Matrix4 *GetProjection() { return &projection; };
        inline Matrix4 *GetView() { return &view; };
        inline Matrix4 GetInvertedView() { return Matrix4::Invert(view); };

        void SetOriginPoint(OriginPoint o);
        inline OriginPoint GetOriginPoint() { return originPoint; };

        void SetType(Type o);
        inline Type GetType() { return type; };

        template <typename T>
        T *As() { return (T *)this; };
    };
}