/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <chrono>

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

    T evaluate(const T currentValue, const std::chrono::system_clock::time_point& startTime);

private:

    EvaluatorParams<T> mParams;
};

NAMESPACE_END(nanogui)

#include "../../src/evaluator.tpp"
