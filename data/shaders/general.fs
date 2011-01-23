#version 120
uniform sampler2D uTexture;

varying vec2 vTexture;

void main(void)
{
    gl_FragColor = texture2D(uTexture, vTexture);
}

