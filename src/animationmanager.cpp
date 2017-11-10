/*
    src/animator.cpp -- animator for widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/animationmanager.h>

NAMESPACE_BEGIN(nanogui)

AnimationManager& AnimationManager::Instance()
{
    static AnimationManager manager;
    return manager;
}

void AnimationManager::addAnimator(const AnimatorInt& animator)
{
    Instance().mAnimatorList.push_back(animator);
}

void AnimationManager::deleteAnimator()
{

}

void AnimationManager::startAnimation()
{
    for (auto& item : Instance().mAnimatorList)
    {
        item.start();
    }

    auto& instance = Instance();
    instance.mTimer.start(std::chrono::milliseconds(10), [&instance]{ instance.updateAnimators(); });
}

void AnimationManager::stopAnimation()
{
    Instance().mTimer.stop();
}

void AnimationManager::updateAnimators()
{
    for (auto& item : Instance().mAnimatorList)
    {
        item.animate();
    }
}

NAMESPACE_END(nanogui)
