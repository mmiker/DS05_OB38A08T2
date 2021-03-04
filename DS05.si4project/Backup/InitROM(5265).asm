;;
;;  aTouch_InitROM.asm
;;

    PUBLIC CO_TKEN0
    PUBLIC CO_TKEN1
    PUBLIC CO_TKCON
    PUBLIC CO_TKSW
    PUBLIC CO_TKPSSR
    PUBLIC CO_SKWKCNT
    PUBLIC CO_PSMODE
    PUBLIC CO_WKTKEN0
    PUBLIC CO_WKTKEN1
    PUBLIC CO_KEYSCANNUM
    PUBLIC CO_TKRVC
    PUBLIC CO_TKDC
    PUBLIC CO_TKFC0
    PUBLIC CO_TKFC1
    PUBLIC CO_TKFC4
    PUBLIC CO_TKFC2
    PUBLIC CO_TKFC3
    PUBLIC CO_PDGPEN
    PUBLIC CO_GKWKCNT
    PUBLIC CO_GPUCNT
    PUBLIC CO_SKUCNT
    PUBLIC CO_AUX
    PUBLIC CO_ALG
    PUBLIC CO_GP0S0
    PUBLIC CO_GP0S1
    PUBLIC CO_GP1S0
    PUBLIC CO_GP1S1
    PUBLIC CO_GP2S0
    PUBLIC CO_GP2S1
    PUBLIC CO_GP3S0
    PUBLIC CO_GP3S1
    PUBLIC CO_GP4S0
    PUBLIC CO_GP4S1
    PUBLIC CO_GP5S0
    PUBLIC CO_GP5S1
    PUBLIC CO_GP6S0
    PUBLIC CO_GP6S1
    PUBLIC CO_GP7S0
    PUBLIC CO_GP7S1
    PUBLIC CO_DEBOUNCE
    PUBLIC CO_RELEASE
    PUBLIC CO_SENSITIVITY
    PUBLIC CO_RAWMAX
    PUBLIC CO_RAWMIN
    PUBLIC _Touch_InitROM
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    CSEG    AT  1F30H
_Touch_InitROM:
    CSEG    AT  1F30H
    DB    0x02

    CSEG    AT  1F31H
    DB    0x20

    CSEG    AT  1F32H
    DB    0x00

    CSEG    AT  1F33H
    DB    0xFF

    CSEG    AT  1F34H
CO_TKEN0:
    DB    0xFD

    CSEG    AT  1F35H
CO_TKEN1:
    DB    0xF8

    CSEG    AT  1F37H
CO_TKCON:
    DB    0x01

    CSEG    AT  1F38H
CO_TKSW:
    DB    0x10

    CSEG    AT  1F39H
CO_TKPSSR:
    DB    0x08

    CSEG    AT  1F3AH
CO_SKWKCNT:
    DB    0x01

;>1: controled by watchdog timer
;1,0:controled by user
    CSEG    AT  1F3BH
CO_PSMODE:              ;power down mode
    DB    0x00

    CSEG    AT  1F3CH
CO_WKTKEN0:
    DB    0xFD

    CSEG    AT  1F3DH
CO_WKTKEN1:
    DB    0xF8

    CSEG    AT  1F3EH
CO_PDGPEN:
    DB    0x00

    CSEG    AT  1F3FH
CO_KEYSCANNUM:              ;Number of scan key
    DB    0x00

    CSEG    AT  1F40H
CO_TKRVC:
    DB    0x0F

    CSEG    AT  1F41H
CO_TKDC:
    DB    0x02

    CSEG    AT  1F42H
CO_TKFC0:
    DB    0x20

    CSEG    AT  1F43H
CO_TKFC1:
    DB    0x00

    CSEG    AT  1F44H
CO_TKFC4:               ;target frequency
    DB    0x3F

    CSEG    AT  1F45H
CO_TKFC2:               ;high frequency
    DB    0x3F

    CSEG    AT  1F46H
CO_TKFC3:               ;low frequency
    DB    0x3F

    CSEG    AT  1F47H
CO_GKWKCNT:
    DB    0x01

    CSEG    AT  1F48H
CO_GPUCNT:
    DB    0x00

    CSEG    AT  1F49H
CO_SKUCNT:
    DB    0x1F

    CSEG    AT  1F4AH
CO_AUX:
    DB    0x00

    CSEG    AT  1F4BH
CO_ALG:
    DB    0x00          ; 1: Baseline
                        ; 2: Ignore Data
                        ; others: Max/Min limit

    CSEG    AT  1F50H
CO_GP0S1:
    DB    0x00

    CSEG    AT  1F51H
CO_GP0S0:
    DB    0x00

    CSEG    AT  1F52H
CO_GP1S1:
    DB    0x00

    CSEG    AT  1F53H
CO_GP1S0:
    DB    0x00

    CSEG    AT  1F54H
CO_GP2S1:
    DB    0x00

    CSEG    AT  1F55H
CO_GP2S0:
    DB    0x00

    CSEG    AT  1F56H
CO_GP3S1:
    DB    0x00

    CSEG    AT  1F57H
CO_GP3S0:
    DB    0x00

    CSEG    AT  1F58H
CO_GP4S1:
    DB    0x00

    CSEG    AT  1F59H
CO_GP4S0:
    DB    0x00

    CSEG    AT  1F5AH
CO_GP5S1:
    DB    0x00

    CSEG    AT  1F5BH
CO_GP5S0:
    DB    0x00

    CSEG    AT  1F5CH
CO_GP6S1:
    DB    0x00

    CSEG    AT  1F5DH
CO_GP6S0:
    DB    0x00

    CSEG    AT  1F5EH
CO_GP7S1:
    DB    0x00

    CSEG    AT  1F5FH
CO_GP7S0:
    DB    0x00

    CSEG    AT  1F60H
CO_DEBOUNCE:
    DB    0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A
    DB    0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A

    CSEG    AT  1F70H
CO_RELEASE:
    DB    0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19
    DB    0x19,0x19,0x19,0x19,0x19,0x19,0x19,0x19

    CSEG    AT  1F80H
CO_SENSITIVITY:
    DB    0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD
    DB    0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD
    DB    0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD

    CSEG    AT  1FA0H
CO_RAWMAX:
    DW    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF
    DW    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF
    DW    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF


    CSEG    AT  1FD0H
CO_RAWMIN:
    DW    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    DW    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    DW    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    END