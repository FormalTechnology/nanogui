/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <vector>
#include <chrono>

#include <nanogui/widget.h>
#include <nanogui/animator.h>
#include <nanogui/types.h>

NAMESPACE_BEGIN(nanogui)

template <typename T>
struct AnimationGroupParams
{
    EvaluatorParams<T> mParams;
    Evaluator<T> mCalc;
    std::function<T()> mGetter;
    std::function<void(T)> mSetter;
};

template <typename T>
class NANOGUI_EXPORT AnimatorGroup : public IAnimatorBase {
public:

    AnimatorGroup();
    virtual ~AnimatorGroup();

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

    void addAnimation(Widget* widget, EvaluatorParams<T> params);

private:

    std::vector<AnimationGroupParams<T>> mAnimationList;
    std::chrono::system_clock::time_point mStartTime;
};

NAMESPACE_END(nanogui)

#include "../../src/animatorGroup.tpp"
