#version 460 core

out vec4 FragColor;

in vec3 pos;

uniform int width;
uniform int height;
uniform float Zoom;
uniform vec3 cam_pos; 

uniform vec3 Line_color = vec3(0.1f,0.1f,0.1f);



vec3 line_col = Line_color; 

float grid(vec2 uv){
    vec2 grid_uv = cos(uv*2*3.14);
    
    if(cos(uv.x/2*3.14)>0.999f||cos(uv.y/2*3.14)>0.999f) line_col*=2;

    return max(grid_uv.x,grid_uv.y);

}

void main()
{   

double x = fract(Zoom/16);
double zoom = (pow(2.0,float(x)-float(floor(x))))*8;

vec2 uv = vec2(pos.x,pos.y)+vec2(cam_pos.x/(width/float(height)),cam_pos.y);
uv.x*=width/float(height);

float line_thickness = float(zoom*zoom) / height / 6;
vec3 color = smoothstep(1.0 - line_thickness,1.0,grid(uv*float(zoom)))*line_col;

FragColor = vec4(color,1.0f);

}