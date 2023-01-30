/*
 * Crystal GUI (crystalgui) is a GUI library built on raylib.
 *
 * This library even provides support for raygui, A simple and easy-to-use
 * immediate-mode gui library
 *
 * Defining "RAYGUI_IMPLEMENTATION" before including this library will cause
 * this library to be used as comparibility mode for raygui. Make sure to
 * load the resources after initializing the window and unload them before
 * closing the window.
 * 
 * The usage of comparibility mode is almost the same as raygui so make sure
 * to read the documentation and examples of those. Those may be provided
 * in this repository.
 *
 * Copyright (c) 2023 Anstro Pleuton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CRYSTALGUI_H
#define CRYSTALGUI_H

#ifdef RAYGUI_IMPLEMENTATION

// This header uses custom implementation of raygui as a compatibility feature
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"



#else // RAYGUI_IMPLEMENTATION



#endif // RAYGUI_IMPLEMENTATION

#endif // CRYSTALGUI_H
