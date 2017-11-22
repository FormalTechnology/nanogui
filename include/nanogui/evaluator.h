/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

/**
 * \file nanogui/evaluator.h
 *
 * \brief Defines the Evaluator for calculate new value.
 * 
 * This class calculate new value use animation params. Duration, curve type.
 */

#pragma once

#include <chrono>

#include <nanogui/widget.h>
#include <nanogui/types.h>

NAMESPACE_BEGIN(nanogui)

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
    
    /// Sets the params for evaluate new value.
    void setEvaluatorParams(const EvaluatorParams<T>& params);
    /// Returns the params for evaluate new value.
    EvaluatorParams<T>& getEvaluatorParams();

    /// Evaluate new value use current time and animation start time.
    T evaluate(const T currentValue, const std::chrono::system_clock::time_point& startTime) const;

private:

    EvaluatorParams<T> mParams;
};

template <typename T>
Evaluator<T>::Evaluator() {
}

template <typename T>
Evaluator<T>::Evaluator(const EvaluatorParams<T>& params) {
  setEvaluatorParams(params);
}

template <typename T>
void Evaluator<T>::setEvaluatorParams(const EvaluatorParams<T>& params) {
    mParams = params;
}

template <typename T>
EvaluatorParams<T>& Evaluator<T>::getEvaluatorParams() {
  return mParams;
}

template  <typename T>
T Evaluator<T>::evaluate(const T /*currentValue*/, const std::chrono::system_clock::time_point& startTime) const {
    T value{};
    const std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

    switch (mParams.curve) {
    case types::EasingCurveType::Linear:

        value = mParams.startValue + ((mParams.endValue - mParams.startValue) * (((currentTime - startTime).count() / 1000) / static_cast<double>(mParams.duration.count())));

        bool inverse = (mParams.endValue - mParams.startValue) < 0;

        if (!inverse) {
            if (value >= mParams.endValue)
                return  mParams.endValue;
        } else {
            if (value <= mParams.endValue)
                return  mParams.endValue;
        }

        break;
    }

    return  value;
}

NAMESPACE_END(nanogui)
