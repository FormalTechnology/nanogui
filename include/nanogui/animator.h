/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

/**
 * \file nanogui/animator.h
 *
 * \brief Defines the animator for widgets.
 */

#pragma once

#include <memory>
#include <functional>
#include <chrono>

#include <nanogui/widget.h>
#include <nanogui/evaluator.h>
#include <nanogui/types.h>

NAMESPACE_BEGIN(nanogui)

/**
 * \class IAnimatorBase animator.h nanogui/animator.h
 *
 * \brief Base Interface for all Animators.
 */
class IAnimatorBase {
public:

    /// Sets the duration of the animation
    virtual void setDuration(types::Duration_t value) = 0;
    /// Returns the duration of the animation
    virtual types::Duration_t getDuration() = 0;

    /// Sets the curve type for Evaluator
    virtual void setCurveType(types::EasingCurveType type) = 0;
    /// Returns the curve type
    virtual types::EasingCurveType getCurveType() = 0;

    virtual ~IAnimatorBase() {}

    /// Evaluate animation use current time.
    virtual void animate() = 0;
    /// Initializes the Animator and Evaluator before starting the animation calculation.
    virtual void start() = 0;
};

/**
 * \class Animator animator.h nanogui/animator.h
 *
 * \brief Animator for widgets.
 */

template <typename T>
class NANOGUI_EXPORT Animator : public IAnimatorBase {
public:

    Animator();
    virtual ~Animator();

    /// Sets the start value for animation.
    void setStartValue(T value);
    /// Returns the start value.
    T getStartValue();

    /// Sets the end value for animation.
    void setEndValue(T value);
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
    
    /// Return true when animation is finished. Animation calculation continues.
    bool isFinished();

    /// Functor for get value for widget.
    std::function<T()> mGetterFunc;
    /// Functor for set value in widget.
    std::function<void(T)> mSetterFunc;

private:

    EvaluatorParams<T> mParams;
    Evaluator<T> mCalc;
    bool mAnimationFinished;

    std::chrono::system_clock::time_point mStartTime;
};

template <typename T>
Animator<T>::Animator() {
  mParams.startValue = 0;
  mParams.endValue = 0;
  mParams.curve = types::EasingCurveType::Linear;

  mAnimationFinished = false;

  setDuration(0);
}

template <typename T>
Animator<T>::~Animator() {
}

template <typename T>
void Animator<T>::start() {
    mStartTime = std::chrono::system_clock::now();

    mAnimationFinished = false;
    mCalc.setEvaluatorParams(mParams);
}

template <typename T>
void Animator<T>::setStartValue(T value) {
    mParams.startValue = value;
}

template <typename T>
T Animator<T>::getStartValue() {
    return mParams.startValue;
}

template <typename T>
void Animator<T>::setEndValue(T value) {
    mParams.endValue = value;
}

template <typename T>
T Animator<T>::getEndValue() {
    return mParams.endValue;
}

template <typename T>
void Animator<T>::animate() {
    if (!mSetterFunc || !mGetterFunc)
        return;

    auto temp = mCalc.evaluate(mGetterFunc(), mStartTime);
    if (temp == mParams.endValue)
        mAnimationFinished = true;

    mSetterFunc(temp);
}

template <typename T>
bool Animator<T>::isFinished() {
    return mAnimationFinished;
}

template <typename T>
void Animator<T>::setDuration(types::Duration_t value) {
    mParams.duration = value;
}

template <typename T>
types::Duration_t Animator<T>::getDuration() {
    return mParams.duration;
}

template <typename T>
void Animator<T>::setDuration(unsigned int value) {
  std::chrono::milliseconds m(value);
  mParams.duration = std::chrono::duration_cast<types::Duration_t>(m);
}

template <typename T>
void Animator<T>::setCurveType(types::EasingCurveType type) {
    mParams.curve = type;
}

template <typename T>
types::EasingCurveType Animator<T>::getCurveType() {
    return  mParams.curve;
}

NAMESPACE_END(nanogui)
