#ifndef _SERIAL_H_INCLUDE_
#define _SERIAL_H_INCLUDE_

int serial_init( int index );                                /* �f�o�C�X������ */
int serial_is_send_enable( int index );                      /* ���M�\�m�F   */
int serial_send_byte( int index, unsigned char b );          /* 1�������M      */

#endif // _SERIAL_H_INCLUDE_
