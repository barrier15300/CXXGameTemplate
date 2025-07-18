
echo git clone

if not exist "%2libs\%3" (
	echo "%3 is not found. clone try now"
	git clone %1 "%2libs\%3"

	if not exist "%2libs\include" (
		mkdir "%2libs\include"
	)

	for %%F in ("%2libs\%3\include\%3\*.h") do (
		echo #include "../%3/include/%3/%%~nxF">> "%2libs\include\%3.h"
	)

	for %%F in ("%2libs\%3\include\%3\*.hpp") do (
		echo #include "../%3/include/%3/%%~nxF">> "%2libs\include\%3.h"
	)

) else (
	echo %3 is exist
)