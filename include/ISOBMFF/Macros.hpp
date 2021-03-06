/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 DigiDNA - www.digidna.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      Macros.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_MACROS_HPP
#define ISOBMFF_MACROS_HPP

#if defined(__clang__)
#if __has_feature(cxx_rtti)
#define RTTI_ENABLED
#endif
#elif defined(__GNUG__)
#if defined(__GXX_RTTI)
    #define RTTI_ENABLED
  #endif
#elif defined(_MSC_VER)
  #if defined(_CPPRTTI)
    #define RTTI_ENABLED
  #endif
#endif

/*
 * Disable warnings about class members not having DLL-interface.
 * Eg: std::shared_ptr
 */
#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable: 4251 )
#endif

/*!
 * @define      ISOBMFF_EXPORT
 * @abstract    Used to export public functions.
 */
#if defined( _WIN32 ) && defined( ISOBMFF_DLL_BUILD )
#define ISOBMFF_EXPORT __declspec( dllexport )
#elif defined( _WIN32 ) && defined( ISOBMFF_LIB_BUILD )
#define ISOBMFF_EXPORT 
#elif defined( _WIN32 )
#define ISOBMFF_EXPORT __declspec( dllimport )
#else
#define ISOBMFF_EXPORT 
#endif

/*!
 * @define      ISOBMFF_NOEXCEPT
 * @abstract    Replacement for the C++ `noexcept` keyword, not supported by all compilers.
 * @param       _a_ If `_a_` evaluates to true, the function is declared to not throw any exceptions.
 */
#ifndef _MSC_VER
#define ISOBMFF_NOEXCEPT( _a_ ) noexcept( _a_ )
#else
#define ISOBMFF_NOEXCEPT( _a_ ) 
#endif

#endif /* ISOBMFF_MACROS_HPP */
