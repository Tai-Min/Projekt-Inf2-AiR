# Projekt-Inf2-AiR

Gra zrobiona na przedmiot Informatyka 2 na 3 semestrze Automatyki i Robotyki.

Jako że większość obiektów w folderze menu i tiles jest do siebie podobna, komentarze umieściłem tylko w niektórych plikach. Resztę można bez problemu wywnioskować na podstawie okomentowanych plików. <br />
Pliki, w ktorych sa komentarze:
#### Folder menu
+ choice.h
+ difficuly.h/.cpp

#### Folder tiles 
+ barrel.h/.cpp
+ gameobject.h/.cpp

W folderze common/characters wszystko powinno byc okomentowane. <br />
game.h/.cpp jest okomentowane. <br />

## Kompilacja

Przeprowadzona w Code::Blocks <br />
w Settings -> Compiler -> Compiler Settings -> Other Options dopisać: <br />
+ -Wno-write-strings <br />

w Settings -> Compiler -> Linker settings dopisać: <br />
+ Wl,--enable-auto-import
+ -lbgi
+ -lgdi32
+ -lcomdlg32
+ -luuid
+ -loleaut32
+ -lole32
+ -lmsimg32

w Settings -> Search Directories -> Compiler dodać ścieżkę do folderu "include" projektu. <br />
W Settings -> Search Directories -> Linker dodać ścieżkę do folderu "lib" projektu.
