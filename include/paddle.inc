; constants

paddle.height equ 5

; structure

struc paddle
    .y resw 1
    .score resw 1

endstruc

; callable functions

paddle.draw:   

    ; local constants
    paddle.draw.rowInBytes equ display.columnsInRow * display.bytesInWord - display.bytesInWord

    ; function logic
    call setDI
    mov ax, display.whiteSpace
    mov cx, paddle.height
    jmp paddle.draw.loop


    paddle.draw.loop:
        stosw
        add di, paddle.draw.rowInBytes
    loop paddle.draw.loop

ret
