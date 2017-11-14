/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <vector>

#include <nanogui/widget.h>
#include <nanogui/animator.h>
#include <nanogui/types.h>

NAMESPACE_BEGIN(nanogui)

template <typename T>
class NANOGUI_EXPORT AnimatorStep : public IAnimatorBase {
public:

    AnimatorStep();
    virtual ~AnimatorStep();

    void setStartValue(T value);
    T getStartValue();

    void setEndValue(T value);
    T getEndValue();

    void setDuration(types::Duration_t value);
    types::Duration_t getDuration();
    
    void setDuration(unsigned int value);

    void setCurveType(types::EasingCurveType type);
    types::EasingCurveType getCurveType();

    void animate();
    void start();

    void addStep(CalculatorParams<T> step);

    std::function<T()> mGetterFunc;
    std::function<void(T)> mSetterFunc;

private:

    Animator<T> mAnimator;
    std::vector<CalculatorParams<T>> mStepParamsList;
    unsigned int mNextIndex;
};

NAMESPACE_END(nanogui)

#include "../../src/animatorStep.tpp"
