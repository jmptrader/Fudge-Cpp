/**
 * Copyright (C) 2010 - 2010, Vrai Stacey.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fudge-cpp/string.hpp"
#include "fudge/string.h"

namespace
{
    typedef FudgeStatus ( *FudgeStringUTFConstructor ) ( FudgeStringImpl * *, const fudge_byte *, size_t );

    inline FudgeStringUTFConstructor getConstructorForType ( fudge::FudgeString::UnicodeType type )
    {
        switch ( type )
        {
            case fudge::FudgeString::UTF8:  return FudgeString_createFromUTF8;
            case fudge::FudgeString::UTF16: return FudgeString_createFromUTF16;
            case fudge::FudgeString::UTF32: return FudgeString_createFromUTF32;
            default:                        return 0;
        }
    }
}

namespace fudge {

FudgeString::FudgeString ( )
    : m_string ( 0 )
{
}

FudgeString::FudgeString ( const std::string & source )
    : m_string ( 0 )
{
    FudgeException::throwOnError ( FudgeString_createFromASCII ( &m_string, source.c_str ( ), source.size ( ) ) );
}

FudgeString::FudgeString ( const char * chars, size_t numchars )
    : m_string ( 0 )
{
    FudgeException::throwOnError ( FudgeString_createFromASCII ( &m_string, chars, numchars ) );
}

FudgeString::FudgeString ( const char * chars )
    : m_string ( 0 )
{
    FudgeException::throwOnError ( FudgeString_createFromASCIIZ ( &m_string, chars ) );
}

FudgeString::FudgeString ( const fudge_byte * bytes, size_t numbytes, UnicodeType type )
    : m_string ( 0 )
{
    FudgeStringUTFConstructor constructor ( getConstructorForType ( type ) );
    if ( constructor )
        FudgeException::throwOnError ( constructor ( &m_string, bytes, numbytes ) );
    else
        throw FudgeException ( FUDGE_STRING_UNKNOWN_UNICODE_TYPE );
}

FudgeString::FudgeString ( const FudgeString & source )
    : m_string ( 0 )
{
    if ( source.m_string )
    {
        FudgeException::throwOnError ( FudgeString_retain ( source.m_string ) );
        m_string = source.m_string;
    }
}

FudgeString & FudgeString::operator= ( const FudgeString & source )
{
    FudgeStringImpl * oldstring ( m_string );

    if ( source.m_string )
    {
        FudgeException::throwOnError ( FudgeString_retain ( source.m_string ) );
        m_string = source.m_string;
    }
    else
        m_string = 0;

    if ( oldstring )
        FudgeException::throwOnError ( FudgeString_release ( oldstring ) );
}

FudgeString::~FudgeString ( )
{
    if ( m_string )
        FudgeException::throwOnError ( FudgeString_release ( m_string ) );
}

}
