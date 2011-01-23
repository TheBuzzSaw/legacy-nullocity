#version 120
uniform mat4 uMVPM;

attribute vec3 iPosition;
attribute vec2 iTexture;

varying vec2 vTexture;

void main(void)
{    
    vTexture = iTexture;
    vec4 p = vec4(iPosition, 1.0);
    gl_Position = uMVPM * p;
}

