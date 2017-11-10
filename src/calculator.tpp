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

template <typename T>
Calculator<T>::Calculator()
{
    init();
}

template <typename T>
Calculator<T>::Calculator(const CalculatorParams<T>& params)
{
  setCalculatorParams(params);
}

template <typename T>
void Calculator<T>::setCalculatorParams(const CalculatorParams<T>& params)
{
    mParams = params;
    
    init();
}

template <typename T>
CalculatorParams<T>& Calculator<T>::getCalculatorParams()
{
  return mParams;
}

template <typename T>
void Calculator<T>::init()
{
    mAccumulateTime = 0;
}

template  <typename T>
int Calculator<T>::calculate(const int currentValue)
{
    int value = 0;

    if (mAccumulateTime >= mParams.duration.count())
    {
        return  currentValue;
    }

    switch (mParams.curve) {
    case types::EasingCurveType::Linear:

        mAccumulateTime += 10;

        value = mParams.startValue + ((mParams.endValue - mParams.startValue) * (mAccumulateTime / (double)mParams.duration.count()));

        break;
    }

    return  value;
}

NAMESPACE_END(nanogui)
