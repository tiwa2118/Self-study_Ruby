#include "define.h"
#include "serial.h"
#include "lib.h"

int main( void )
{
    // �V���A���f�o�C�X������
    serial_init( SERIAL_DEFAULT_DEVICE );

    puts( "Hello World\n" );

    // ���l�o��
    putxval( 0x10, 0 );
    puts( "\n" );
    putxval( 0xffff, 0 );
    puts( "\n" );

    // �������[�v�Œ�~
    while( 1 )
    {
        ;
    }

    return 0;

}
