/******************************************
* �V���A���E�f�o�C�X�E�h���C�o�̖{��
*
******************************************/

/* ---- header include ---- */
#include "define.h"
#include "serial.h"


/* ---- macro ---- */
#define SERIAL_SCI_NUM    (3)                /* SCI�̐� */

// SCI�̒�`
#define H8_3069F_SCI0    ( (volatile struct h8_3069f_sci *) 0xffffb0 )
#define H8_3069F_SCI1    ( (volatile struct h8_3069f_sci *) 0xffffb8 )
#define H8_3069F_SCI2    ( (volatile struct h8_3069f_sci *) 0xffffc0 )

// SCI�̊e�탌�W�X�^��`
struct h8_3069f_sci {
    volatile UINT8 smr;
    volatile UINT8 brr;
    volatile UINT8 scr;
    volatile UINT8 tdr;
    volatile UINT8 ssr;
    volatile UINT8 rdr;
    volatile UINT8 scmr;
};

// SMR�̊e�r�b�g�̒�`
#define H8_3069F_SCI_SMR_CKS_PER1            (0 << 0)
#define H8_3069F_SCI_SMR_CKS_PER4            (1 << 0)
#define H8_3069F_SCI_SMR_CKS_PER16           (2 << 0)
#define H8_3069F_SCI_SMR_CKS_PER64           (3 << 0)
#define H8_3069F_SCI_SMR_MP                  (1 << 2)
#define H8_3069F_SCI_SMR_STOP                (1 << 3)
#define H8_3069F_SCI_SMR_OE                  (1 << 4)
#define H8_3069F_SCI_SMR_PE                  (1 << 5)
#define H8_3069F_SCI_SMR_CHR                 (1 << 6)
#define H8_3069F_SCI_SMR_CA                  (1 << 7)

// SCR�̊e�r�b�g�̒�`
#define H8_3069F_SCI_SCR_CKE0                (1 << 0)
#define H8_3069F_SCI_SCR_CKE1                (1 << 1)
#define H8_3069F_SCI_SCR_TEIE                (1 << 2)
#define H8_3069F_SCI_SCR_MPIE                (1 << 3)
#define H8_3069F_SCI_SCR_RE                  (1 << 4)        /* ��M�L�� */
#define H8_3069F_SCI_SCR_TE                  (1 << 5)        /* ���M�L�� */
#define H8_3069F_SCI_SCR_RIE                 (1 << 6)        /* ��M���荞�ݗL�� */
#define H8_3069F_SCI_SCR_TIE                 (1 << 7)        /* ���M���荞�ݗL�� */

// SSR�̊e�r�b�g�̒�`
#define H8_3069F_SCI_SSR_MPBT                (1 << 0)
#define H8_3069F_SCI_SSR_MPB                 (1 << 1)
#define H8_3069F_SCI_SSR_TEND                (1 << 2)
#define H8_3069F_SCI_SSR_PER                 (1 << 3)
#define H8_3069F_SCI_SSR_FERERS              (1 << 4)
#define H8_3069F_SCI_SSR_ORER                (1 << 5)
#define H8_3069F_SCI_SSR_RDRF                (1 << 6)        /* ��M���� */
#define H8_3069F_SCI_SSR_TDRE                (1 << 7)        /* ���M���� */

static struct {
    volatile struct h8_3069f_sci *sci;
} regs[ SERIAL_SCI_NUM ] = {
    { H8_3069F_SCI0 },
    { H8_3069F_SCI1 },
    { H8_3069F_SCI2 },
};


/***************************************************
* serial_init -- �f�o�C�X������
*
* �p�����[�^
*    index -- 
*
* �߂�l
*    0 -- �����I��
*
***************************************************/
int serial_init( int index )
{
    volatile struct h8_3069f_sci *sci = regs[ index ].sci;

    sci->scr = 0;
    sci->smr = 0;
    sci->brr = 64;        /* 20MHz�̃N���b�N����9600bps�𐶐�(25MHz�̏ꍇ��80�ɂ���) */
    sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE;        /* ����M�\ */
    sci->ssr = 0;

    return 0;
}


/***************************************************
* serial_is_send_enable -- ���M�\���ǂ����̔���
*
* �p�����[�^
*    index -- 
*
* �߂�l
*    ?? -- ??
*
***************************************************/
int serial_is_send_enable( int index )
{
    volatile struct h8_3069f_sci *sci = regs[ index ].sci;
    return ( sci->ssr & H8_3069F_SCI_SSR_TDRE );
}


/***************************************************
* serial_send_byte -- �V���A���ւ�1�������M
*
* �p�����[�^
*    index -- 
*        c -- ���M���镶��
*
* �߂�l
*    0 -- �����I��
*
***************************************************/
int serial_send_byte( int index, unsigned char c )
{
    volatile struct h8_3069f_sci *sci = regs[ index ].sci;

    /* ���M�\�ɂȂ�܂ő҂� */
    while ( !serial_is_send_enable( index ) )
    {
        ;
    }

    sci->tdr = c;
    sci->ssr &= ~H8_3069F_SCI_SSR_TDRE;        /* ���M�J�n */

    return 0;
}
