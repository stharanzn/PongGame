; constants

display.address equ 0xb800
display.columnsInRow equ 80
display.bytesInWord equ 2
display.rows equ 25
display.whiteSpace equ 0x7720


;inline functions

%macro display.setup 0
    mov ax, 0x03
    int 10h

    push display.address
    pop es
%endmacro

%macro display.clearScreen 0
    ; local constants
    display.clearScreen.blackSpace equ 0x0020


    ; function logic
    mov ax, display.clearScreen.blackSpace
    mov di, 0x0
    mov cx, display.columnsInRow * display.rows

    display.clearScreen.loop:
        stosw
    loop display.clearScreen.loop
%endmacro

%macro display.drawSeprator 0
    ; local constants
    display.drawSeprator.blueSpace equ 0x1120
    display.drawSeprator.halfRowBytes equ display.columnsInRow / 2 * display.bytesInWord - display.bytesInWord
    display.drawSeprator.twoRowBytes equ display.columnsInRow * 2 * display.bytesInWord - display.bytesInWord


    ; function logic
    mov ax, display.drawSeprator.blueSpace
    mov di, display.drawSeprator.halfRowBytes
    stosw

    mov cx, 13
    display.drawSeprator.loop:
        add di, display.drawSeprator.twoRowBytes
        stosw
    loop display.drawSeprator.loop

%endmacro


; callable functionss

setDI:

    ; local constants
    display.setDI.bytesInRow equ display.columnsInRow * display.bytesInWord

    ; function logic
    mov ax, display.setDI.bytesInRow
    mul bl
    shl cx, 1
    add ax, cx
    mov di, ax
ret

