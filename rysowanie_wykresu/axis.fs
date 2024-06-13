#version 460 core

out vec4 FragColor;

in vec3 pos;

void main()
{   
    if(sin((pos.x+1)*1200)>0.99|| sin((pos.y+1)*900)>0.99){
        FragColor=vec4(0.2f,0.2f,0.2f,1.0f);
    }
    else{
        FragColor=vec4(0.05f,0.05f,0.05f,1.0f);
    }
}