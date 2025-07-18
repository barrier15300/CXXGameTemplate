
echo %1
echo %2



python "%1scripts\DirCopy.py" "%1Asset" %2

python "%1scripts\RecToUTF8.py" "%1packages"



call "%1scripts\GitClone.bat" https://github.com/fmtlib/fmt.git "%1" fmt
call "%1scripts\GitClone.bat" https://github.com/xtensor-stack/xsimd.git "%1" xsimd

exit 0