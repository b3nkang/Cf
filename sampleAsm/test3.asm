global _main
section .text
_main:
    push rbp
    mov rbp, rsp
    sub rsp, 128
    mov rax, 7
    mov [rbp - 8], rax
    mov rax, 11
    mov [rbp - 16], rax
    mov rax, 4
    mov [rbp - 24], rax
    mov rax, 8
    mov [rbp - 32], rax
    mov rax, [rbp - 24]
    mov [rbp - 8], rax
    mov rax, [rbp - 8]
    mov rbx, rax
    mov rax, [rbp - 8]
    sub rax, rbx
    mov [rbp - 40], rax
    mov rax, [rbp - 32]
    mov [rbp - 8], rax
    mov rax, [rbp - 16]
    mov rbx, rax
    mov rax, [rbp - 8]
    sub rax, rbx
    mov [rbp - 48], rax
    mov rax, [rbp - 40]
    mov [rbp - 8], rax
    mov rax, [rbp - 40]
    mov rbx, rax
    mov rax, [rbp - 8]
    imul rax, rbx
    mov [rbp - 8], rax
    mov rax, [rbp - 48]
    mov [rbp - 16], rax
    mov rax, [rbp - 48]
    mov rbx, rax
    mov rax, [rbp - 16]
    imul rax, rbx
    mov rbx, rax
    mov rax, [rbp - 8]
    add rax, rbx
    mov [rbp - 56], rax
    mov rax, [rbp - 56]
    leave
    and rsp, -16
    mov rdi, rax
    mov rax, 0x2000001
    syscall
