#include "Lib/All.h"
#include "LuaEx.h"

using namespace xxx;

struct Foo1
{
    int x = 0;
    int y = 0;
    inline void SetXY( int x = 0, int y = 0 )
    {
        this->x = x; this->y = y;
    }
    inline int GetX()
    {
        return x;
    }
    inline int GetY()
    {
        return y;
    }
};

int main()
{
    LuaEx L;
    Foo1 f1;
    L.Struct( &f1, "Foo1" )
        .Field( "x", &Foo1::x )
        .Field( "y", &Foo1::y )
        .Function( "SetXY", &Foo1::SetXY )
        .Function( "GetX", &Foo1::GetX )
        .Function( "GetY", &Foo1::GetY );
    L.DoString( R"--(
function f1()
    Foo1.SetXY( 123, 456 )
    print( Foo1.x, Foo1.y )
    Foo1.x, Foo1.y = 11, 22
    print( Foo1.GetX(), Foo1.GetY() )
end
)--" );
    if( L.PcallPop( "f1", nullptr ) )
    {
        CoutLine( "f1.x y = ", f1.x, " ", f1.y );
    }
    system( "pause" );
    return 0;
}

//struct ER
//{
//    template<typename R, typename T, typename ...PS>
//    static auto xxx(R(T::* f)( PS... ))->decltype( f )
//    {
//        typedef R( T::* FuncType )( PS... );
//        auto v = (uint64)*(size_t*)&f;
//        CoutLine( v );
//        FuncType f2;
//        (uint64)*(size_t*)&f2 = v;
//        return f2;
//    }
//};

//Foo1 f;
//( f.*ER::xxx( &Foo1::SetXY ) )( 123, 456 );
//CoutLine( "f.x y = ", f.x, f.y );


//.Field( "x", &Foo1::x )
//.Field( "y", &Foo1::y, true )
//.Function( "SetXY", []( Lua L )
//{
//    if( L.CallInstanceFunc( &Foo1::SetXY ) )
//    {
//    }
//    else if( auto o = L.ToInstance<Foo1, int>() )
//    {
//        o->SetXY( L.ToInt( -1 ) );
//    }
//    else if( auto o = L.ToInstance<Foo1>() )
//    {
//        o->SetXY();
//    }
//    else {}         // todo: throw exception to lua
//    return 0;
//} )
//.Function( "GetXY", []( Lua L )
//{
//    if( auto o = L.CheckAndGetUpValue<Foo1>() )
//    {
//        L.PushMulti( o->x, o->y );
//        return 2;
//    }
//    return 0;
//} );


//print( Foo1.GetXY() )
//Foo1.x = 0
//Foo1.y = 0    --readonly
//print( Foo1.GetXY() )


//struct Foo2
//{
//    String x;
//};

//Foo1 f1; Foo2 f2, f3;
//CoutLine( "f1.x, f1.y, f2.x, f3.x = ", f1.x, " ", f1.y, " ", f2.x, " ", f3.x );

//LuaStruct<Foo2>().Field( "x", &Foo2::x );
//L.Struct( &f2, "Foo2" );
//L.Struct( &f3, "Foo3" );

//L.PcallPop( "f1", nullptr, 12, 34, "asdfqwer", "eee" );
//L.PcallPop( "f2", [ &]( int n ) { L.DumpMulti( n ); } );


//function xxx( ... )
//    print( 1 )
//    local t = {...}
//    print( 2 )
//    table.insert( t, "asdf" )
//    table.insert( t, 12 )
//    table.insert( t, 34.5 )
//    print( 3 )
//    return table.unpack( t ) 
//end
//function f1( x, y, name1, name2 )
//    Foo1.x = x
//    Foo1.y = y
//    Foo2.x = name1
//    Foo3.x = name2
//end
//function f2()
//    return Foo1.x, Foo1.y, Foo2.x, Foo3.x
//end