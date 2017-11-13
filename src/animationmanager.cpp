/*
    src/animator.cpp -- animator for widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/animator.h>
#include <nanogui/animationmanager.h>

NAMESPACE_BEGIN(nanogui)

AnimationManager& AnimationManager::Instance()
{
    static AnimationManager manager;
    return manager;
}

void AnimationManager::addAnimator(const std::shared_ptr<IAnimatorBase> animator)
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
        item->start();
    }

    auto& instance = Instance();
    instance.mTimer.start(std::chrono::milliseconds(Instance().mTimeOut), [&instance]{ instance.updateAnimators(); });
}

void AnimationManager::stopAnimation()
{
    Instance().mTimer.stop();
    Instance().mAnimatorList.clear();
}

void AnimationManager::updateAnimators()
{
    for (auto& item : Instance().mAnimatorList)
    {
        item->animate();
    }
}

unsigned int AnimationManager::getTimeOut()
{
    return Instance().mTimeOut;
}

void AnimationManager::setTimeOut(unsigned int timeOut)
{
    Instance().mTimeOut = timeOut;
}

NAMESPACE_END(nanogui)
