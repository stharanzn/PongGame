org 0x7c00
bits 16

; constants
BiosSignature equ 0aa55h

jmp main

%include 'include/display.inc'
%include 'include/ball.inc'
%include 'include/keyboard.inc'
%include 'include/paddle.inc'


main:

    display.setup

    ; gameLoop
    gameLoop:

        display.clearScreen

        display.drawSeprator
        

        mov bx, [playerPaddle + paddle.y]
        mov cx, 0x0        
        call paddle.draw

        mov bx, [cpuPaddle + paddle.y]
        mov cx, (display.columnsInRow - 1 )        
        call paddle.draw        

        mov bx, [gameball + ball.x]
        mov cx, ball.direction.goingRight
        ; mov dx, [ playerPaddle + paddle.y]
        ball.xBoundCheck
        call ball.move
        mov [gameball + ball.x], bx

        mov bx, [gameball + ball.y]
        mov cx, ball.direction.goingDown
        ball.yBoundCheck
        call ball.move
        mov [gameball + ball.y], bx

        ball.drawBall

        keyboard.getKey

        mov ah, 0x86
        mov cx, 0x1
        mov dx, 0x4240
        int 15h

    jmp gameLoop


playerPaddle:
    istruc paddle
        at paddle.y, dw 10
        at paddle.score, dw  0
    iend

cpuPaddle: 
    istruc paddle
        at paddle.y, dw 10
        at paddle.score, dw 0
    iend

gameball:
    istruc ball
        at ball.x, dw display.columnsInRow / 2
        at ball.y, dw display.rows / 2
        at ball.direction, dw ball.enum.direction.TopRight
    iend


times 510-($-$$) db 0
dw BiosSignature
