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

#include <nanogui/widget.h>
#include <nanogui/calculator.h>
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

    std::function<T()> mGetterFunc;
    std::function<void(T)> mSetterFunc;

private:

    CalculatorParams<T> mParams;
    Calculator<T> mCalc;
};

NAMESPACE_END(nanogui)

#include "../../src/animator.tpp"
