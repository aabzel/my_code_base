@echo off
del /S *.o
If exist "*.exe" (
    Echo File exist
    del *.exe
)
cd ..
del *.o
If exist "*.exe" (
    Echo File exist
    del *.exe
)

cd 0_code_master

dir