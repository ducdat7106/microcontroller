ORG 00h
mov p3,#0ffh
mov p0,#00h
mov p1,#0ffh
main:
mov p0,#00011000b
mov p3,#00h
mov p1,#0ffh
call delay
jmp main
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
