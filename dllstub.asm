; This file contains code from https://github.com/ThirteenAG/Ultimate-ASI-Loader
; and https://github.com/plusls's pull request https://github.com/ysc3839/FontMod/pull/51

ifndef X64
	.386
	.model flat, C
endif

FuncStub macro name
	extern @CatStr(<addr>, name, <:ptr>)
	name proc export
		jmp @CatStr(<addr>, name)
	name endp
endm

.code

; version
FuncStub GetFileVersionInfoA
FuncStub GetFileVersionInfoByHandle
FuncStub GetFileVersionInfoExA
FuncStub GetFileVersionInfoExW
FuncStub GetFileVersionInfoSizeA
FuncStub GetFileVersionInfoSizeExA
FuncStub GetFileVersionInfoSizeExW
FuncStub GetFileVersionInfoSizeW
FuncStub GetFileVersionInfoW
FuncStub VerFindFileA
FuncStub VerFindFileW
FuncStub VerInstallFileA
FuncStub VerInstallFileW
FuncStub VerLanguageNameA
FuncStub VerLanguageNameW
FuncStub VerQueryValueA
FuncStub VerQueryValueW

end
