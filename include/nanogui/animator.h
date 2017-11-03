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

- Добавить группу анимации. Один аниатор для множества виджетов.
- Один глобальный обьект следит за временем и обновляет состояние аниматоров.
- Аниматор должен регистрироваться в глобальном обьекте.
- Разные типы аниматоров. Нужно два типа: аниматор по кривой и аниматор по ключевым кадрам.
- Написать примеры использования анимации.

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

typedef std::chrono::duration<float, std::chrono::milliseconds> DurationType;

template <typename T>
class NANOGUI_EXPORT Animator {
public:

    Animator();
    virtual ~Animator();

    void setStartValue(T value)
    {
        mStartValue = value;
    }

    T getStartValue()
    {
        return mStartValue;
    }

    void setEndValue(T value)
    {
        mEndValue = value;
    }

    T getEndValue()
    {
        return mEndValue;
    }

    void setDuration(DurationType value)
    {
        mDuration = value;
    }

    DurationType getDuration()
    {
        return mDuration;
    }

    void setCurveType(EasingCurveType type)
    {
        mCurveType = type;
    }

    EasingCurveType getCurveType()
    {
        return mCurveType;
    }

private:

    ///
    using GetCallback = std::function<T()>;
    GetCallback<T> mGetterFunc;

    ///
    using SetCallback = std::function<void(T)>;
    SetCallback<T> mSetterFunc;

    T mStartValue;
    T mEndValue;
    DurationType mDuration;
    EasingCurveType mCurveType;

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

NAMESPACE_END(nanogui)
