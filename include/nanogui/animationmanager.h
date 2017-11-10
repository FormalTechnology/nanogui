/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <vector>

#include <nanogui/widget.h>
#include <nanogui/animator.h>
#include <nanogui/timer.h>

NAMESPACE_BEGIN(nanogui)

class NANOGUI_EXPORT AnimationManager
{

public:

    static AnimationManager& Instance();

    static void addAnimator(const AnimatorInt& animator);
    static void deleteAnimator();

    static void startAnimation();
    static void stopAnimation();

private:

    std::vector<AnimatorInt> mAnimatorList;

    Timer mTimer;

    void updateAnimators();

    AnimationManager(){}
    AnimationManager(const AnimationManager& root);
    AnimationManager& operator = (const AnimationManager&);
};

NAMESPACE_END(nanogui)
