/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <memory>
#include <vector>

#include <nanogui/widget.h>
#include <nanogui/timer.h>

NAMESPACE_BEGIN(nanogui)

class IAnimatorBase;

class NANOGUI_EXPORT AnimationManager
{

public:

    static AnimationManager& Instance();

    static void addAnimator(const std::shared_ptr<IAnimatorBase> animator);
    static void deleteAnimator();

    static void startAnimation();
    static void stopAnimation();

    static unsigned int getTimeOut();
    static void setTimeOut(unsigned int timeOut);

private:

    std::vector<std::shared_ptr<IAnimatorBase>> mAnimatorList;

    Timer mTimer;
    unsigned int mTimeOut;

    void updateAnimators();

    AnimationManager()
    {
        mTimeOut = 0;
    }

    AnimationManager(const AnimationManager& root);
    AnimationManager& operator = (const AnimationManager&);
};

NAMESPACE_END(nanogui)
