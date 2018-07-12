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
 * @file        Box.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/Box.hpp>
#include <ISOBMFF/Utils.hpp>
#include <ISOBMFF/DisplayableObjectContainer.hpp>
#include <ISOBMFF/IParser.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::Box >::IMPL
{
    public:
        
        IMPL( const std::string & name = "????" );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string            _name;
        std::vector< uint8_t > _data;
        bool                   _hasData;
};

#define XS_PIMPL_CLASS ISOBMFF::Box
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    Box::Box( const std::string & name ): XS::PIMPL::Object< Box >( name )
    {}
    
    std::string Box::GetName( void ) const
    {
        return this->impl->_name;
    }
    
    void Box::ReadData(IParser *parser, BinaryStream &stream)
    {
        ( void )parser;
        
        this->impl->_data    = stream.ReadAllData();
        this->impl->_hasData = true;
    }
    
    std::vector< uint8_t > Box::GetData( void ) const
    {
        return this->impl->_data;
    }
    
    std::vector< std::pair< std::string, std::string > > Box::GetDisplayableProperties( void ) const
    {
        return {};
    }
}

XS::PIMPL::Object< ISOBMFF::Box >::IMPL::IMPL( const std::string & name ):
    _name( name ),
    _hasData( false )
{}

XS::PIMPL::Object< ISOBMFF::Box >::IMPL::IMPL( const IMPL & o ):
    _name( o._name ),
    _data( o._data ),
    _hasData( o._hasData )
{}

XS::PIMPL::Object< ISOBMFF::Box >::IMPL::~IMPL( void )
{}
