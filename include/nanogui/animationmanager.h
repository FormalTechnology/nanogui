/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

/**
 * \file nanogui/animationManager.h
 *
 * \brief Defines the manager for managing and synchronizing animations.
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

    /// get ref for instance animation manager.
    static AnimationManager& Instance();

    /// Added animation in manager.
    static void addAnimator(const std::shared_ptr<IAnimatorBase> animator);
    /// Deleted animation in manager.
    static void deleteAnimator(const std::shared_ptr<IAnimatorBase> animator);

    /// Start use animation.
    static void startAnimation();
    /// Stop use animation.
    static void stopAnimation();

    /// Returns time out for the timer.
    static unsigned int getTimeOut();
    /// Sets time out for the timer.
    static void setTimeOut(unsigned int timeOut);

    /// This function must be called to update the state of the animation. Without its call, the animated parameter will not change.
    void updateAnimators();
    
private:

    std::vector<std::shared_ptr<IAnimatorBase>> mAnimatorList;

    Timer mTimer;
    unsigned int mTimeOut;

    AnimationManager() {
        mTimeOut = 0;
    }

    AnimationManager(const AnimationManager& root);
    AnimationManager& operator = (const AnimationManager&);
};

NAMESPACE_END(nanogui)
