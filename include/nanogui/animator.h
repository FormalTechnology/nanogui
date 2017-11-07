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

#include <nanogui/widget.h>
#include <nanogui/calculator.h>
#include <nanogui/types.h>

NAMESPACE_BEGIN(nanogui)
/**
 * \class Animator animator.h nanogui/animator.h
 *
 * \brief Animator for widgets.
 */

class Animator
{
public:

    void setDuration(types::Duration_t value);
    types::Duration_t getDuration();

    void setCurveType(types::EasingCurveType type);
    types::EasingCurveType getCurveType();

protected:

    types::Duration_t mDuration;
    types::EasingCurveType mCurveType;

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

    std::shared_ptr<Calculator> mCalcPtr;

    void animate();
};

NAMESPACE_END(nanogui)
