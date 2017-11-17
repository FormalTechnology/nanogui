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

class IAnimatorBase;

template <typename T>
struct EvaluatorParams
{
  T startValue;
  T endValue;
  types::Duration_t duration;
  types::EasingCurveType curve;
};

template <typename T>
class Evaluator
{
public:

    Evaluator();
    Evaluator(const EvaluatorParams<T>& params);
    
    void setEvaluatorParams(const EvaluatorParams<T>& params);
    EvaluatorParams<T>& getEvaluatorParams();

    T evaluate(const T currentValue);

    unsigned int getTimeOut();
    void setTimeOut(unsigned int timeOut);

private:

    unsigned int mAccumulateTime;
    unsigned int mTimeOut;

    EvaluatorParams<T> mParams;
    
    void init();
};

NAMESPACE_END(nanogui)

#include "../../src/evaluator.tpp"
