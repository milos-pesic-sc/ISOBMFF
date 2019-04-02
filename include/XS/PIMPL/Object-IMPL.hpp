/*******************************************************************************
 * Copyright (c) 2015, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @brief       Private delcarations of the XS::PIMPL::Object template class
 * 
 * This header shall be included in implementations of PIMPL classes.
 * Note that explicit template instanciation is required after the declaration
 * of the IMPL class.
 */

#include <XS/PIMPL/Object.hpp>
#include <memory>
#include <algorithm>

#ifndef XS_PIMPL_CLASS
#error "Please define XS_PIMPL_CLASS before including this header file"
#endif

namespace XS
{
    namespace PIMPL
    {
        /* C++11 support is buggy on MSVC V120 toolset (see C4520)... */
        #if !defined( _MSC_FULL_VER ) || _MSC_FULL_VER >= 190024215
        
        template<>
        Object< XS_PIMPL_CLASS >::Object( void ): impl( new Object< XS_PIMPL_CLASS >::IMPL() )
        {}
        
        template<>
        template< typename ... A >
        Object< XS_PIMPL_CLASS >::Object( A & ... a ): impl( new Object< XS_PIMPL_CLASS >::IMPL( a ... ) )
        {}
        
        template<>
        template< typename ... A >
        Object< XS_PIMPL_CLASS >::Object( const A & ... a ): impl( new Object< XS_PIMPL_CLASS >::IMPL( a ... ) )
        {}
        
        #else
        
        template<>
        Object< XS_PIMPL_CLASS >::Object( void ): impl( new Object< XS_PIMPL_CLASS >::IMPL )
        {}
        
        template<>
        template< typename A1, typename ... A2 >
        Object< XS_PIMPL_CLASS >::Object( A1 a1, A2 ... a2 ): impl( new Object< XS_PIMPL_CLASS >::IMPL( a1, a2 ... ) )
        {}
        
        #endif
        
        template<>
        Object< XS_PIMPL_CLASS >::Object( const Object< XS_PIMPL_CLASS > & o ): impl( new Object< XS_PIMPL_CLASS >::IMPL( *( o.impl ) ) )
        {}
        
        template<>
        Object< XS_PIMPL_CLASS >::Object( Object< XS_PIMPL_CLASS > && o ): impl( std::move( o.impl ) )
        {
            o.impl = nullptr;
        }
        
        template<>
        Object< XS_PIMPL_CLASS >::~Object( void )
        {
            delete this->impl;
        }
        
        template<>
        Object< XS_PIMPL_CLASS > & Object< XS_PIMPL_CLASS >::operator =( Object< XS_PIMPL_CLASS > o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        template< class U >
        void swap( Object< U > & o1, Object< U > & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
    }
}

/* Explicit template instantiation */
template class XS::PIMPL::Object< XS_PIMPL_CLASS >;
template void XS::PIMPL::swap< XS_PIMPL_CLASS >( XS::PIMPL::Object< XS_PIMPL_CLASS > & o1, XS::PIMPL::Object< XS_PIMPL_CLASS > & o2 );