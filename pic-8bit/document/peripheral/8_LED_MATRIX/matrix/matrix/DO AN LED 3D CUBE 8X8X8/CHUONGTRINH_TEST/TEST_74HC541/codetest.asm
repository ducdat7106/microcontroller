org 00h
ic1 bit p3.0
ic2 bit p3.1
ic3 bit p3.3
ic4 bit p3.3
ic5 bit p3.4
ic6 bit p3.5
ic7 bit p3.6
ic8 bit p3.7
main:

;loop1:
;mov p1,#00h
;call delayms
;mov p3,#00h
;call delayms
;call delay
;mov p1,#0ffh
;call delayms
;call delay
;djnz r1,loop1
call nhapnhay
call sangdan_cungluc
call sangdan_tungic





;call sangdan
;call tesic1
;call tesic2
;call te




jmp main
nhapnhay:
mov p3,#00h
mov p1,#00h
call delay
mov p3,#0ffh
call delay
mov p3,#00h
mov p1,#00h
call delay
mov p3,#0ffh
call delay
ret 
sangdan_cungluc:
mov p3,#0ffh
call delay
mov p3,#00h
mov p1,#01111111b
call delay
mov p3,#00h
mov p1,#00111111b
call delay
mov p3,#00h
mov p1,#00011111b
call delay
mov p3,#00h
mov p1,#00001111b
call delay
mov p1,#00h
mov p3,#00000111b
call delay
mov p3,#00h
mov p1,#00000011b
call delay
mov p3,#00h
mov p1,#00000001b
call delay
mov p3,#00h
mov p1,#00000000b
call delay
ret
sangdan_tungic:
mov p3,#0ffh
call delay
mov p3,#01111111b
mov p1,#01111111b
call delay
mov p3,#01111111b
mov p1,#00111111b
call delay
mov p3,#01111111b
mov p1,#00011111b
call delay
mov p3,#01111111b
mov p1,#00001111b
call delay
mov p3,#01111111b
mov p1,#00000111b
call delay
mov p3,#01111111b
mov p1,#00000011b
call delay
mov p3,#01111111b
mov p1,#00000001b
call delay
mov p3,#01111111b
mov p1,#00000000b
call delay
;//////////////
mov p3,#0ffh
call delay
mov p3,#10111111b
mov p1,#01111111b
call delay
mov p3,#10111111b
mov p1,#00111111b
call delay
mov p3,#10111111b
mov p1,#00011111b
call delay
mov p3,#10111111b
mov p1,#00001111b
call delay
mov p3,#10111111b
mov p1,#00000111b
call delay
mov p3,#10111111b
mov p1,#00000011b
call delay
mov p3,#10111111b
mov p1,#00000001b
call delay
mov p3,#10111111b
mov p1,#00000000b
call delay
;;////////
mov p3,#0ffh
call delay
mov p3,#11011111b
mov p1,#01111111b
call delay
mov p3,#11011111b
mov p1,#00111111b
call delay
mov p3,#11011111b
mov p1,#00011111b
call delay
mov p3,#11011111b
mov p1,#00001111b
call delay
mov p3,#11011111b
mov p1,#00000111b
call delay
mov p3,#11011111b
mov p1,#00000011b
call delay
mov p3,#11011111b
mov p1,#00000001b
call delay
mov p3,#11011111b
mov p1,#00000000b
call delay
;//////////
mov p3,#0ffh
call delay
mov p3,#11101111b
mov p1,#01111111b
call delay
mov p3,#11101111b
mov p1,#00111111b
call delay
mov p3,#11101111b
mov p1,#00011111b
call delay
mov p3,#11101111b
mov p1,#00001111b
call delay
mov p3,#11101111b
mov p1,#00000111b
call delay
mov p3,#11101111b
mov p1,#00000011b
call delay
mov p3,#11101111b
mov p1,#00000001b
call delay
mov p3,#11101111b
mov p1,#00000000b
call delay
;;//////
mov p3,#0ffh
call delay
mov p3,#11110111b
mov p1,#01111111b
call delay
mov p3,#11110111b
mov p1,#00111111b
call delay
mov p3,#11110111b
mov p1,#00011111b
call delay
mov p3,#11110111b
mov p1,#00001111b
call delay
mov p3,#11110111b
mov p1,#00000111b
call delay
mov p3,#11110111b
mov p1,#00000011b
call delay
mov p3,#11110111b
mov p1,#00000001b
call delay
mov p3,#11110111b
mov p1,#00000000b
call delay
;////////
mov p3,#0ffh
call delay
mov p3,#11111011b
mov p1,#01111111b
call delay
mov p3,#11111011b
mov p1,#00111111b
call delay
mov p3,#11111011b
mov p1,#00011111b
call delay
mov p3,#11111011b
mov p1,#00001111b
call delay
mov p3,#11111011b
mov p1,#00000111b
call delay
mov p3,#11111011b
mov p1,#00000011b
call delay
mov p3,#11111011b
mov p1,#00000001b
call delay
mov p3,#11111011b
mov p1,#00000000b
call delay
;;/////
mov p3,#0ffh
call delay
mov p3,#11111101b
mov p1,#01111111b
call delay
mov p3,#11111101b
mov p1,#00111111b
call delay
mov p3,#11111101b
mov p1,#00011111b
call delay
mov p3,#11111101b
mov p1,#00001111b
call delay
mov p3,#11111101b
mov p1,#00000111b
call delay
mov p3,#11111101b
mov p1,#00000011b
call delay
mov p3,#11111101b
mov p1,#00000001b
call delay
mov p3,#11111101b
mov p1,#00000000b
call delay
;;///
mov p3,#0ffh
call delay
mov p3,#11111110b
mov p1,#01111111b
call delay
mov p3,#11111110b
mov p1,#00111111b
call delay
mov p3,#11111110b
mov p1,#00011111b
call delay
mov p3,#11111110b
mov p1,#00001111b
call delay
mov p3,#11111110b
mov p1,#00000111b
call delay
mov p3,#11111110b
mov p1,#00000011b
call delay
mov p3,#11111110b
mov p1,#00000001b
call delay
mov p3,#11111110b
mov p1,#00000000b
call delay


ret




delay:
mov r1,#15
		
het_1s:
mov tmod,#01h
mov th0,#high(-50000)	
mov tl0,#low(-50000)
setb tr0
jnb tf0,$
clr tr0
clr tf0
djnz r1,het_1s
ret
end


