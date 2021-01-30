@echo off
del /S *.o
If exist "*.exe" (
    Echo File exist
    del *.exe
)
If exist "*.exe" (
    Echo File exist
    del *.exe
)

dir