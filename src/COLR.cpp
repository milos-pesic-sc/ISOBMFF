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
 * @file        COLR.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/COLR.hpp>
#include <sstream>
#include <iomanip>

template<>
class XS::PIMPL::Object< ISOBMFF::COLR >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string            _colourType;
        uint16_t               _colourPrimaries;
        uint16_t               _transferCharacteristics;
        uint16_t               _matrixCoefficients;
        bool                   _fullRangeFlag;
        std::vector< uint8_t > _iccProfile;
};

#define XS_PIMPL_CLASS ISOBMFF::COLR
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    COLR::COLR( void ): Box( "colr" )
    {}
    
    void COLR::ReadData(IParser *parser, BinaryStream &stream)
    {
        this->SetColourType( stream.ReadFourCC() );
        
        if( this->GetColourType() == "nclx" )
        {
            this->SetColourPrimaries( stream.ReadUInt16() );
            this->SetTransferCharacteristics( stream.ReadUInt16() );
            this->SetMatrixCoefficients( stream.ReadUInt16() );
            this->SetFullRangeFlag( ( stream.ReadUInt8() & 0x80 ) != 0 );
        }
        else if( this->GetColourType() == "rICC" || this->GetColourType() == "prof" )
        {
            this->SetICCProfile( stream.ReadAllData() );
        }
        else
        {
            Box::ReadData( parser, stream );
        }
    }
    
    std::vector< std::pair< std::string, std::string > > COLR::GetDisplayableProperties( void ) const
    {
        auto props( Box::GetDisplayableProperties() );
        
        props.push_back( { "Colour type", this->GetColourType() } );
        
        if( this->GetColourType() == "nclx" )
        {
            props.push_back( { "Colour primaries",         std::to_string( this->GetColourPrimaries() ) } );
            props.push_back( { "Transfer characteristics", std::to_string( this->GetTransferCharacteristics() ) } );
            props.push_back( { "Matrix coefficients",      std::to_string( this->GetMatrixCoefficients() ) } );
            props.push_back( { "Full range flag",          ( this->GetFullRangeFlag() ) ? "yes" : "no" } );
        }
        else if( this->GetColourType() == "rICC" || this->GetColourType() == "prof" )
        {
            {
                std::vector< uint8_t > data;
                std::stringstream      ss;
                std::string            s;
                
                data = this->GetICCProfile();
                
                if( data.size() > 0 )
                {
                    for( auto byte: data )
                    {
                        ss << std::hex
                           << std::uppercase
                           << std::setfill( '0' )
                           << std::setw( 2 )
                           << static_cast< uint32_t >( byte )
                           << " ";
                    }
                    
                    s = ss.str();
                    s = s.substr( 0, s.length() - 1 );
                }
                
                props.push_back( { "ICC profile", s } );
            }
        }
        
        return props;
    }
    
    std::string COLR::GetColourType( void ) const
    {
        return this->impl->_colourType;
    }
    
    uint16_t COLR::GetColourPrimaries( void ) const
    {
        return this->impl->_colourPrimaries;
    }
    
    uint16_t COLR::GetTransferCharacteristics( void ) const
    {
        return this->impl->_transferCharacteristics;
    }
    
    uint16_t COLR::GetMatrixCoefficients( void ) const
    {
        return this->impl->_matrixCoefficients;
    }
    
    bool COLR::GetFullRangeFlag( void ) const
    {
        return this->impl->_fullRangeFlag;
    }
    
    std::vector< uint8_t > COLR::GetICCProfile( void ) const
    {
        return this->impl->_iccProfile;
    }
    
    void COLR::SetColourType( const std::string & value )
    {
        this->impl->_colourType = value;
    }
    
    void COLR::SetColourPrimaries( uint16_t value )
    {
        this->impl->_colourPrimaries = value;
    }
    
    void COLR::SetTransferCharacteristics( uint16_t value )
    {
        this->impl->_transferCharacteristics = value;
    }
    
    void COLR::SetMatrixCoefficients( uint16_t value )
    {
        this->impl->_matrixCoefficients = value;
    }
    
    void COLR::SetFullRangeFlag( bool value )
    {
        this->impl->_fullRangeFlag = value;
    }
    
    void COLR::SetICCProfile( const std::vector< uint8_t > & value )
    {
        this->impl->_iccProfile = value;
    }
}

XS::PIMPL::Object< ISOBMFF::COLR >::IMPL::IMPL( void ):
    _colourPrimaries( 0 ),
    _transferCharacteristics( 0 ),
    _matrixCoefficients( 0 ),
    _fullRangeFlag( false )
{}

XS::PIMPL::Object< ISOBMFF::COLR >::IMPL::IMPL( const IMPL & o ):
    _colourType( o._colourType ),
    _colourPrimaries( o._colourPrimaries ),
    _transferCharacteristics( o._transferCharacteristics ),
    _matrixCoefficients( o._matrixCoefficients ),
    _fullRangeFlag( o._fullRangeFlag ),
    _iccProfile( o._iccProfile )
{}

XS::PIMPL::Object< ISOBMFF::COLR >::IMPL::~IMPL( void )
{}

