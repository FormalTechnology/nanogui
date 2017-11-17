/*
    src/calculator.cpp -- calculate value use curve and time

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/evaluator.h>
#include <nanogui/animator.h>
#include <nanogui/animationmanager.h>

NAMESPACE_BEGIN(nanogui)

template <typename T>
Evaluator<T>::Evaluator()
{
    init();
}

template <typename T>
Evaluator<T>::Evaluator(const EvaluatorParams<T>& params)
{
  setEvaluatorParams(params);
}

template <typename T>
void Evaluator<T>::setEvaluatorParams(const EvaluatorParams<T>& params)
{
    mParams = params;
    
    init();
}

template <typename T>
EvaluatorParams<T>& Evaluator<T>::getEvaluatorParams()
{
  return mParams;
}

template <typename T>
void Evaluator<T>::init()
{
    mAccumulateTime = 0;
    mTimeOut = 0;
}

template  <typename T>
T Evaluator<T>::evaluate(const T currentValue)
{
    T value = 0;

    if (mAccumulateTime >= mParams.duration.count())
    {
        return  currentValue;
    }

    switch (mParams.curve) {
    case types::EasingCurveType::Linear:

        mAccumulateTime += mTimeOut;

        value = mParams.startValue + ((mParams.endValue - mParams.startValue) * (mAccumulateTime / (double)mParams.duration.count()));

        break;
    }

    return  value;
}

template <typename T>
unsigned int Evaluator<T>::getTimeOut()
{
    return mTimeOut;
}

template <typename T>
void Evaluator<T>::setTimeOut(unsigned int timeOut)
{
    mTimeOut = timeOut;
}

NAMESPACE_END(nanogui)
