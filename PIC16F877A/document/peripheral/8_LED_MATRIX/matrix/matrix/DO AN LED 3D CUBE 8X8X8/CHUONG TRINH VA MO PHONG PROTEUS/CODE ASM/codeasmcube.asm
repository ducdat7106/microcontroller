ORG 00H
;DO AN VI DIEU KHIEN LED 3D CUBE 8X8X8
;NGUOI THUC HIEN : NGUYEN TRONG TUAN ANH 11CDT1
;GVHD :GVHD: Th.s LE XUNG___________________KHAI BAO_____________________________
;TRINH BIEN DICH KEIL C
DU_LIEU DATA P1
DIEU_KHIEN DATA P3
QUET DATA P2
SO_LAN_LAP EQU 2
TOC_DO_HIEN_THI EQU 20
;____________________CHUONG TRINH CHINH______________________
MAIN:
CALL DICH_CHU  
CALL CHAY_CHU_DUOI_LEN	
CALL HIEN_CHU_MRTU	  
CALL SANG_DUOI_MANG
CALL SANG_TRAI_PHAI
CALL SANG_DUOI_LOP
CALL SANG_DAN_LOP
CALL NHAP_NHAY
JMP MAIN
;____________________DICH_CHU______________________________________
DICH_CHU:
MOV R2,#00H
DICH:
MOV R5,#TOC_DO_HIEN_THI
TOC_DO_DICH:
MOV R0,#00H
MOV R1,#00000001B
QUET_LED_DICH:
MOV A,R0 
MOV DPTR,#MA_CHU_M	
MOVC A,@A+DPTR ;
MOV DU_LIEU,A	;

MOV A,R2
MOV DPTR,#MA_DIEU_KHIEN	
MOVC A,@A+DPTR ;
MOV DIEU_KHIEN,A
;_______________________________________
MOV QUET,R1  
MOV A,R1	
RR A		
MOV R1,A	
MOV QUET,R1
;________________________________________
CALL DELAY_MS
CALL XOA
INC R0
CJNE R0,#8,QUET_LED_DICH
DJNZ R5,TOC_DO_DICH
INC R2
CJNE R2,#8,DICH
RET
;_______________________________HIEN CHU MRTU____________________
HIEN_CHU_MRTU:
MOV DPTR,#MA_CHU_M
CALL HIEN_THI_CHU
MOV DPTR,#MA_CHU_R
CALL HIEN_THI_CHU
MOV DPTR,#MA_CHU_T
CALL HIEN_THI_CHU
MOV DPTR,#MA_CHU_U
CALL HIEN_THI_CHU
RET
;///////////////////////////////////
HIEN_THI_CHU:
MOV R5,#TOC_DO_HIEN_THI
TOC_DO:
MOV R0,#00H
MOV R1,#00000001B
QUET_LED:	
MOV A,R0 ; 
MOVC A,@A+DPTR ;
MOV DU_LIEU,A	;
MOV DIEU_KHIEN,#0E7H
;//
MOV QUET,R1  
MOV A,R1	
RR A		
MOV R1,A	
MOV QUET,R1
;////
CALL DELAY_MS
CALL XOA
INC R0
CJNE R0,#8,QUET_LED
DJNZ R5,TOC_DO
RET
;___________________________CHAY CHU_________________
CHAY_CHU_DUOI_LEN:
MOV DPTR,#MA_CHU_MRTU
MOV R7,#32
CHAY_CHU:
MOV R5,#5
TOC_DO2:
MOV R0,#00H
MOV R1,#00000001B
QUET_LED2:	
MOV A,R0 
MOVC A,@A+DPTR 
MOV DU_LIEU,A	
MOV DIEU_KHIEN,#0E7H
;//
MOV QUET,R1  
MOV A,R1	
RR A		
MOV R1,A	
MOV QUET,R1
;///////////////////////
CALL DELAY_MS
CALL XOA
INC R0
CJNE R0,#8,QUET_LED2
DJNZ R5,TOC_DO2
INC DPTR
DJNZ R7,CHAY_CHU
RET
;_____________SANG DUOI MANG___________________
SANG_DUOI_MANG:
CALL XOA
MOV R0,#00H        ;Bien dem so trang thai hien thi
MOV DPTR,#MA_DIEU_KHIEN   ;Nap di chi vung du lieu 
LABEL_1:              
MOV A,R0            ; Chuyen gia tri thanh ghi R0 vao thanh ghi A
MOVC A,@A+DPTR        ; Lay du lieu tu vung nho
MOV DU_LIEU,#0FFH
MOV DIEU_KHIEN,A
MOV QUET,#0FFH            
CALL DELAY_S
INC R0            ; Lay du lieu ke tiep
CJNE R0,#7,LABEL_1        ; Kiem tra so du trang thai hien thi
;/////////////////
CALL XOA
MOV R0,#7       ;Bien dem so trang thai hien thi
;Nap di chi vung du lieu 
LABEL_2:              
MOV A,R0            ; Chuyen gia tri thanh ghi R0 vao thanh ghi A
MOVC A,@A+DPTR        ; Lay du lieu tu vung nho
MOV DU_LIEU,#0FFH
MOV DIEU_KHIEN,A
MOV QUET,#0FFH            
CALL DELAY_S
DEC R0            ; Lay du lieu ke tiep
CJNE R0,#0,LABEL_2        ; Kiem tra so du trang thai hien thi
RET
;_______________________________SANG_MANG___________________________
SANG_TRAI_PHAI:
MOV R1,#3
LAP_TP:
CALL XOA
MOV R0,#00H        ;Bien dem so trang thai hien thi
MOV DPTR,#MA_TRAI_PHAI   ;Nap di chi vung du lieu 
LABEL_TP1:              
MOV A,R0            ; Chuyen gia tri thanh ghi R0 vao thanh ghi A
MOVC A,@A+DPTR        ; Lay du lieu tu vung nho
MOV DU_LIEU,A
MOV DIEU_KHIEN,#00H
MOV QUET,#0FFH            
CALL DELAY_S
INC R0            ; Lay du lieu ke tiep
CJNE R0,#7,LABEL_1        ; Kiem tra so du trang thai hien thi
;/////////////////
CALL XOA
MOV R0,#7       ;Bien dem so trang thai hien thi
;//MOV DPTR,#MA_MANG    ;Nap di chi vung du lieu 
LABEL_TP2:              
MOV A,R0            ; Chuyen gia tri thanh ghi R0 vao thanh ghi A
MOVC A,@A+DPTR        ; Lay du lieu tu vung nho
MOV DU_LIEU,A
MOV DIEU_KHIEN,#00H
MOV QUET,#0FFH            
CALL DELAY_S
DEC R0            ; Lay du lieu ke tiep
CJNE R0,#0,LABEL_2        ; Kiem tra so du trang thai hien thi
DJNZ R1,LAP_TP
RET
;__________________________SANG_DUOI_LOP_______________________________
SANG_DUOI_LOP:
MOV R1,#SO_LAN_LAP
LAP_LAI:
CALL XOA
MOV A,#10000000B
LAP_2:
MOV DU_LIEU,#0FFH
MOV DIEU_KHIEN,#00H
MOV QUET,A
RR A
CALL DELAY_S
CJNE A,#10000000B,LAP_2
;__________________________________________________________
CALL XOA
MOV A,#00000001B
LAP_3:
MOV DU_LIEU,#0FFH
MOV DIEU_KHIEN,#00H
MOV QUET,A
RL A
CALL DELAY_S
CJNE A,#00000001B,LAP_3
DJNZ R1,LAP_LAI
RET

;___________________SANG DAN LOP_________________________
SANG_DAN_LOP:
MOV A,#00H
DICH_1:
SETB C
RRC A
MOV DU_LIEU,#0FFH
MOV DIEU_KHIEN,#00H
MOV QUET,A
CALL DELAY_S
CJNE A,#0FFH,DICH_1
;____________________________________
MOV A,#00H
DICH_2:
SETB C
RLC A
MOV DU_LIEU,#0FFH
MOV DIEU_KHIEN,#00H
MOV QUET,A
CALL DELAY_S
CJNE A,#0FFH,DICH_2
RET
;/////////____________NHAP NHAY______________________
NHAP_NHAY:
MOV R2,#3
LAP_1:
MOV DU_LIEU,#0FFH
MOV DIEU_KHIEN,#00H
MOV QUET,#0FFH
CALL DELAY_S
MOV DU_LIEU,#00H
MOV DIEU_KHIEN,#00H
MOV QUET,#00H
CALL DELAY_S 
DJNZ R2,LAP_1
RET
;_____________HAM XOA CHONG NHIEU_____________________
XOA:
MOV DU_LIEU,#00H
MOV DIEU_KHIEN,#00H
MOV QUET,#00H
CALL DELAY_MS
RET
;/____________HAM DELAY_MS_____________________
DELAY_MS:
MOV TMOD,#01H
MOV TH0,#HIGH(-1500)
MOV TL0,#LOW(-1500)
SETB TR0
JNB TF0,$
CLR TR0
CLR TF0
RET
;________________HAM DELAY_S_______________
DELAY_S:
MOV R2,#10
DELAY_1:
MOV TMOD,#10H
MOV TH1,#HIGH(-50000)
MOV TL1,#LOW(-50000)
SETB TR1
JNB TF1,$
CLR TF1
CLR TR1
DJNZ R2,DELAY_1
RET
;_____________________BANG MA_______________________________________________
MA_TRAI_PHAI: 	DB 001H,002H,004H,008H,010H,020H,040H,080H ;	 MA_MANG
MA_DIEU_KHIEN:  DB 0FEH,0FDH,0FBH,0F7H,0EFH,0DFH,0BFH,07FH; MA DIEU KHIEN
MA_CHU_M: 	DB 066H,0FFH,0FFH,0DBH,0DBH,0C3H,0C3H,000H;
MA_CHU_R: 	DB 01FH,033H,033H,01FH,00FH,01BH,033H,000H	
MA_CHU_T: 	DB 07EH,018H,018H,018H,018H,018H,018H,000H	
MA_CHU_U: 	DB 066H,066H,066H,066H,066H,066H,03CH,000H	

MA_CHU_MRTU: 	DB 066H,0FFH,0FFH,0DBH,0DBH,0C3H,0C3H,000H;
			 	DB 01FH,033H,033H,01FH,00FH,01BH,033H,000H	
 				DB 07EH,018H,018H,018H,018H,018H,018H,000H	
 				DB 066H,066H,066H,066H,066H,066H,03CH,000H
END
;_____________________________________________________________________________________














