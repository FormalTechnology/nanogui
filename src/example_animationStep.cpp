/*
    src/example2.cpp -- C++ version of an example application that shows
    how to use the form helper class. For a Python implementation, see
    '../python/example2.py'.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <nanogui/nanogui.h>

using namespace nanogui;

enum test_enum {
    Item1 = 0,
    Item2,
    Item3
};

bool bvar = true;
int ivar = 12345678;
double dvar = 3.1415926;
float fvar = (float)dvar;
std::string strval = "A string";
test_enum enumval = Item2;
Color colval(0.5f, 0.5f, 0.7f, 1.f);

int main(int /* argc */, char ** /* argv */) {
    nanogui::init();

    AnimationManager::Instance();
    AnimationManager::setTimeOut(10);

    /* scoped variables */ {
        bool use_gl_4_1 = true;// Set to true to create an OpenGL 4.1 context.
        Screen *screen = nullptr;

        if (use_gl_4_1) {
            // NanoGUI presents many options for you to utilize at your discretion.
            // See include/nanogui/screen.h for what all of these represent.
            screen = new Screen(Vector2i(500, 700), "NanoGUI test [GL 4.1]",
                                /*resizable*/true, /*fullscreen*/false, /*colorBits*/8,
                                /*alphaBits*/8, /*depthBits*/24, /*stencilBits*/8,
                                /*nSamples*/0, /*glMajor*/4, /*glMinor*/1);
        } else {
            screen = new Screen(Vector2i(500, 700), "NanoGUI test");
        }

        bool enabled = true;
        FormHelper *gui = new FormHelper(screen);
        ref<Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
        gui->addGroup("Basic types");
        gui->addVariable("bool", bvar);
        gui->addVariable("string", strval);

        gui->addGroup("Validating fields");
        gui->addVariable("int", ivar)->setSpinnable(true);
        gui->addVariable("float", fvar);
        gui->addVariable("double", dvar)->setSpinnable(true);

        gui->addGroup("Complex types");
        gui->addVariable("Enumeration", enumval, enabled)
           ->setItems({"Item 1", "Item 2", "Item 3"});
        gui->addVariable("Color", colval)
           ->setFinalCallback([](const Color &c) {
                 std::cout << "ColorPicker Final Callback: ["
                           << c.r() << ", "
                           << c.g() << ", "
                           << c.b() << ", "
                           << c.w() << "]" << std::endl;
             });

        gui->addGroup("Other widgets");
        gui->addButton("Press for begin animation", []()
        {
          AnimationManager::startAnimation();
          std::cout << "Button pressed." << std::endl;
        });

        FormHelper* gui2 = new FormHelper(screen);
        ref<Window> window2 = gui2->addWindow(Eigen::Vector2i(200, 10), "Form helper example 2");
        gui2->addGroup("Basic types");
        gui2->addVariable("bool", bvar);
        gui2->addVariable("string", strval);

        gui2->addGroup("Validating fields");
        gui2->addVariable("int", ivar)->setSpinnable(true);
        gui2->addVariable("float", fvar);
        gui2->addVariable("double", dvar)->setSpinnable(true);

        gui2->addGroup("Complex types");
        gui2->addVariable("Enumeration", enumval, enabled)
           ->setItems({"Item 1", "Item 2", "Item 3"});
        gui2->addVariable("Color", colval)
           ->setFinalCallback([](const Color &c) {
                 std::cout << "ColorPicker Final Callback: ["
                           << c.r() << ", "
                           << c.g() << ", "
                           << c.b() << ", "
                           << c.w() << "]" << std::endl;
             });

        gui2->addGroup("Other widgets");
        gui2->addButton("A button", []()
        {
          std::cout << "Button pressed." << std::endl;
        });

        screen->setVisible(true);
        screen->performLayout();

        auto animator = std::make_shared<AnimatorStep<int>>();

        CalculatorParams<int> step1;
        CalculatorParams<int> step2;

        step1.startValue = 0;
        step1.endValue = 500;

        std::chrono::milliseconds m(1000);
        step1.duration = m;

        step2.startValue = 500;
        step2.endValue = 0;
        step2.duration = m;

        animator->addStep(step1);
        animator->addStep(step2);
        animator->mGetterFunc = std::bind(&nanogui::getter, window.get(), Axis::eX);
        animator->mSetterFunc = std::bind(&nanogui::setter, std::placeholders::_1, window.get(), Axis::eX);

        AnimationManager::Instance().addAnimator(animator);

        nanogui::mainloop();
        AnimationManager::stopAnimation();
    }

    nanogui::shutdown();
    return 0;
}
