/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

//! - Duplicated from CRotateTool as a way to expose the ability to draw and handle rotation to an axis.
namespace RotationDrawHelper
{
    //! Circle drawing and hit testing functionality over arbitrary axes
    class Axis
    {
    public:

        //! \param defaultColor Color used to draw the camera aligned portion of the axis.
        //! \param highlightColor Color used to draw the circle when it is in focus.
        Axis(const ColorF& defaultColor = Col_White, const ColorF& highlightColor = Col_Yellow);

        //! Sets the colors.
        //! \param defaultColor Color used to draw the camera aligned portion of the axis.
        //! \param highlightColor Color used to draw the circle when it is in focus.
        void SetColors(const ColorF& defaultColor = Col_White, const ColorF& highlightColor = Col_Yellow);

        //! Draws an axis aligned circle.
        //! \param dc DisplayContext to use for rendering.
        //! \param position World space position used as the center of the circle.
        //! \param axis The axis by which to align the circle.
        //! \param angleRadians The angle towards which the circle will be highlighted.
        //! \param radius The radius of the circle.
        //! \param highlighted If true it will draw the circle in the specified highlightColor.
        void Draw(DisplayContext& dc, const Vec3& position, const Vec3& axis, float angleRadians, float angleStepRadians, float radius, bool highlighted, float screenScale, bool drawInFront);

        //! Calculates a hit testing mesh (invisible) used for intersection testing.
        //! \param object_pos The position of the object to be selected if hit testing return true.
        //! \param hc The HitContext in which the hit object is set if an intersection is true.
        //! \param radius The radius for the axis' circle.
        //! \param angleStepRadians The angle for the step used to calculate the circle, a smaller angle results in a higher quality circle.
        //! \param axis The axis by which to align the intersection geometry.
        bool HitTest(Vec3& object_pos, HitContext& hc, float radius, float angleStepRadians, const Vec3& axis, float screenScale);

        //! Draws the generated hit testing geometry, good for diagnostics and debugging.
        //! \param dc DisplayContext to use for rendering.
        //! \param hc The HitContext that contains the view direction raycast.
        //! \param position World space position used as the center of the circle.
        //! \param radius The radius for the axis' circle.
        //! \param angleStepRadians The angle for the step used to calculate the circle, a smaller angle results in a higher quality circle.
        //! \param[out] axis The axis by which to align the intersection geometry.
        void DebugDrawHitTestSurface(DisplayContext& dc, HitContext& hc, const Vec3& position, float radius, float angleStepRadians, const Vec3& axis, float screenScale);

    protected:

        enum States
        {
            StateDefault,
            StateHighlight,
            StateCount
        };

        ColorF m_colors[StateCount];

        //! Defines the width of the generated hit testing geometry.
        float m_hitTestWidth = 0.2f;

        //! Contains the vertices that make up the ring for the intersection testing geometry.
        //! \remark Only contains the center positions, quads are generated by calculating the four vertices offset by m_hitTestWidth.
        std::vector<Vec3> m_vertices;

        //! Generates the world space geometry necessary to perform hit testing.
        //! \param hc The HitContext data.
        //! \param position The world space position around which the geometry will be centered.
        //! \param radius The radius of the ring.
        //! \param angleStepRadians The angle for the step used to calculate the circle, a smaller angle results in a higher quality circle.
        //! \param axis The axis to which the geometry will be aligned to.
        void GenerateHitTestGeometry(HitContext& hc, const Vec3& position, float radius, float angleStepRadians, const Vec3& axis, float screenScale);

        //! Performs intersection testing between a ray and both sides of a quad
        //! \param ray The ray to test (in world space)
        //! \param quad An array of four Vec3 points in world space.
        //! \param[out] contact The intersection position in world space at which the intersection occurred.
        bool IntersectRayWithQuad(const Ray& ray, Vec3 quad[4], Vec3& contact);
    };
}