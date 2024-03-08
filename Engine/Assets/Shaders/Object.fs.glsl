#version 400

in vec2 vUV;
uniform sampler2D uTexture;

uniform vec4 uColor;

out vec4 outColor;

void main() {
    outColor = texture2D(uTexture, vUV);
}