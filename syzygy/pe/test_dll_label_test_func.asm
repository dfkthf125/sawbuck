; Copyright 2012 Google Inc. All Rights Reserved.
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
;
; Listing generated by Microsoft (R) Optimizing Compiler Version 15.00.30729.01
;
; The original C++ source code was:
;
; extern "C" int LabelTestFunc(int k) {
;   switch (k) {
;     case 1:
;     case 7:
;     case 15:
;       return 10;
;
;     case 10:
;     case 70:
;     case 150:
;       return 100;
;
;     case 100:
;     case 700:
;     case 1500:
;       return 1000;
;
;     case 1000:
;     case 7000:
;     case 15000:
;       return 10000;
;
;     default:
;       return -1;
;   }
; }

  TITLE C:\src\label_test_func.cc
  .686P
  .XMM
  include listing.inc
  .model flat

;INCLUDELIB LIBCMT
;INCLUDELIB OLDNAMES

PUBLIC _LabelTestFunc
; Function compile flags: /Odtp
_TEXT SEGMENT
tv64 = -4      ; size = 4
_k$ = 8        ; size = 4
_LabelTestFunc PROC
; File c:\src\labeltestfunc.cc
; Line 2
  push ebp
  mov ebp, esp
  push ecx
; Line 3
  mov eax, DWORD PTR _k$[ebp]
  mov DWORD PTR tv64[ebp], eax
  cmp DWORD PTR tv64[ebp], 150  ; 00000096H
  jg SHORT $LN10@LabelTestF
  cmp DWORD PTR tv64[ebp], 150  ; 00000096H
  je SHORT $LN4@LabelTestF
  mov ecx, DWORD PTR tv64[ebp]
  sub ecx, 1
  mov DWORD PTR tv64[ebp], ecx
  cmp DWORD PTR tv64[ebp], 99   ; 00000063H
  ja SHORT $LN1@LabelTestF
  mov edx, DWORD PTR tv64[ebp]
  movzx eax, BYTE PTR $LN12@LabelTestF[edx]
  jmp DWORD PTR $LN13@LabelTestF[eax*4]
$LN10@LabelTestF:
  cmp DWORD PTR tv64[ebp], 1500  ; 000005dcH
  jg SHORT $LN11@LabelTestF
  cmp DWORD PTR tv64[ebp], 1500  ; 000005dcH
  je SHORT $LN3@LabelTestF
  cmp DWORD PTR tv64[ebp], 700  ; 000002bcH
  je SHORT $LN3@LabelTestF
  cmp DWORD PTR tv64[ebp], 1000  ; 000003e8H
  je SHORT $LN2@LabelTestF
  jmp SHORT $LN1@LabelTestF
$LN11@LabelTestF:
  cmp DWORD PTR tv64[ebp], 7000  ; 00001b58H
  je SHORT $LN2@LabelTestF
  cmp DWORD PTR tv64[ebp], 15000 ; 00003a98H
  je SHORT $LN2@LabelTestF
  jmp SHORT $LN1@LabelTestF
$LN5@LabelTestF:
; Line 7
  mov eax, 10     ; 0000000aH
  jmp SHORT $LN8@LabelTestF
$LN4@LabelTestF:
; Line 12
  mov eax, 100    ; 00000064H
  jmp SHORT $LN8@LabelTestF
$LN3@LabelTestF:
; Line 17
  mov eax, 1000    ; 000003e8H
  jmp SHORT $LN8@LabelTestF
$LN2@LabelTestF:
; Line 22
  mov eax, 10000    ; 00002710H
  jmp SHORT $LN8@LabelTestF
$LN1@LabelTestF:
; Line 25
  or eax, -1
$LN8@LabelTestF:
; Line 27
  mov esp, ebp
  pop ebp
  ret 0
  npad 3
; This label will conflict with the reloc on the next line.
; TODO(rogerm): The symbols generated from assembly don't seem expressive
;     enough to generate both data and code labels, so this isn't quite
;     reproductive of the label/reloc collision we saw in chrome 17.0.963.12
;     (where we were notified of a data symbol, a reloc, and two code labels
;     all referring to the same address), but it does trigger the same check.
;     More troubling is the case table below, for which we get no data symbol
;     from the assembly driven debug info, we just get a code label. This
;     causes that label to be interpreted as code.
$LN13@LabelTestF:
  DD $LN5@LabelTestF
  DD $LN4@LabelTestF
  DD $LN3@LabelTestF
  DD $LN1@LabelTestF
$LN12@LabelTestF:
  DB 0
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 0
  DB 3
  DB 3
  DB 1
  DB 3
  DB 3
  DB 3
  DB 3
  DB 0
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 1
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 3
  DB 2
_LabelTestFunc ENDP
_TEXT ENDS
END
