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
 * @file        DREF.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/DREF.hpp>
#include <ISOBMFF/ContainerBox.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::DREF >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::vector< std::shared_ptr< ISOBMFF::Box > > _boxes;
};

#define XS_PIMPL_CLASS ISOBMFF::DREF
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    DREF::DREF( void ): FullBox( "dref" )
    {}
    
    void DREF::ReadData(IParser *parser, BinaryStream &stream)
    {
        ContainerBox container( "????" );
        
        FullBox::ReadData( parser, stream );
        stream.ReadBigEndianUInt32();
        container.ReadData( parser, stream );
        
        this->impl->_boxes = container.GetBoxes();
    }
    
    void DREF::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        Container::WriteBoxes( os, indentLevel );
    }
    
    void DREF::AddBox( std::shared_ptr< Box > box )
    {
        if( box != nullptr )
        {
            this->impl->_boxes.push_back( box );
        }
    }
    
    std::vector< std::shared_ptr< Box > > DREF::GetBoxes( void ) const
    {
        return this->impl->_boxes;
    }
}

XS::PIMPL::Object< ISOBMFF::DREF >::IMPL::IMPL( void )
{}

XS::PIMPL::Object< ISOBMFF::DREF >::IMPL::IMPL( const IMPL & o ):
    _boxes( o._boxes )
{}

XS::PIMPL::Object< ISOBMFF::DREF >::IMPL::~IMPL( void )
{}

