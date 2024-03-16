#pragma once

#include "Base.h"
#include "Math/Matrix4.h"
#include "Math/Transform.h"

namespace Core
{
    class CE_API Camera
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

        enum class TransformationType
        {
            Transform,
            Matrix
        };

    protected:
        Matrix4 projection;
        Matrix4 view;
        OriginPoint originPoint;
        TransformationType transformType;
        Transform transform;
        Matrix4 matrixTransform;
        Type type;
        float zoom;

    public:
        Camera(){};
        ~Camera(){};

        virtual void CalculateProjection();
        void CalculateView();

        inline Matrix4 *GetProjection() { return &projection; };
        inline Matrix4 *GetView() { return &view; };
        inline Matrix4 GetInvertedView() { return Matrix4::Invert(view); };
        inline Transform *GetTransform() { return &transform; };

        /// @brief Called if the transform type is set to Matrix. Otherwise no effect is taken.
        /// @param matrix A pointer to a Matrix4 class.
        inline void SetTransformMatrix(Matrix4 *matrix) { matrixTransform.From(matrix); };

        void SetOriginPoint(OriginPoint o);
        inline OriginPoint GetOriginPoint() { return originPoint; };

        void SetType(Type o);
        inline Type GetType() { return type; };

        void SetTransformationType(TransformationType o);
        inline TransformationType GetTransformationType() { return transformType; };

        inline float GetZoom() { return zoom; }
        void SetZoom(float z);
        void AddZoom(float z);

        template <typename T>
        T *As() { return (T *)this; };
    };
}