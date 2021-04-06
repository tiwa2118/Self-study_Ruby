#include "define.h"
#include "serial.h"
#include "lib.h"

int main( void )
{
    // シリアルデバイス初期化
    serial_init( SERIAL_DEFAULT_DEVICE );

    puts( "Hello World\n" );

    // 数値出力
    putxval( 0x10, 0 );
    puts( "\n" );
    putxval( 0xffff, 0 );
    puts( "\n" );

    // 無限ループで停止
    while( 1 )
    {
        ;
    }

    return 0;

}
