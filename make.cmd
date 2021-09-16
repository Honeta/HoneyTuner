@echo off
npm install && npm run make && mkdir .\out\honeytuner-win32-x64\audio && g++ .\source\*.cpp -o .\out\honeytuner-win32-x64\main.exe