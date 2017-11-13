/*
    src/animator.cpp -- animator for widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/animator.h>
#include <nanogui/animationmanager.h>

NAMESPACE_BEGIN(nanogui)

template <typename T>
Animator<T>::Animator()
{
  mParams.startValue = 0;
  mParams.endValue = 0;
  mParams.curve = types::EasingCurveType::Linear;
  
  setDuration(0);
}

template <typename T>
Animator<T>::~Animator()
{

}

template <typename T>
void Animator<T>::start()
{
    mCalc.setCalculatorParams(mParams);
    mCalc.setTimeOut(AnimationManager::getTimeOut());
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
    mSetterFunc(mCalc.calculate(mGetterFunc()));
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
