/*
    src/animator.cpp -- animator for widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nanogui/timer.h>

NAMESPACE_BEGIN(nanogui)

Timer::Timer()
{
    mRunning = false;
}

Timer::~Timer()
{
    stop();
}

void Timer::start(const Interval& interval, const Timeout& timeout)
{
    if (mRunning)
    {
        return;
    }

    mRunning = true;

    mWorkThread = std::thread([=]()
    {
        while (mRunning == true)
        {
            std::this_thread::sleep_for(interval);
            timeout();
        }
    });
}

void Timer::stop()
{
    if (!mRunning)
    {
        return;
    }

    mRunning = false;
    if (mWorkThread.joinable())
    {
        mWorkThread.join();
    }
}

NAMESPACE_END(nanogui)
