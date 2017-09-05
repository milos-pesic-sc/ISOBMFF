/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
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
 * @header      PITM.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef IBMFF_PITM_HPP
#define IBMFF_PITM_HPP

#include <XS/PIMPL/Object.hpp>
#include <IBMFF/FullBox.hpp>
#include <IBMFF/Matrix.hpp>
#include <cstdint>

namespace IBMFF
{
    class PITM: public FullBox, public XS::PIMPL::Object< PITM >
    {
        public:
            
            using XS::PIMPL::Object< PITM >::impl;
            
            PITM( void );
            
            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            
            uint32_t GetItemID( void ) const;
            
            void SetItemID( uint32_t value );
    };
}

#endif /* IBMFF_PITM_HPP */
