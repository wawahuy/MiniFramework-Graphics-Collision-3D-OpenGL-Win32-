#version 140
in vec3 fragNormal;
in vec2 fragTexCoord;
in vec3 fragPos;
in vec4 fragColor;

out vec4 g_color;

//Texture
uniform sampler2D       texture0;
uniform sampler2D       texture1;
uniform samplerCube     texture2;
uniform sampler2D       texture3;
uniform sampler2D       texture4;
uniform samplerBuffer   texture5;
uniform sampler2D       texture6;
uniform sampler2D       texture7;

//Camera Class
uniform vec3 view_position;

//Main
void main(){

    vec3 color = texture(texture0, fragTexCoord).rgb;
    
    g_color = vec4(color, 1.0);

}
