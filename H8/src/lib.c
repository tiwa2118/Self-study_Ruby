#include "define.h"
#include "serial.h"
#include "lib.h"



/***************************************************
* memset -- ��������������
*
* �p�����[�^
*    b -- ���������p�̃o�b�t�@
*    c -- ������������e
*    len -- ����������o�C�g��
*
* �߂�l
*    b -- ����������̃o�b�t�@
*
***************************************************/
void *memset( void *b, int c, long len )
{
    char *p;

    for ( p = b; len > 0; len-- )
    {
        *(p++) = c;
    }
    return b;
}


/***************************************************
* memcpy -- �������R�s�[
*
* �p�����[�^
*    dst -- �R�s�[��̃o�b�t�@
*    src -- �R�s�[���̃o�b�t�@
*    len -- ����������o�C�g��
*
* �߂�l
*    dst -- �R�s�[��̃o�b�t�@
*
***************************************************/
void *memcpy( void *dst, const void *src, long len )
{
    char *d = dst;
    const char *s = src;

    for ( ; len > 0; len-- )
    {
        *(d++) = *(s++);
    }
    return dst;
}


/***************************************************
* memcmp -- ��������r
*
* �p�����[�^
*    b1 -- ��r�p�̃o�b�t�@1
*    b2 -- ��r�p�̃o�b�t�@2
*   len -- ��r����o�C�g��
*
* �߂�l
*    0 -- �����I��
*   -1 -- �G���[�F�o�b�t�@1���s��
*    1 -- �G���[�F�o�b�t�@2���s��
*
***************************************************/
int memcmp( const void *b1, const void *b2, long len )
{
    const char *p1 = b1;
    const char *p2 = b2;

    for ( ; len > 0; len-- )
    {
        if ( *p1 != *p2 )
        {
            return (*p1 > *p2) ? 1 : -1;
        }
        p1++;
        p2++;
    }
    return 0;
}


/***************************************************
* strlen -- �����񒷎擾
*
* �p�����[�^
*    s -- ��r�p�̃o�b�t�@1
*
* �߂�l
*    len -- ������
*
***************************************************/
int strlen( const char *s )
{
    int len;
    for ( len = 0; *s; s++, len++ )
    {
        ;
    }
    return len;
}


/***************************************************
* strcpy -- �����񒷎擾
*
* �p�����[�^
*    *dst -- �R�s�[��̕�����o�b�t�@
*    *src -- �R�s�[���̕�����o�b�t�@
*
* �߂�l
*    d -- �R�s�[��̕�����
*
***************************************************/
char *strcpy( char *dst, const char *src )
{
    char *d = dst;
    
    for ( ;; dst++, src++ )
    {
        *dst = *src;
        if (!*src)
        {
            break;
        }
    }
    return d;
}


/***************************************************
* strcmp -- �������r
*
* �p�����[�^
*    *s1 -- ��r������1
*    *s2 -- ��r������2
*
* �߂�l
*    0 -- ����I��
*    1 -- ��r������1�ُ̈�
*   -1 -- ��r������2���ُ�
*
***************************************************/
int strcmp( const char *s1, const char *s2 )
{
    while ( *s1 || *s2 )
    {
        if ( *s1 != *s2 )
        {
            return (*s1 > *s2) ? 1 : -1;
        }
        s1++;
        s2++;
    }
    return 0;
}


/***************************************************
* strncmp -- �������r
*
* �p�����[�^
*    *s1 -- ��r������1
*    *s2 -- ��r������2
*
* �߂�l
*    0 -- ����I��
*    1 -- ��r������1�ُ̈�
*   -1 -- ��r������2���ُ�
*
***************************************************/
int strncmp( const char *s1, const char *s2, int len )
{
    while ( (*s1 || *s2) && (len > 0) )
    {
        if ( *s1 != *s2 )
        {
            return (*s1 > *s2) ? 1 : -1;
        }
        s1++;
        s2++;
        len--;
    }
    return 0;
}


/***************************************************
* putc -- 1�������M
*
* �p�����[�^
*    c -- ���M���镶��
*
* �߂�l
*    0 -- 
*
***************************************************/
int putc( unsigned char c )
{
    if ( c == '\n' )
    {
        serial_send_byte( SERIAL_DEFAULT_DEVICE, '\r' );
    }
    return serial_send_byte( SERIAL_DEFAULT_DEVICE, c );
}


/***************************************************
* puts -- �����񑗐M
*
* �p�����[�^
*    s -- ���M���镶����
*
* �߂�l
*    0 -- �����I��
*   -1 -- �G���[
*
***************************************************/
int puts( unsigned char *str )
{
    if ( NULL == str )
    {
        return -1;
    }

    while ( *str )
    {
        putc( *(str++) );
    }
    return 0;
}


/***************************************************
* putxval -- ���l�o��
*
* �p�����[�^
*    value  -- �\������l
*    column -- �\������
*
* �߂�l
*    0 -- �����I��
*
***************************************************/
int putxval( unsigned long value, int column )
{
    char buf[9];    // ������o�͗p�o�b�t�@
    char *p;
    
    
    // ���̌����珈������̂ŁA�o�b�t�@�̏I�[���痘�p����
    p = buf + sizeof(buf) - 1;
    *(p--) = '\0';
    
    if ( !value && !column )
    {
        column++;
    }
    
    while ( value || column )
    {
        // 16�i�����ɕϊ����ăo�b�t�@�Ɋi�[����
        *(p--) = "0123456789abcdef"[value & 0xf];
        // ���̌��ɐi�߂�
        value >>= 4;
        
        if ( column )
        {
            column--;
        }
    }
    
    puts(p + 1);
    
    return 0;
}
