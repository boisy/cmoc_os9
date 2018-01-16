#include <cgfx.h>

/**************************************
 * Standard Text Functions (MW C)     *
 * Copyright (c) 1989 by Mike Sweet   *
 **************************************/

asm void
_cgfx_curhome(path_id path)
{
    asm
    {
_write EXTERNAL
        lda #1
        bra send1
    }
}

asm void
_cgfx_curon(path_id path)
{
    asm
    {
        ldd #$0521
        bra send2
    }
}

asm void
_cgfx_curoff(path_id path)
{
    asm
    {
        ldd #$0520
        bra send2
    }
}

asm void
_cgfx_curlft(path_id path)
{
    asm
    {
        lda #8
        bra send1
    }
}

asm void
_cgfx_currght(path_id path)
{
    asm
    {
        lda #6
        bra send1
    }
}

asm void
_cgfx_curup(path_id path)
{
    asm
    {
        lda #9
        bra send1
    }
}

asm void
_cgfx_curdwn(path_id path)
{
    asm
    {
        lda #10
        bra send1
    }
}

asm void
_cgfx_erline(path_id path)
{
    asm
    {
        lda #3
        bra send1
    }
}

asm void
_cgfx_ereoline(path_id path)
{
    asm
    {
        lda #4
        bra send1
    }
}

asm void
_cgfx_ereoscrn(path_id path)
{
    asm
    {
        lda #11
        bra send1
    }
}

asm void
_cgfx_clear(path_id path)
{
    asm
    {
        lda #12
        bra send1
    }
}

asm void
_cgfx_bell(path_id path)
{
    asm
    {
        lda #7
        bra send1
    }
}

asm void
_cgfx_crrtn(path_id path)
{
    asm
    {
        lda #13
        bra send1
    }
}

asm void
_cgfx_revon(path_id path)
{
    asm
    {
        ldd #$1f20
        bra send2
    }
}

asm void
_cgfx_revoff(path_id path)
{
    asm
    {
        ldd #$1f21
        bra send2
    }
}

asm void
_cgfx_undlnon(path_id path)
{
    asm
    {
        ldd #$1f22
        bra send2
    }
}

asm void
_cgfx_undlnoff(path_id path)
{
    asm
    {
        ldd #$1f23
        bra send2
    }
}

asm void
_cgfx_blnkon(path_id path)
{
    asm
    {
        ldd #$1f24
        bra send2
    }
}

asm void
_cgfx_blnkoff(path_id path)
{
    asm
    {
        ldd #$1f25
        bra send2
    }
}

asm void
_cgfx_insline(path_id path)
{
    asm
    {
        ldd #$1f30
        bra send2
    }
}

asm void
_cgfx_delline(path_id path)
{
    asm
    {
        ldd #$1f31

send2   pshs d,u
        ldu #2
        bra sendit

send1   pshs d,u
        ldu #1

sendit  leax ,s
        lda 7,s
        lbsr _write
        puls x,u

os9err0 bcc noerr0
        clra
        std _errno,y
        ldd #-1
        rts
noerr0 clra
        clrb
        rts
    }
}

asm void
_cgfx_curxy(path_id path, int x, int y)
{
    asm
    {
        pshs u
        leas -3,s
        lda 10,s
        ldb 12,s
        addd #$2020
        std 1,s
        lda #2
        sta ,s
        lda 8,s
        ldu #3
        leax ,s
        lbsr _write
        leas 3,s
        puls u
        bra os9err0
    }
}
