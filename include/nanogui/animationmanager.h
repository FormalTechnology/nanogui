/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <vector>
#include <thread>
#include <chrono>

#include <nanogui/widget.h>
#include <nanogui/animator.h>

#include <iostream>

NAMESPACE_BEGIN(nanogui)

class Timer
{
    std::thread th;
    bool running = false;

public:

    ~Timer()
    {
        stop();
    }

    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    void start(const Interval& interval, const Timeout& timeout)
    {
        if (running)
        {
            return;
        }

        running = true;

        th = std::thread([=]()
        {
            while (running == true)
            {
                std::cout << "Thread is work!" << std::endl;
                std::this_thread::sleep_for(interval);
                timeout();
            }
        });
    }

    void stop()
    {
        if (!running)
        {
            return;
        }

        running = false;
        if (th.joinable())
        {
            th.join();
        }
    }
};


class NANOGUI_EXPORT AnimationManager
{
public:
    static AnimationManager& Instance()
    {
        static AnimationManager manager;
        return manager;
    }

    static void addAnimator(const AnimatorInt& animator)
    {
        Instance().mAnimatorList.push_back(animator);
    }

    static void deleteAnimator()
    {

    }

    static void startAnimation()
    {
        for (auto& item : Instance().mAnimatorList)
        {
            item.start();
        }

        auto& instance = Instance();
        instance.mTimer.start(std::chrono::milliseconds(10), [&instance]{ instance.updateAnimators(); });
    }

    static void stopAnimation()
    {
        Instance().mTimer.stop();
    }

private:

    std::vector<AnimatorInt> mAnimatorList;

    Timer mTimer;

    void updateAnimators()
    {
        for (auto& item : Instance().mAnimatorList)
        {
            item.animate();
        }
    }

    AnimationManager(){}
    AnimationManager(const AnimationManager& root);
    AnimationManager& operator = (const AnimationManager&);
};

NAMESPACE_END(nanogui)
