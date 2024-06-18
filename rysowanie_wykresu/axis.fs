#version 460 core

out vec4 FragColor;

in vec3 pos;
<<<<<<< HEAD

void main()
{   
    if(sin((pos.x+1)*1200)>0.99|| sin((pos.y+1)*900)>0.99){
        FragColor=vec4(0.2f,0.2f,0.2f,1.0f);
    }
    else{
        FragColor=vec4(0.05f,0.05f,0.05f,1.0f);
    }
=======
uniform int width;
uniform int height;
uniform float Zoom;
uniform vec3 cam_pos; 

uniform vec3 Line_color = vec3(0.2f,0.2f,0.2f);



vec3 line_col = Line_color; 

float grid(vec2 uv){
    vec2 grid_uv = cos(uv*2*3.14);
    
    if(cos(uv.x/2*3.14)>0.999f||cos(uv.y/2*3.14)>0.999f) line_col*=2;

    return max(grid_uv.x,grid_uv.y);

}

void main()
{   

double x = fract(Zoom/16);
double zoom1 = (1+fract(x))*8;
double zoom2 = (pow(2.0,float(x)-float(floor(x))))*8;

double zoom = zoom2;

vec2 uv = vec2(pos.x,pos.y)+vec2(cam_pos.x/(width/float(height)),cam_pos.y);
uv.x*=width/float(height);

float line_thickness = float(zoom*zoom) / height / 4;
vec3 color = smoothstep(1.0 - line_thickness,1.0,grid(uv*float(zoom)))*line_col;

FragColor = vec4(color,1.0f);

>>>>>>> 38fda81def5fc158bd343a8363746b4e11f06388
}