global _main
section .text
_main:
    push rbp
    mov rbp, rsp
    sub rsp, 48
    mov rax, 10
    mov [rbp - 8], rax
    mov rax, [rbp - 8]
    mov [rbp - 1000], rax
    mov rax, 56
    mov [rbp - 992], rax
    mov rax, 7
    mov rbx, rax
    mov rax, [rbp - 992]
    cqo
    idiv rbx
    mov rbx, rax
    mov rax, [rbp - 1000]
    imul rax, rbx
    mov [rbp - 1008], rax
    mov rax, 1
    mov rbx, rax
    mov rax, [rbp - 1008]
    add rax, rbx
    mov [rbp - 1016], rax
    mov rax, 80
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    setg al
    movzx rax, al
    cmp rax, 0
    je .L0
    mov rax, 83
    mov [rbp - 16], rax
    mov rax, [rbp - 16]
    mov [rbp - 1016], rax
    mov rax, [rbp - 8]
    mov rbx, rax
    mov rax, [rbp - 1016]
    cmp rax, rbx
    mov rax, 0
    sete al
    movzx rax, al
    cmp rax, 0
    je .L2
    mov rax, 100
    jmp .L_return
.L2:
    mov rax, 101
    jmp .L_return
    jmp .L1
.L0:
.L1:
.L_return:
    leave
    and rsp, -16
    mov rdi, rax
    mov rax, 0x2000001
    syscall
