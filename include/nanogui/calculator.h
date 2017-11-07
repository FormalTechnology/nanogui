/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <nanogui/widget.h>
#include <nanogui/types.h>

NAMESPACE_BEGIN(nanogui)

struct CalculatorParams
{
  int startValue;
  int endValue;
  types::Duration_t duration;
  types::EasingCurveType curve;
};

class Calculator
{
public:

    Calculator();
    Calculator(const CalculatorParams& params);
    
    void setCalculatorParams(const CalculatorParams& params);
    CalculatorParams& getCalculatorParams();
    
    void calculate();

private:

    int mCurrentValue;
    int mValueStep;
    int mTimeStep;
    int mAccumulateTime;

    CalculatorParams mParams;
    
    void init();
};

NAMESPACE_END(nanogui)
