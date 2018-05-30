#version 430 core

uniform vec4 ourColor;
uniform float time;
uniform vec2 mouseCorr;
out vec4 color;
in vec3 colorOut;
in vec3 positionOut;
in vec4 gl_FragCoord;

void main(){

    vec2 normCord;// = vec2(gl_FragCoord.x/800.0f, gl_FragCoord.y/600.0f);
    // normCord.x = gl_FragCoord.x/800.0f;
    // normCord.y = gl_FragCoord.y/600.0f;
    // color = vec4(
    // normCord.x,
    // normCord.y,
    // 0.0f,
    // 1.0f);  

    normCord.x = gl_FragCoord.x;
    normCord.y = gl_FragCoord.y;
    float radiusV = sqrt(pow(mouseCorr.x - normCord.x,2)+ pow(600 - mouseCorr.y - normCord.y,2));
    float red = (colorOut.r + sin(time * 180 / (3.14 * 10000) / 2.0f + 0.5f)) / 2.0f;
    float green = (colorOut.g + sin((time + 30) * 180 / (3.14 * 20000) / 2.0f + 0.5f)) / 2.0f;
    float blue = (colorOut.b + sin((time + 60) * 180 / (3.14 * 40000) / 2.0f + 0.5f)) / 2.0f;

    // color = vec4(
    // vec3(red, green, blue) - radiusV/500.0f,
    // 1.0f);

    color = vec4(colorOut, 1.0f);

    // color = vec4(
    // mouseCorr.x / 2.0f + 0.5f,
    // mouseCorr.y / 2.0f + 0.5f,
    // 0.0f,
    // 1.0f);  

    // color = vec4(
    // (mouseCorr.r + sin(time * 180 / (3.14 * 10000) / 2.0f + 0.5f)) / 2.0f,
    // (mouseCorr.g + sin((time + 30) * 180 / (3.14 * 20000) / 2.0f + 0.5f)) / 2.0f,
    // (colorOut.b + sin((time + 60) * 180 / (3.14 * 40000) / 2.0f + 0.5f)) / 2.0f,
    // 1.0f);    

    
     //   color = vec4(colorOut.rgb, 1.0f);


}