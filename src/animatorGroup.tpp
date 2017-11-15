/*
    src/animator.cpp -- animator for widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/animatorGroup.h>
#include <nanogui/animationmanager.h>

NAMESPACE_BEGIN(nanogui)

enum class Axis
{
  eX,
  eY
};

inline int getter(Widget* window, Axis axis)
{
  Eigen::Vector2i pos = window->position();
  if (axis == Axis::eX)
  {
    return pos.x();
  }
  else if (axis == Axis::eY)
  {
    return pos.y();
  }

  return -1;
}

inline void setter(int value, Widget* window, Axis axis)
{
  Eigen::Vector2i pos = window->position();
  if (axis == Axis::eX)
  {
    Eigen::Vector2i newPos(value, pos.y());
    window->setPosition(newPos);
  }
  else if (axis == Axis::eY)
  {
    Eigen::Vector2i newPos(pos.x(), value);
    window->setPosition(newPos);
  }
}

template <typename T>
AnimatorGroup<T>::AnimatorGroup()
{
}

template <typename T>
AnimatorGroup<T>::~AnimatorGroup()
{

}

template <typename T>
void AnimatorGroup<T>::start()
{
    for (auto& item : mAnimationList)
    {
        item.mCalc.setCalculatorParams(item.mParams);
        item.mCalc.setTimeOut(AnimationManager::getTimeOut());
    }
}

template <typename T>
void AnimatorGroup<T>::setStartValue(T value)
{
}

template <typename T>
T AnimatorGroup<T>::getStartValue()
{
    return T();
}

template <typename T>
void AnimatorGroup<T>::setEndValue(T value)
{
}

template <typename T>
T AnimatorGroup<T>::getEndValue()
{   
    return T();
}

template <typename T>
void AnimatorGroup<T>::animate()
{
    for (auto& item : mAnimationList)
    {
        if (!item.mSetter || !item.mGetter)
        {
            continue;
        }

        auto temp = item.mCalc.calculate(item.mGetter());
        item.mSetter(temp);
    }
}

template <typename T>
void AnimatorGroup<T>::addAnimation(Widget* widget, CalculatorParams<T> params)
{
    AnimationGroupParams<T> animParams;
    animParams.mParams = params;

    animParams.mGetter = std::bind(&getter, widget, Axis::eX);
    animParams.mSetter = std::bind(&setter, std::placeholders::_1, widget, Axis::eX);
    animParams.mParams.curve = types::EasingCurveType::Linear;

    mAnimationList.push_back(animParams);
}

template <typename T>
void AnimatorGroup<T>::setDuration(types::Duration_t value)
{
}

template <typename T>
types::Duration_t AnimatorGroup<T>::getDuration()
{
    return std::chrono::milliseconds(1000);
}

template <typename T>
void AnimatorGroup<T>::setDuration(unsigned int value)
{
}

template <typename T>
void AnimatorGroup<T>::setCurveType(types::EasingCurveType type)
{
}

template <typename T>
types::EasingCurveType AnimatorGroup<T>::getCurveType()
{
    return types::EasingCurveType::Linear;
}

NAMESPACE_END(nanogui)
