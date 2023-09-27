; constants

ball.direction.goingRight equ 01b
ball.direction.goingDown equ 10b

ball.enum.direction.TopLeft equ 00b
ball.enum.direction.TopRight equ 01b
ball.enum.direction.BottomLeft equ 10b
ball.enum.direction.BottomRight equ 11b


; structure

struc ball
    .x resw 1
    .y resw 1
    .direction resw 1
endstruc


; inline functions

%macro ball.drawBall 0
    mov bx, [gameball + ball.y]
    mov cx, [gameball + ball.x]
    call setDI
    mov ax, display.whiteSpace
    stosw
%endmacro

%macro ball.xBoundCheck 0

    mov ax, [gameball + ball.direction]
    and ax, cx
    jz ball.xBoundCheck.goOpposite

    ; check bounds for cpupaddle side
    cmp bx, display.columnsInRow - 2
    jne ball.xBoundCheck.endBoundCheck

    mov cx, [gameball + ball.y]
    mov dx, [cpuPaddle + paddle.y]
    cmp dx, cx
    jle ball.xBoundCheck.checkCPUPaddleBottomBound
    jmp ball.xBoundCheck.givePointsToCPU

    ball.xBoundCheck.checkCPUPaddleBottomBound:
        mov cx, [ gameball + ball.y]
        add dx, paddle.height
        cmp dx, cx
        jge ball.xBoundCheck.bounceOffPaddle
        jmp ball.xBoundCheck.givePointsToPlayer
    
    ball.xBoundCheck.givePointsToPlayer:
        call ball.respawn
        jmp ball.xBoundCheck.endBoundCheck

    ; check bounds for player paddle side
    ball.xBoundCheck.goOpposite:
        cmp bx, 1
        jne ball.xBoundCheck.endBoundCheck

        mov cx, [ gameball + ball.y]                
        mov dx, [playerPaddle + paddle.y]
        cmp dx, cx
        jle ball.xBoundCheck.checkPaddleBottomBound        

        jmp ball.xBoundCheck.givePointsToCPU

        ball.xBoundCheck.checkPaddleBottomBound:
            mov cx, [ gameball + ball.y]
            add dx, paddle.height
            cmp dx, cx
            jge ball.xBoundCheck.bounceOffPaddle
            jmp ball.xBoundCheck.givePointsToCPU
        
        ball.xBoundCheck.bounceOffPaddle:
            mov ax, [gameball + ball.direction]
            xor ax, ball.direction.goingRight
            mov [gameball + ball.direction], ax
            jmp ball.xBoundCheck.endBoundCheck
        
        ball.xBoundCheck.givePointsToCPU:
            ; mov ax, [cpuPaddle + paddle.score]
            ; inc ax
            ; push ax
            call ball.respawn  
            jmp ball.xBoundCheck.endBoundCheck          
    
    ball.xBoundCheck.endBoundCheck:

%endmacro

%macro ball.yBoundCheck 0

    mov ax, [gameball + ball.direction]
    and ax, cx
    jz ball.yBoundCheck.goOpposite

    cmp bx, display.rows - 1
    jne ball.yBoundCheck.endBoundCheck
    mov ax, [gameball + ball.direction]
    xor ax, ball.direction.goingDown
    mov [gameball + ball.direction], ax
    jmp ball.yBoundCheck.endBoundCheck

    

    ball.yBoundCheck.goOpposite:
        cmp bx, 0
        jne ball.yBoundCheck.endBoundCheck
        mov ax, [gameball + ball.direction]
        xor ax, ball.direction.goingDown
        mov [gameball + ball.direction], ax
    
    ball.yBoundCheck.endBoundCheck:

%endmacro



; callable functions

ball.respawn:
    mov bx, display.columnsInRow / 2
    mov dx, display.rows / 2
    mov [gameball + ball.x], bx
    mov [gameball + ball.y], dx
ret

ball.move:
    mov ax, [ gameball + ball.direction]
    and ax, cx
    jz ball.move.goOpposite
    ball.move.goWith:                
        inc bx
        ret        
    
    ball.move.goOpposite:
        dec bx

ret