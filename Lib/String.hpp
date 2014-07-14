#ifndef _STRING_HPP__
#define _STRING_HPP__


template<typename ...TS>
void String::append( TS const & ...vs )
{
    int maxLen = Utils::getFillMaxLength( vs... ) + 1;
    if( _dataLen + maxLen > _bufLen )
        reserve( _dataLen + maxLen );
    _dataLen += Utils::fill( _buf + _dataLen, vs... );
}

template<typename ...TS>
String String::make( TS const & ...vs )
{
    String rtv;
    rtv.append( vs... );
    return rtv;
}

template<typename ...TS>
String String::makeFormat( char const* format, TS const & ...vs )
{
    String rtv;
    rtv.appendFormat( format, vs... );
    return rtv;
}

template<typename ...TS>
String String::make( Pool& p, TS const & ...vs )
{
    String rtv( p );
    rtv.append( vs... );
    return rtv;
}

template<typename ...TS>
String String::makeFormat( Pool& p, char const* format, TS const & ...vs )
{
    String rtv( p );
    rtv.appendFormat( format, vs... );
    return rtv;
}




template<typename T>
void String::appendFormatCore( List<String>& ss, int& i, T const & v )
{
    ss[ i ].append( v );
}

template<typename T, typename ...TS>
void String::appendFormatCore( List<String>& ss, int& i, T const & v, TS const & ...vs )
{
    ss[ i++ ].append( v );
    appendFormatCore( ss, i, vs... );
}

template<typename ...TS>
void String::appendFormat( char const* format, TS const & ...vs )
{
    ALIGN8( char buf[ sizeof...( vs ) ][ 64 ] );
    List<String> ss( sizeof...( vs ) );
    for( int i = 0; i < sizeof...( vs ); ++i )
        ss.push( String( buf[ i ], _countof( buf[ i ] ), 0 ) );
    int num = 0;
    appendFormatCore( ss, num, vs... );

    char numBuf[ 32 ];
    String numStr( numBuf, 32, 0 );
    int offset = 0;
    while( auto c = format[ offset ] )
    {
        if( c == '{' )
        {
            c = format[ ++offset ];
            if( c == '{' )
            {
                push( '{' );
            }
            else
            {
                while( c = format[ offset ] )
                {
                    if( c == '}' )
                    {
                        Utils::fromString( num, numBuf );
                        numStr.clear();
                        if( num < 0 || num >= sizeof...( vs ) )
                        {
                            throw std::invalid_argument( "argument out of range." );
                        }
                        append( ss[ num ] );
                        break;
                    }
                    else
                    {
                        numStr.push( c );
                    }
                    ++offset;
                }
            }
        }
        else
        {
            push( c );
        }
        ++offset;
    }
}



template<typename T>
void String::appendHex( T const& v )
{
    reserve( _dataLen + 17 );
    _dataLen += Utils::toHexString( _buf + _dataLen, v );
    _buf[ _dataLen ] = '\0';
}


#endif
