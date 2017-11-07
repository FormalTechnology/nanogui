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

#include <chrono>

#include <nanogui/widget.h>

NAMESPACE_BEGIN(nanogui)
/**
 * \class Animator animator.h nanogui/animator.h
 *
 * \brief Animator for widgets.
 */

/// Easing curve type.
enum class EasingCurveType {
    Linear         ///< Linear curve type.
};

typedef std::chrono::duration<unsigned int> DurationType;

class Animator
{
public:

    void setDuration(DurationType value);
    DurationType getDuration();

    void setCurveType(EasingCurveType type);
    EasingCurveType getCurveType();

protected:

    DurationType mDuration;
    EasingCurveType mCurveType;

    virtual void animate() = 0;
};

class NANOGUI_EXPORT AnimatorInt : public Animator {
public:

    AnimatorInt();
    virtual ~AnimatorInt();

    void setStartValue(int value);
    int getStartValue();

    void setEndValue(int value);
    int getEndValue();

private:

    ///
    typedef std::function<int()> GetCallBack_t;
    GetCallBack_t mGetterFunc;

    ///
    typedef std::function<void(int)> SetCallBack_t;
    SetCallBack_t mSetterFunc;

    int mStartValue;
    int mEndValue;

    void animate()
    {
        int currentValue = mGetterFunc();
        auto d = (mEndValue - mStartValue) / mDuration.count();
        currentValue += d * 10;
        mSetterFunc(currentValue);
    }
};

class Calculator
{
public:

    Calculator(int startValue, int endValue, DurationType duration, EasingCurveType type)
    {
        mCurveType = type;
        mCurrentValue = startValue;
        mAccumulateTime = 0;
        mTimeStep = 10;

        if (type == EasingCurveType::Linear)
        {
            mValueStep = (endValue - startValue) / duration.count();
            mValueStep *= mTimeStep;
        }
        else
        {
            mValueStep = 0;
        }
    }

    void calculate()
    {
        switch (mCurveType) {
        case EasingCurveType::Linear:
            mCurrentValue += mValueStep;
            mAccumulateTime += mTimeStep;
            break;
        default:
            break;
        }
    }

private:

    int mCurrentValue;
    int mValueStep;
    int mTimeStep;
    int mAccumulateTime;
    EasingCurveType mCurveType;
};

NAMESPACE_END(nanogui)
