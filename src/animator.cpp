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

AnimatorInt::AnimatorInt()
{
}

AnimatorInt::~AnimatorInt()
{

}

void AnimatorInt::start()
{
    mCalc.setCalculatorParams(mParams);
}

void AnimatorInt::setStartValue(int value)
{   
    mParams.startValue = value;
}

int AnimatorInt::getStartValue()
{
    return mParams.startValue;
}

void AnimatorInt::setEndValue(int value)
{   
    mParams.endValue = value;
}

int AnimatorInt::getEndValue()
{   
    return mParams.endValue;
}

void AnimatorInt::animate()
{
    mSetterFunc(mCalc.calculate(mGetterFunc()));
}

void AnimatorInt::setDuration(types::Duration_t value)
{   
    mParams.duration = value;
}

types::Duration_t AnimatorInt::getDuration()
{
    return mParams.duration;
}

void AnimatorInt::setDuration(unsigned int value)
{
  std::chrono::milliseconds m(value);
  mParams.duration = std::chrono::duration_cast<types::Duration_t>(m);
}

void AnimatorInt::setCurveType(types::EasingCurveType type)
{   
    mParams.curve = type;
}

types::EasingCurveType AnimatorInt::getCurveType()
{   
    return  mParams.curve;
}

NAMESPACE_END(nanogui)
