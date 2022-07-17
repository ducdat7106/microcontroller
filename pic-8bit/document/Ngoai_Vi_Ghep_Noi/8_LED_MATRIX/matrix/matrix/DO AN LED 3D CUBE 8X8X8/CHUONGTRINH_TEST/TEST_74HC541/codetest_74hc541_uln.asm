org 00h
;p3 data
;p1 dieukhien
;p0 uln dem
mov p3,#0ffh
mov p0,#0ffh
mov p1,#00h
main:

call sangtatca
call nhapnhay
call sangdan

jmp main
sangtatca:
mov p1,#0ffh
mov p0,#0ffh
mov p3,#00h
call delay
call delay
ret
nhapnhay:
mov p1,#0ffh
mov p3,#00h
mov p0,#0ffh
call delay
mov p3,#0ffh
mov p0,#00h
mov p1,#00h
call delay
mov p1,#0ffh
mov p3,#00h
mov p0,#0ffh
call delay
mov p3,#0ffh
mov p0,#00h
mov p1,#00h
call delay
ret
sangdan:
mov p3,#0ffh
mov p1,#00h
mov p0,#00h
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#10000000b
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#11000000b
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#11100000b
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#11110000b
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#11111000b
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#11111100b
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#11111110b
call delay
mov p0,#0ffh
mov p3,#00h
mov p1,#11111111b

call delay
ret
delay:
mov r1,#10
lap:
mov tmod,#01h
mov th0,#high(-50000)
mov tl0,#low(-50000)
setb tr0
jnb tf0,$
clr tf0
clr tr0
djnz r1,lap
ret
end







