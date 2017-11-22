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

/*- Добавить группу анимации. Один аниатор для множества виджетов.
- Один глобальный обьект следит за временем и обновляет состояние аниматоров.
- Аниматор должен регистрироваться в глобальном обьекте.
- Разные типы аниматоров. Нужно два типа: аниматор по кривой и аниматор по ключевым кадрам.
- Написать примеры использования анимации.*/

#pragma once

#include <memory>
#include <functional>
#include <chrono>

#include <nanogui/widget.h>
#include <nanogui/evaluator.h>
#include <nanogui/types.h>

NAMESPACE_BEGIN(nanogui)
/**
 * \class Animator animator.h nanogui/animator.h
 *
 * \brief Animator for widgets.
 */

class IAnimatorBase
{
public:

    virtual void setDuration(types::Duration_t value) = 0;
    virtual types::Duration_t getDuration() = 0;

    virtual void setCurveType(types::EasingCurveType type) = 0;
    virtual types::EasingCurveType getCurveType() = 0;

    virtual ~IAnimatorBase() {}

    virtual void animate() = 0;
    virtual void start() = 0;
};

template <typename T>
class NANOGUI_EXPORT Animator : public IAnimatorBase {
public:

    Animator();
    virtual ~Animator();

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
    bool isFinished();

    std::function<T()> mGetterFunc;
    std::function<void(T)> mSetterFunc;

private:

    EvaluatorParams<T> mParams;
    Evaluator<T> mCalc;
    bool mAnimationFinished;

    std::chrono::system_clock::time_point mStartTime;
};

template <typename T>
Animator<T>::Animator()
{
  mParams.startValue = 0;
  mParams.endValue = 0;
  mParams.curve = types::EasingCurveType::Linear;

  mAnimationFinished = false;

  setDuration(0);
}

template <typename T>
Animator<T>::~Animator()
{

}

template <typename T>
void Animator<T>::start()
{
    mStartTime = std::chrono::system_clock::now();

    mAnimationFinished = false;
    mCalc.setEvaluatorParams(mParams);
}

template <typename T>
void Animator<T>::setStartValue(T value)
{
    mParams.startValue = value;
}

template <typename T>
T Animator<T>::getStartValue()
{
    return mParams.startValue;
}

template <typename T>
void Animator<T>::setEndValue(T value)
{
    mParams.endValue = value;
}

template <typename T>
T Animator<T>::getEndValue()
{
    return mParams.endValue;
}

template <typename T>
void Animator<T>::animate()
{
    if (!mSetterFunc || !mGetterFunc)
    {
        return;
    }

    auto temp = mCalc.evaluate(mGetterFunc(), mStartTime);
    if (temp == mParams.endValue)
    {
        mAnimationFinished = true;
    }

    mSetterFunc(temp);
}

template <typename T>
bool Animator<T>::isFinished()
{
    return mAnimationFinished;
}

template <typename T>
void Animator<T>::setDuration(types::Duration_t value)
{
    mParams.duration = value;
}

template <typename T>
types::Duration_t Animator<T>::getDuration()
{
    return mParams.duration;
}

template <typename T>
void Animator<T>::setDuration(unsigned int value)
{
  std::chrono::milliseconds m(value);
  mParams.duration = std::chrono::duration_cast<types::Duration_t>(m);
}

template <typename T>
void Animator<T>::setCurveType(types::EasingCurveType type)
{
    mParams.curve = type;
}

template <typename T>
types::EasingCurveType Animator<T>::getCurveType()
{
    return  mParams.curve;
}

NAMESPACE_END(nanogui)
