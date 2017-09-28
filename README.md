# OpenGL #
This code was my first attempt to learn and use OpenGL. 
I initially did not have a repository for it, however I 
accidentally ran rm -rf (powershell: rm -r -fo) on the folder
that contained the code. So to be safe I decicded it was 
wise to create a repository, not only so I could go back to
working versions of the code, but also so I wouldnt almost 
lose the code. This is not a compleate repo so dont expect
for it to be working all the time. 

## To Compile ##
`g++ .\*.cpp -Og -g -std=c++17 -IC:\Dev  -LC:\Dev\lib -lglfw3 -lglad -lopengl32 -lgdi32 -o a.exe`
<br> OR <br>
`g++ .\Camera.cpp .\Texture.cpp .\Window.cpp .\Shader.cpp .\main.cpp -Og -g -std=c++17 -IC:\Dev  -LC:\Dev\lib -lglfw3 -lglad -lopengl32 -lgdi32 -o a.exe`

## Tutorials ##
- [Tutorials]( https://learnopengl.com/ )