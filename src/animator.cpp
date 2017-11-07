/*
    src/animator.cpp -- animator for widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/animator.h>

NAMESPACE_BEGIN(nanogui)

AnimatorInt::AnimatorInt()
{

}

AnimatorInt::~AnimatorInt()
{

}

void AnimatorInt::setStartValue(int value)
{
    mStartValue = value;
}

int AnimatorInt::getStartValue()
{
    return mStartValue;
}

void AnimatorInt::setEndValue(int value)
{
    mEndValue = value;
}

int AnimatorInt::getEndValue()
{
    return mEndValue;
}

void Animator::setDuration(types::Duration_t value)
{
    mDuration = value;
}

types::Duration_t Animator::getDuration()
{
    return mDuration;
}

void Animator::setCurveType(types::EasingCurveType type)
{
    mCurveType = type;
}

types::EasingCurveType Animator::getCurveType()
{
    return mCurveType;
}

NAMESPACE_END(nanogui)
