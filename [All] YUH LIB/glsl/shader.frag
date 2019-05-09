#version 130
in vec3 fragNormal;
in vec2 fragTexCoord;
in vec3 fragPos;
in vec4 fragColor;
in vec4 fragPosLightSpace;

out vec4 g_color;

//Texture
uniform sampler2D   texture0;
uniform sampler2D   texture1;

//Drawing
uniform vec3        draw_color;

//Camera Class
uniform vec3 view_position;

//Light
struct Light {
    vec3    position;
    vec3    color;
    float   ambientIntensity;
    float   diffuseIntensity;
    float   specularIntensity;
    float   specularPower;
    bool    activePointLight;
    float   pointConstant;
    float   pointLinear;
    float   pointExp;
};

//Main
void main(){
    if( draw_color == vec3(0,0,0))
        g_color = vec4(texture(texture0, fragTexCoord).rgb, 1.0);
    else 
        g_color = vec4(draw_color, 1.0);
}
