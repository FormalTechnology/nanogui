/*
    src/calculator.cpp -- calculate value use curve and time

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/calculator.h>

NAMESPACE_BEGIN(nanogui)

Calculator::Calculator()
{
    init();
}

Calculator::Calculator(const CalculatorParams& params)
{
  setCalculatorParams(params);
}

void Calculator::setCalculatorParams(const CalculatorParams& params)
{
    mParams = params;
    
    init();
}

CalculatorParams& Calculator::getCalculatorParams()
{
  return mParams;
}

void Calculator::init()
{
    mAccumulateTime = 0;
    mTimeStep = 10;
    mValueStep = 0;
}

int Calculator::calculate(const int currentValue)
{
    static bool fistCall = true;
    int value = 0;

    switch (mParams.curve) {
    case types::EasingCurveType::Linear:
      
        if (fistCall)
        {
            mValueStep = (mParams.endValue - mParams.startValue) / mParams.duration.count();
            mValueStep *= mTimeStep;
            fistCall = false;
        }

        value = currentValue + mValueStep;
        mAccumulateTime += mTimeStep;
        break;
    default:
        break;
    }

    return  value;
}

NAMESPACE_END(nanogui)
