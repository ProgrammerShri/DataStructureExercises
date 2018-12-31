@echo off
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
for /r %%d in (.) do (
    pushd %%d
    for %%f in (*.cpp) do (
        cl /EHsc /source-charset:utf-8 /O2 %%f
    )
    popd
)