/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

/**
 * \file nanogui/animatorGroup.h
 *
 * \brief Animator for group widgets.
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

    /// Sets the start value for animation.
    void setStartValue(T value);
    /// Returns the start value.
    T getStartValue();

    /// Sets the end value for animation.
    void setEndValue(T);
    /// Returns the end value.
    T getEndValue();

    /// Sets the duration of the animation
    void setDuration(types::Duration_t value);
    /// Returns the duration of the animation
    types::Duration_t getDuration();
    
    /// Sets the duration of the animation
    void setDuration(unsigned int value);

    /// Sets the curve type for Evaluator
    void setCurveType(types::EasingCurveType type);
    /// Returns the curve type
    types::EasingCurveType getCurveType();

    /// Evaluate animation use current time.
    void animate();
    /// Initializes the Animator and Evaluator before starting the animation calculation.
    void start();

    /// Add widget and animation params to group.
    void addAnimation(Widget* widget, EvaluatorParams<T> params);

private:

    std::vector<AnimationGroupParams<T>> mAnimationList;
    std::chrono::system_clock::time_point mStartTime;
};

enum class Axis
{
  eX,
  eY
};

inline int getter(Widget* window, Axis axis) {
  Eigen::Vector2i pos = window->position();
  if (axis == Axis::eX) {
    return pos.x();
  } else if (axis == Axis::eY) {
    return pos.y();
  }

  return -1;
}

inline void setter(int value, Widget* window, Axis axis) {
  Eigen::Vector2i pos = window->position();
  if (axis == Axis::eX) {
    Eigen::Vector2i newPos(value, pos.y());
    window->setPosition(newPos);
  } else if (axis == Axis::eY) {
    Eigen::Vector2i newPos(pos.x(), value);
    window->setPosition(newPos);
  }
}

template <typename T>
AnimatorGroup<T>::AnimatorGroup() {
}

template <typename T>
AnimatorGroup<T>::~AnimatorGroup() {
}

template <typename T>
void AnimatorGroup<T>::start() {
    mStartTime = std::chrono::system_clock::now();

    for (auto& item : mAnimationList)
        item.mCalc.setEvaluatorParams(item.mParams);
}

template <typename T>
void AnimatorGroup<T>::setStartValue(T /*value*/) {
}

template <typename T>
T AnimatorGroup<T>::getStartValue() {
    return T();
}

template <typename T>
void AnimatorGroup<T>::setEndValue(T /*value*/) {
}

template <typename T>
T AnimatorGroup<T>::getEndValue() {
    return T();
}

template <typename T>
void AnimatorGroup<T>::animate() {
    for (auto& item : mAnimationList) {
        if (!item.mSetter || !item.mGetter)
            continue;

        auto temp = item.mCalc.evaluate(item.mGetter(), mStartTime);
        item.mSetter(temp);
    }
}

template <typename T>
void AnimatorGroup<T>::addAnimation(Widget* widget, EvaluatorParams<T> params) {
    AnimationGroupParams<T> animParams;
    animParams.mParams = params;

    animParams.mGetter = std::bind(&getter, widget, Axis::eX);
    animParams.mSetter = std::bind(&setter, std::placeholders::_1, widget, Axis::eX);
    animParams.mParams.curve = types::EasingCurveType::Linear;

    mAnimationList.push_back(animParams);
}

template <typename T>
void AnimatorGroup<T>::setDuration(types::Duration_t /*value*/) {
}

template <typename T>
types::Duration_t AnimatorGroup<T>::getDuration() {
    return std::chrono::milliseconds(1000);
}

template <typename T>
void AnimatorGroup<T>::setDuration(unsigned int /*value*/) {
}

template <typename T>
void AnimatorGroup<T>::setCurveType(types::EasingCurveType /*type*/) {
}

template <typename T>
types::EasingCurveType AnimatorGroup<T>::getCurveType() {
    return types::EasingCurveType::Linear;
}

NAMESPACE_END(nanogui)
