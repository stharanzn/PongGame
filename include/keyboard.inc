; constants

keyboard.moveUpKey equ 0x11
keyboard.moveDownKey equ 0x1f
keyboard.cpuMoveUpkey equ 0x48
keyboard.cpuMoveDownKey equ  0x50

; inline functions

%macro keyboard.getKey 0

    ;local constants
    keyboard.paddleTopFromBottom equ display.rows - paddle.height

    mov ah, 0x1
    int 16h
    jz keyboard.endGetKey

    mov ah, 0x0
    int 16h

    cmp ah, keyboard.moveDownKey
    je keyboard.getkey.moveDown

    cmp ah, keyboard.moveUpKey
    je keyboard.getkey.moveUp

    cmp ah, keyboard.cpuMoveUpkey
    je keyboard.getKey.cpuMoveUp

    cmp ah, keyboard.cpuMoveDownKey
    je keyboard.getKey.cpuMoveDown

    jmp keyboard.endGetKey    
    ; jne stopGameLoop

    keyboard.getkey.moveUp:
        mov ax, [playerPaddle + paddle.y]

        cmp ax, 0
        je keyboard.endGetKey

        dec ax
        mov [playerPaddle + paddle.y], ax
        jmp keyboard.endGetKey

    keyboard.getkey.moveDown:
        mov ax, [playerPaddle + paddle.y] 
        cmp ax, keyboard.paddleTopFromBottom
        je keyboard.endGetKey       
        inc ax
        mov [playerPaddle + paddle.y], ax
        jmp keyboard.endGetKey

    keyboard.getKey.cpuMoveUp:
        mov ax, [cpuPaddle + paddle.y]

        cmp ax, 0
        je keyboard.endGetKey

        dec ax
        mov [cpuPaddle + paddle.y], ax
        jmp keyboard.endGetKey


    keyboard.getKey.cpuMoveDown:
        mov ax, [cpuPaddle + paddle.y] 
        cmp ax, keyboard.paddleTopFromBottom
        je keyboard.endGetKey       
        inc ax
        mov [cpuPaddle + paddle.y], ax
        jmp keyboard.endGetKey

    keyboard.endGetKey:

%endmacro
