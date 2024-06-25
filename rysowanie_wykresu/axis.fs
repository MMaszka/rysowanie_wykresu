#version 460 core

out vec4 FragColor;

in vec3 pos;

uniform int width;
uniform int height;
uniform float Zoom;
uniform vec3 cam_pos; 

uniform vec3 Line_color = vec3(0.1f,0.1f,0.1f);



vec3 line_col = Line_color; 

double x = fract(Zoom/16);
double zoom = (pow(2.0,float(x)-float(floor(x))))*8;
float line_thickness = float(zoom*zoom) / height / 6;

float grid(vec2 uv){
    vec2 grid_uv = cos(uv*2*3.14);
    if(abs(uv.x/width*Zoom-cam_pos.x)<2){
        line_col*=4;
    }
    if(abs(uv.y/height*Zoom-cam_pos.y)<2){
        line_col*=4;
    }
    if(cos(uv.x/2*3.14)>0.999f||cos(uv.y/2*3.14)>0.999f) line_col*=2;
    
    return max(grid_uv.x,grid_uv.y);

}

void main()
{   



vec2 uv = vec2(pos.x,pos.y)+vec2(cam_pos.x/(width/float(height)),cam_pos.y);
uv.x*=width/float(height);


vec3 color = smoothstep(1.0 - line_thickness,1.0,grid(uv*float(zoom)))*line_col;

FragColor = vec4(color,1.0f);

}