//
//  fakeglfw.cpp
//  NanoGUICocoa
//
//  Created by Dmitry Lavrov on 07/12/2015.
//  Copyright © 2015 Formal Technology. All rights reserved.
//

#include <nanogui/fakeglfw.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void glfwSetClipboardString(GLFWwindow * w, const char *string)
{
    // TODO
}

const char* glfwGetClipboardString(GLFWwindow *w)
{
    // TODO
    return NULL;
}

