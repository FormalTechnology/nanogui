/*
    src/animator.cpp -- animator for widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/calculator.h>

NAMESPACE_BEGIN(nanogui)

Calculator::Calculator(int startValue, int endValue, types::Duration_t duration, types::EasingCurveType type)
{
    mCurveType = type;
    mCurrentValue = startValue;
    mAccumulateTime = 0;
    mTimeStep = 10;

    if (type == types::EasingCurveType::Linear)
    {
        mValueStep = (endValue - startValue) / duration.count();
        mValueStep *= mTimeStep;
    }
    else
    {
        mValueStep = 0;
    }
}

void Calculator::calculate()
{
    switch (mCurveType) {
    case types::EasingCurveType::Linear:
        mCurrentValue += mValueStep;
        mAccumulateTime += mTimeStep;
        break;
    default:
        break;
    }
}

NAMESPACE_END(nanogui)
