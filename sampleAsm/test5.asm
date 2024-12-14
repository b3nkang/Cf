global _main
section .text
_main:
    push rbp
    mov rbp, rsp
    sub rsp, 64
    mov rax, 7
    mov [rbp - 8], rax
    mov rax, 9
    mov [rbp - 16], rax
    mov rax, 15
    mov [rbp - 24], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 24]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setl al
    movzx rax, al
    cmp rax, 0
    je .L0
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1008]
    sub rax, rbx
    mov [rbp - 1016], rax
    mov rax, 0
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setg al
    movzx rax, al
    cmp rax, 0
    je .L2
    mov rax, [rbp - 24]
    mov [rbp - 1008], rax
    mov rax, [rbp - 8]
    mov rbx, rax
    mov rax, [rbp - 1008]
    sub rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    add rax, rbx
    jmp .L_return
.L2:
    mov rax, [rbp - 16]
    mov [rbp - 1016], rax
    mov rax, [rbp - 24]
    mov rbx, rax
    mov rax, [rbp - 1016]
    add rax, rbx
    jmp .L_return
    jmp .L1
.L0:
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, [rbp - 24]
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov [rbp - 1008], rax
    mov rax, 4
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setg al
    movzx rax, al
    cmp rax, 0
    je .L4
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 24]
    mov rbx, rax
    mov rax, [rbp - 1016]
    add rax, rbx
    jmp .L_return
.L4:
    mov rax, [rbp - 24]
    mov [rbp - 1008], rax
    mov rax, 1
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    sete al
    movzx rax, al
    cmp rax, 0
    je .L6
    mov rax, [rbp - 16]
    mov [rbp - 1000], rax
    mov rax, [rbp - 8]
    mov rbx, rax
    mov rax, [rbp - 1000]
    sub rax, rbx
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    sub rax, rbx
    mov [rbp - 1016], rax
    mov rax, 0
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setge al
    movzx rax, al
    cmp rax, 0
    je .L8
    mov rax, [rbp - 8]
    mov [rbp - 1000], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1000]
    imul rax, rbx
    mov [rbp - 1008], rax
    mov rax, [rbp - 24]
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1016]
    cqo
    idiv rbx
    jmp .L_return
.L8:
    mov rax, [rbp - 8]
    mov [rbp - 1008], rax
    mov rax, [rbp - 24]
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 1016]
    add rax, rbx
    jmp .L_return
    jmp .L7
.L6:
    mov rax, [rbp - 8]
    mov [rbp - 992], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 992]
    add rax, rbx
    mov [rbp - 1000], rax
    mov rax, [rbp - 24]
    mov rbx, rax
    mov rax, [rbp - 1000]
    add rax, rbx
    mov [rbp - 1008], rax
    mov rax, 2
    mov rbx, rax
    mov rax, [rbp - 1008]
    imul rax, rbx
    mov [rbp - 1016], rax
    mov rax, 4
    mov rbx, rax
    mov rax, [rbp - 1016]
    sub rax, rbx
    jmp .L_return
.L7:
.L5:
.L1:
.L_return:
    leave
    and rsp, -16
    mov rdi, rax
    mov rax, 0x2000001
    syscall
