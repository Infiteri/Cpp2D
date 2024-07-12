#include "CollisionDetector.h"
#include "Math/Vectors.h"
#include "Math/Math.h"

namespace Core
{
    static inline float TransformToAxis(AABBCollider *box, Vector3 axis)
    {
        return box->Size.x * Math::Abs(axis.Dot(box->GetAxis(0))) +
               box->Size.y * Math::Abs(axis.Dot(box->GetAxis(1))) +
               1 * Math::Abs(axis.Dot(box->GetAxis(2))); // TODO: Presume the box depth, NOTE: Required
    }

    static inline bool overlapOnAxis(
        AABBCollider *one,
        AABBCollider *two,
        const Vector3 &axis,
        const Vector3 &toCentre)
    {
        // Project the half-size of one onto axis
        float oneProject = TransformToAxis(one, axis);
        float twoProject = TransformToAxis(two, axis);

        // Project this onto the axis
        float distance = Math::Abs(toCentre.Dot(axis));

        // Check for overlap
        return (distance < oneProject + twoProject);
    }

#define CE_TEST_OVERLAP(axis) overlapOnAxis(one, two, (axis), toCentre)

    bool CollisionDetector::AABBvsAABB(AABBCollider *one, AABBCollider *two)
    {
        // Find the vector between the two centres
        Vector3 toCentre = two->GetAxis(3) - one->GetAxis(3);

        return (
            CE_TEST_OVERLAP(one->GetAxis(0)) &&
            CE_TEST_OVERLAP(one->GetAxis(1)) &&
            CE_TEST_OVERLAP(one->GetAxis(2)) &&
            // And on two's
            CE_TEST_OVERLAP(two->GetAxis(0)) &&
            CE_TEST_OVERLAP(two->GetAxis(1)) &&
            CE_TEST_OVERLAP(two->GetAxis(2)));
    }
}