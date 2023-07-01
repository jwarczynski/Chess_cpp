1. To compile this project it is necesseray to have g++ instaled.
2. Download CHECKERS.cpp foldef
3. Open command prompt and using 'cd' command change the working directory to downloaded folder
4. Type: g++ src/*.cpp -o bin/main.exe    (without the colon an the beginning)  
5. next change working directory to bin folder by typing: cd bin
6. type main.exe  

First choose verse coordinate(y), then column coordinate(x)


To compile with sfml, type:
    g++ src/*.cpp -o bin/main.exe -Llib -lsfml-graphics -lsfml-window -lsfml-system
then:
    cd bin 
and finally:
    main.exe


https://www.youtube.com/watch?v=_r7i5X0rXJk
