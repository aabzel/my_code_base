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

cd cpp_display_emitattor

dir