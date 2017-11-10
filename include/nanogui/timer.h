/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <functional>
#include <thread>
#include <chrono>

#include <nanogui/widget.h>

NAMESPACE_BEGIN(nanogui)

class Timer
{

public:

    Timer();
    ~Timer();

    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    void start(const Interval& interval, const Timeout& timeout);
    void stop();

private:

    std::thread mWorkThread;
    bool mRunning;
};

NAMESPACE_END(nanogui)
